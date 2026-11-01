#include "StartDelay.hpp"

#include <string>
#include <vector>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/filesystem.hpp>
#include <boost/log/trivial.hpp>
#include <boost/nowide/cstdio.hpp>

namespace Slic3r {

// the gcode processor writes the first line M73s right after this tag, and only once
static const char *EXECUTABLE_BLOCK_START = "; EXECUTABLE_BLOCK_START";

// M73 P<percent> R<minutes> for the normal mode, M73 Q<percent> S<minutes> for the stealth one.
// Which of them the file carries depends on the slicing settings, so the waits countdown is
// mirrored from the lines already there instead of being guessed.
static std::string countdown_lines(const std::vector<char> &modes, int minutes_left)
{
    std::string ret;
    for (char mode : modes) {
        if (mode == 'P')
            ret += "M73 P0 R" + std::to_string(minutes_left) + "\n";
        else
            ret += "M73 Q0 S" + std::to_string(minutes_left) + "\n";
    }
    return ret;
}

bool inject_start_delay(const std::string &src_path, const std::string &dst_path, int start_delay)
{
    if (start_delay <= 0)
        return false;

    FILE *in = boost::nowide::fopen(src_path.c_str(), "rb");
    if (in == nullptr) {
        BOOST_LOG_TRIVIAL(error) << "start delay: could not open the sliced gcode";
        return false;
    }

    FILE *out = boost::nowide::fopen(dst_path.c_str(), "wb");
    if (out == nullptr) {
        BOOST_LOG_TRIVIAL(error) << "start delay: could not write the gcode to send";
        fclose(in);
        return false;
    }

    bool        ok       = true;
    bool        injected = false;
    std::string line;
    line.reserve(1024);

    auto write_str = [out, &ok](const std::string &str) {
        if (ok && !str.empty() && fwrite(str.data(), 1, str.size(), out) != str.size())
            ok = false;
    };

    // the M73s to mirror are buffered until their run ends, so that the waits can be written
    // before them: the delay has to run ahead of the estimate, not replace it
    bool              in_m73_run = false;
    std::vector<char> modes;
    std::string       m73_run;

    auto flush_m73_run = [&]() {
        if (!in_m73_run)
            return;
        // the claim action makes the printer report the wait as a preparation stage
        write_str("M1002 gcode_claim_action : 30\n");
        for (int minutes_left = start_delay; minutes_left > 0; --minutes_left) {
            write_str(countdown_lines(modes, minutes_left));
            write_str("M400 S60\n");
        }
        write_str(m73_run);
        in_m73_run = false;
        injected   = true;
        modes.clear();
        m73_run.clear();
    };

    int ch;
    while (ok) {
        ch = fgetc(in);
        if (ch == EOF) {
            if (ferror(in))
                ok = false;
            if (!line.empty()) {
                flush_m73_run();
                write_str(line);
            }
            break;
        }

        line += static_cast<char>(ch);
        if (ch != '\n')
            continue;

        if (injected) {
            write_str(line);
        } else if (in_m73_run) {
            // collect the consecutive first line M73s, one per enabled time mode
            if (boost::starts_with(line, "M73 P") && line.find(" R") != std::string::npos) {
                modes.push_back('P');
                m73_run += line;
            } else if (boost::starts_with(line, "M73 Q") && line.find(" S") != std::string::npos) {
                modes.push_back('Q');
                m73_run += line;
            } else {
                // M73 C/D (time to the next stop) belong after the countdown, with the estimate
                if (boost::starts_with(line, "M73 ")) {
                    m73_run += line;
                    line.clear();
                    continue;
                }
                flush_m73_run();
                write_str(line);
            }
        } else {
            write_str(line);
            if (boost::starts_with(line, EXECUTABLE_BLOCK_START))
                in_m73_run = true;
        }
        line.clear();
    }

    if (ok && in_m73_run)
        flush_m73_run();

    if (fclose(out) != 0)
        ok = false;
    fclose(in);

    if (ok && !injected) {
        BOOST_LOG_TRIVIAL(error) << "start delay: no insertion point in the sliced gcode";
        ok = false;
    }

    if (!ok) {
        boost::system::error_code ec;
        boost::filesystem::remove(dst_path, ec);
    }

    return ok;
}

} // namespace Slic3r
