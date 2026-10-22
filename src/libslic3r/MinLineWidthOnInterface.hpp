#ifndef slic3r_MinLineWidthOnInterface_hpp_
#define slic3r_MinLineWidthOnInterface_hpp_

#include "PrintConfig.hpp"

namespace Slic3r {

// min_line_width_on_interface presses the molten filament onto the support or raft interface to improve adhesion.
// That is wanted only when the object touches the interface (no Z gap, e.g. a soluble or breakaway interface
// material): with a Z gap the interface is the object material and has to come off, so it is not pressed.

// The first object layer on a raft, when the raft contact Z distance is 0.
inline bool min_line_width_on_raft_interface(const PrintObjectConfig &config)
{
    return config.min_line_width_on_interface.value > 0. && config.raft_layers.value > 0 &&
           config.raft_contact_distance.value == 0.;
}

// The object layers resting on the support top interface.
inline bool min_line_width_on_support_interface(const PrintObjectConfig &config)
{
    return config.min_line_width_on_interface.value > 0. && config.enable_support.value &&
           config.support_top_z_distance.value == 0.;
}

} // namespace Slic3r

#endif // slic3r_MinLineWidthOnInterface_hpp_
