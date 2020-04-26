#ifndef CMAINFRAME_H
#define CMAINFRAME_H

#include "colourview.h"

class CMainFrame : public wxFrame
{
private:
    TParameters m_param;
    CColourView m_view;

    wxBoxSizer* m_box;
    wxTextCtrl* m_txtRect;
    wxTextCtrl* m_txtDivider;
    wxTextCtrl* m_txtColour;

    void ChangeSizeFrame();

    void OnScroll(wxScrollEvent& event);
    void OnChangeRect(wxCommandEvent& event);
    void OnChangeDivider(wxCommandEvent& event);
    void OnMouseLeftDown(wxMouseEvent& event);

    DECLARE_EVENT_TABLE()

public:
    CMainFrame(wxWindow* parent = nullptr);
    ~CMainFrame();
};

#endif // CMAINFRAME_H