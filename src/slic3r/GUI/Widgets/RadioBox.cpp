#include "RadioBox.hpp"

#include "../wxExtensions.hpp"

namespace Slic3r {
namespace GUI {
RadioBox::RadioBox(wxWindow *parent)
    : wxBitmapToggleButton(parent, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE)
    , m_on(this, "radio_on", 18)
    , m_off(this, "radio_off", 18)
    , m_ban(this, "radio_ban", 18)
#ifdef __WXGTK__
    , m_on_kbfocus(this, "radio_on_kbfocus", 18)
    , m_off_kbfocus(this, "radio_off_kbfocus", 18)
#endif
{
    // SetBackgroundStyle(wxBG_STYLE_TRANSPARENT);
    if (parent) SetBackgroundColour(parent->GetBackgroundColour());
    // Bind(wxEVT_TOGGLEBUTTON, [this](auto& e) { update(); e.Skip(); });
#ifdef __WXGTK__
    Bind(wxEVT_SET_FOCUS, [this](wxFocusEvent &e) { m_has_focus = true; update(); e.Skip(); });
    Bind(wxEVT_KILL_FOCUS, [this](wxFocusEvent &e) { m_has_focus = false; update(); e.Skip(); });
#endif
    SetSize(m_on.GetBmpSize());
    SetMinSize(m_on.GetBmpSize());
    update();
}

void RadioBox::SetValue(bool value)
{
    wxBitmapToggleButton::SetValue(value);
    update();
}

bool RadioBox::GetValue()
{
    return wxBitmapToggleButton::GetValue();
}


void RadioBox::Rescale()
{
    m_on.msw_rescale();
    m_off.msw_rescale();
    m_ban.msw_rescale();
#ifdef __WXGTK__
    m_on_kbfocus.msw_rescale();
    m_off_kbfocus.msw_rescale();
#endif
    SetSize(m_on.GetBmpSize());
    update();
}

void RadioBox::update() {
#ifdef __WXGTK__
    if (m_has_focus && IsEnabled()) {
        SetBitmap((GetValue() ? m_on_kbfocus : m_off_kbfocus).bmp());
        return;
    }
#endif
        SetBitmap((GetValue() ? m_on : m_off).bmp());
        SetBitmapDisabled(m_ban.bmp());

}

}
}

