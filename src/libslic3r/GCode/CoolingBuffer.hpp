#ifndef slic3r_CoolingProcess_hpp_
#define slic3r_CoolingProcess_hpp_
#include "../libslic3r.h"
#include "GCodeEditor.hpp"

namespace Slic3r {

class CoolingBuffer
{
public:
    CoolingBuffer(){};

    // park_layer_time > 0: a layer shorter than this even at the minimum print speed is not slowed down, the print head parks
    // for the rest of the time.
    float calculate_layer_slowdown(std::vector<PerExtruderAdjustments> &per_extruder_adjustments, float park_layer_time = 0.f);

    // Results of the last calculate_layer_slowdown() call.
    // Time the print head parks after the layer, 0 if it does not park.
    float park_time() const { return m_park_time; }
    // The layer could not be slowed down to the layer time of the filament, because the minimum print speed was reached.
    bool  layer_time_not_reached() const { return m_layer_time_not_reached; }

private:
    // Old logic: proportional.
    bool m_cooling_logic_proportional = false;
    float m_park_time              = 0.f;
    bool  m_layer_time_not_reached = false;
};

}
#endif