#ifndef slic3r_GUI_RADIOBOX_hpp_
#define slic3r_GUI_RADIOBOX_hpp_

#include "../wxExtensions.hpp"

#include <wx/tglbtn.h>

namespace Slic3r {
namespace GUI {

class RadioBox : public wxBitmapToggleButton
{
public:
    RadioBox(wxWindow *parent);

public:
    void SetValue(bool value) override;
	bool GetValue();
    void Rescale();
    // refresh the bitmap: a disabled radio shows the ban icon and keeps no focus ring
    bool Enable(bool enable = true) override {
        bool result = wxBitmapToggleButton::Enable(enable);
#ifdef __WXGTK__
        if (!enable) m_has_focus = false;
#endif
        update();
        return result;
    }
    bool Disable() { return Enable(false); }

private:
    void update();

private:
    ScalableBitmap m_on;
    ScalableBitmap m_off;
    ScalableBitmap m_ban;
#ifdef __WXGTK__
    // Keyboard focus ring: GTK never shows the focused bitmap state of this button
    ScalableBitmap m_on_kbfocus;
    ScalableBitmap m_off_kbfocus;
    bool m_has_focus = false;
#endif
};

}}



#endif // !slic3r_GUI_CheckBox_hpp_
