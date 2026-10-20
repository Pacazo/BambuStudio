#include "BuildInfo.hpp"
#include "build_info.h"

namespace Slic3r { namespace GUI {

std::string build_info_commit()
{
    return SLIC3R_GIT_COMMIT;
}

std::string build_info_datetime()
{
    return SLIC3R_BUILD_DATETIME;
}

}} // namespace Slic3r::GUI
