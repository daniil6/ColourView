#include "colourview.h"
#include <iostream>

BEGIN_EVENT_TABLE(CColourView, wxPanel)
EVT_LEFT_DOWN(CColourView::OnMouseLeftDown)
EVT_MOTION(CColourView::OnMouseMoved)
EVT_PAINT(CColourView::OnPaintEvent)
END_EVENT_TABLE()

CColourView::CColourView(wxWindow* parent, TParameters* param)
    : wxScrolledWindow(parent, NewControlId())
    , m_param(param)
{
    this->SetScrollRate(5, 5);
    m_text = new wxStaticText(this, NewControlId(), wxT("TEXT"));
}

CColourView::~CColourView()
{
}

void CColourView::OnMouseLeftDown(wxMouseEvent& event)
{
    m_position = event.GetPosition();

    RefreshRect(wxRect(m_previous, wxSize(m_param->rect, m_param->rect)));

    m_previous.x = m_position.x / m_param->rect * m_param->rect;
    m_previous.y = m_position.y / m_param->rect * m_param->rect;

    RefreshRect(wxRect(m_previous, wxSize(m_param->rect, m_param->rect)));

    int blue = m_position.x / m_param->rect * m_param->divider;
    int green = m_position.y / m_param->rect * m_param->divider;

    event.ResumePropagation(1);
    event.SetPosition(wxPoint(blue, green));
    event.Skip();
}

void CColourView::OnMouseMoved(wxMouseEvent& event)
{
    wxPoint mousePosition = event.GetPosition();
    std::cout << "x=" << mousePosition.x << " y=" << mousePosition.y << "\t";

    int xx = mousePosition.x / m_param->rect * m_param->rect;
    int yy = mousePosition.y / m_param->rect * m_param->rect;

    std::cout << "x=" << xx << " y=" << yy << "\t";

    int blue = mousePosition.x / m_param->rect * m_param->divider;
    int green = mousePosition.y / m_param->rect * m_param->divider;

    std::cout << "blue=" << blue << " green=" << green << std::endl;
}

void CColourView::OnPaintEvent(wxPaintEvent& event)
{
    wxPaintDC dc(this);
    Render(dc);
}

void CColourView::Render(wxDC& dc)
{
    int xx(0), yy(0);
    int green(0), blue(0);

    while(green < 256) {
        blue = xx = 0;
        while(blue < 256) {

            int pX = m_position.x / m_param->rect * m_param->rect;
            int pY = m_position.y / m_param->rect * m_param->rect;

            if(pX == xx && pY == yy)
                dc.SetPen(wxPen(wxColor(255, 255, 255), 1));
            else
                dc.SetPen(wxPen(wxColor(m_param->red, green, blue), 1));

            dc.SetBrush(wxColor(m_param->red, green, blue));
            dc.DrawRectangle(wxPoint(xx, yy), wxSize(m_param->rect, m_param->rect));

            if(m_param->rect > 45)
                dc.DrawText(wxString::Format(wxT("%d, %d"), green, blue), wxPoint(xx, yy));

            xx += m_param->rect;
            blue += m_param->divider;
        }
        yy += m_param->rect;
        green += m_param->divider;
    }
}

void CColourView::SetSizeView(int size)
{
    m_position.x = 0;
    m_position.y = 0;

    m_previous.x = 0;
    m_previous.y = 0;

    this->SetMaxSize(wxSize(size, size));
    m_text->SetPosition(wxPoint(size - 1, size));
}