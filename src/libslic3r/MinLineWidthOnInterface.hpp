#ifndef slic3r_MinLineWidthOnInterface_hpp_
#define slic3r_MinLineWidthOnInterface_hpp_

#include "PrintConfig.hpp"

namespace Slic3r {

// min_line_width_on_interface applies only where the object touches the interface: no Z gap to it

// The first object layer on a raft, without a gap to the raft
inline bool min_line_width_on_raft_interface(const PrintObjectConfig &config)
{
    return config.min_line_width_on_interface.value > 0. && config.raft_layers.value > 0 &&
           (config.support_top_z_distance.value == 0. || config.raft_contact_distance.value == 0.);
}

// The object layers resting on the support top interface
inline bool min_line_width_on_support_interface(const PrintObjectConfig &config)
{
    return config.min_line_width_on_interface.value > 0. && config.enable_support.value &&
           config.support_top_z_distance.value == 0.;
}

} // namespace Slic3r

#endif // slic3r_MinLineWidthOnInterface_hpp_
