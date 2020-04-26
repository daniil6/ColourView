#include "MainFrame.h"
#include <wx/valnum.h>

BEGIN_EVENT_TABLE(CMainFrame, wxFrame)
EVT_LEFT_DOWN(CMainFrame::OnMouseLeftDown)
EVT_SCROLL(CMainFrame::OnScroll)
END_EVENT_TABLE()

#define STYLE_FRAME wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER)

CMainFrame::CMainFrame(wxWindow* parent)
    : wxFrame(parent, wxID_ANY, wxT("Colour View"), wxDefaultPosition, wxDefaultSize, STYLE_FRAME)
    , m_param{ 0, 10, 5 }
    , m_view(this, &m_param)
{
    SetIcon(wxICON(colour));
    SetBackgroundColour(*wxWHITE);

    wxIntegerValidator<unsigned short> valRect;
    valRect.SetRange(2, 100);

    wxIntegerValidator<unsigned short> valDivider;
    valDivider.SetRange(1, 255);

    m_txtRect = new wxTextCtrl(this, NewControlId(), wxString::Format(wxT("%d"), m_param.rect), wxDefaultPosition,
        wxDefaultSize, wxNO_BORDER | wxALIGN_CENTER_HORIZONTAL | wxTE_PROCESS_ENTER, valRect);
    m_txtDivider = new wxTextCtrl(this, NewControlId(), wxString::Format(wxT("%d"), m_param.divider), wxDefaultPosition,
        wxDefaultSize, wxNO_BORDER | wxALIGN_CENTER_HORIZONTAL | wxTE_PROCESS_ENTER, valDivider);
    m_txtColour = new wxTextCtrl(this, NewControlId(), wxT("0, 0, 0"), wxDefaultPosition, wxDefaultSize,
        wxTE_READONLY | wxNO_BORDER | wxALIGN_CENTER_HORIZONTAL);

    m_txtDivider->SetToolTip(wxT("(255 / x) + 1"));

    wxSlider* slider = new wxSlider(this, NewControlId(), 0, 0, 255);

    m_box = new wxBoxSizer(wxVERTICAL);
    wxStaticBoxSizer* st_box = nullptr;
    wxBoxSizer* h_box = new wxBoxSizer(wxHORIZONTAL);

    st_box = new wxStaticBoxSizer(wxHORIZONTAL, this, wxT("Длина квадрата"));
    st_box->Add(m_txtRect);
    h_box->Add(st_box, 0, wxALL, 5);

    st_box = new wxStaticBoxSizer(wxHORIZONTAL, this, wxT("Градация"));
    st_box->Add(m_txtDivider);
    h_box->Add(st_box, 0, wxALL, 5);

    st_box = new wxStaticBoxSizer(wxHORIZONTAL, this, wxT("Цвет"));
    st_box->Add(m_txtColour);
    h_box->Add(st_box, 0, wxALL, 5);

    m_box->Add(h_box);
    m_box->Add(&m_view, 1, wxEXPAND);
    m_box->Add(slider, 0, wxEXPAND);

    ChangeSizeFrame();

    Bind(wxEVT_TEXT_ENTER, &CMainFrame::OnChangeRect, this, m_txtRect->GetId());
    Bind(wxEVT_TEXT_ENTER, &CMainFrame::OnChangeDivider, this, m_txtDivider->GetId());
}

CMainFrame::~CMainFrame()
{
}

void CMainFrame::OnMouseLeftDown(wxMouseEvent& event)
{
    auto obg = this->FindWindow(event.GetId());
    if(obg == &m_view) {
        wxPoint pos = event.GetPosition();
        m_txtColour->SetValue(
            wxString::Format(wxT("%s, %d, %d"), m_txtColour->GetValue().BeforeFirst(wxT(',')), pos.y, pos.x));
    }
}

void CMainFrame::OnChangeRect(wxCommandEvent& event)
{
    m_param.rect = wxAtoi(m_txtRect->GetValue());
    ChangeSizeFrame();
}

void CMainFrame::OnChangeDivider(wxCommandEvent& event)
{
    m_param.divider = wxAtoi(m_txtDivider->GetValue());
    ChangeSizeFrame();
}

void CMainFrame::OnScroll(wxScrollEvent& event)
{
    int red = event.GetPosition();
    m_txtColour->SetValue(wxString::Format(wxT("%d,%s"), red, m_txtColour->GetValue().AfterFirst(wxT(','))));
    m_param.red = red;
    Refresh();
}

void CMainFrame::ChangeSizeFrame()
{
    int size = m_param.rect * (255 / m_param.divider + 1);
    m_view.Refresh();
    m_view.SetSizeView(size);
    this->SetSizerAndFit(m_box);
}