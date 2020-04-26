#ifndef CCOLOURVIEW_H
#define CCOLOURVIEW_H

#include <wx/wx.h>

struct TParameters {
    int red;
    int rect;
    int divider;
};

class CColourView : public wxScrolledWindow
{
private:
    wxBoxSizer* main_box;
    
    wxStaticText* m_text;

    TParameters* m_param;

    wxPoint m_position;
    wxPoint m_previous;

    void Render(wxDC& dc);
    void RenderRect(wxDC& dc);

    void OnPaintEvent(wxPaintEvent& event);
    void OnMouseMoved(wxMouseEvent& event);
    void OnMouseLeftDown(wxMouseEvent& event);

    DECLARE_EVENT_TABLE()

public:
    CColourView(wxWindow* parent, TParameters* param);
    ~CColourView();

    void SetSizeView(int size);
};

#endif // CCOLOURVIEW_H