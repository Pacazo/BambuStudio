#ifndef slic3r_GCode_StartDelay_hpp_
#define slic3r_GCode_StartDelay_hpp_

#include <string>

namespace Slic3r {

// The start delay makes the printer wait before running the start gcode, so that nothing is
// heated, homed or calibrated until the delay is over. It is not a slicing parameter: the wait
// is injected into the file sent to the printer, leaving the sliced gcode and its time estimate
// untouched.
//
// Writes src_path with the waits inserted into dst_path. Returns false and leaves dst_path
// unusable on failure. start_delay <= 0 is an error, the caller sends the original file instead.
bool inject_start_delay(const std::string &src_path, const std::string &dst_path, int start_delay);

} // namespace Slic3r

#endif // slic3r_GCode_StartDelay_hpp_
