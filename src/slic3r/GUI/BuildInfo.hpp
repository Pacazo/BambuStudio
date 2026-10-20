#ifndef slic3r_GUI_BuildInfo_hpp_
#define slic3r_GUI_BuildInfo_hpp_

#include <string>

namespace Slic3r { namespace GUI {

// Regenerated on every build, not on configure
std::string build_info_commit();
std::string build_info_datetime();

}} // namespace Slic3r::GUI

#endif
