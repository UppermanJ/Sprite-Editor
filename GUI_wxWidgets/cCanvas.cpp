#include "cCanvas.h"

#include "wx/dcclient.h"
#include "wx/dcmemory.h"
#include "wx/dcbuffer.h"

wxBEGIN_EVENT_TABLE(cCanvas, wxHVScrolledWindow)
EVT_PAINT(cCanvas::OnPaint)
EVT_LEFT_DOWN(cCanvas::OnMouseLeftDown)
wxEND_EVENT_TABLE()


cCanvas::cCanvas(wxWindow* parent) : wxHVScrolledWindow(parent, wxID_ANY)
{
    
    SetRowColumnCount(40, 40);
    SetBackgroundStyle(wxBG_STYLE_PAINT);


    palette[0] = wxColor(0, 0, 0);
    palette[1] = wxColor(0, 0, 128);
    palette[2] = wxColor(0, 128, 0);
    palette[3] = wxColor(0, 128, 128);
    palette[4] = wxColor(128, 0, 0);
    palette[5] = wxColor(128, 0, 128);
    palette[6] = wxColor(128, 128, 0);
    palette[7] = wxColor(192, 192, 192);
    palette[8] = wxColor(128, 128, 128);
    palette[9] = wxColor(0, 0, 255);
    palette[10] = wxColor(0, 255, 0);
    palette[11] = wxColor(0, 255, 255);
    palette[12] = wxColor(255, 0, 0);
    palette[13] = wxColor(255, 0, 255);
    palette[14] = wxColor(255, 255, 0);
    palette[15] = wxColor(255, 255, 255);
}

cCanvas::~cCanvas()
{
}

void cCanvas::SetPixelSize(int n)
{
    m_nPixelSize = n;
    wxVarHScrollHelper::RefreshAll();
    wxVarHScrollHelper::RefreshAll();
    Refresh();
}

void cCanvas::SetSpriteData(int rows, int columns, unsigned char* pSprite)
{
    m_pSprite = pSprite;
    this->SetRowColumnCount(rows, columns);
}

void cCanvas::SetColour(int c)
{
    m_nColour = c;
}

wxCoord cCanvas::OnGetRowHeight(size_t row) const
{
    return wxCoord(m_nPixelSize);
}

wxCoord cCanvas::OnGetColumnWidth(size_t col) const
{
    return wxCoord(m_nPixelSize);
}

void cCanvas::OnDraw(wxDC& dc)
{
    dc.Clear();

    wxBrush brush = dc.GetBrush();
    wxPen pen = dc.GetPen();

    wxPosition s = GetVisibleBegin();
    wxPosition e = GetVisibleEnd();

    pen.SetStyle(wxPENSTYLE_LONG_DASH);
    pen.SetColour(wxColor(200, 200, 200));
    dc.SetPen(pen);

    for (int y = s.GetRow(); y < e.GetRow(); y++)
    {
        for (int x = s.GetCol(); x < e.GetCol(); x++)
        {
            int colour = m_pSprite[y * this->GetColumnCount() + x];

            if (colour < 16)
            {
                brush.SetColour(palette[colour]);
                brush.SetStyle(wxBRUSHSTYLE_SOLID);
            }
            else 
            {
                brush.SetStyle(wxBrushStyle::wxBRUSHSTYLE_CROSSDIAG_HATCH);
                brush.SetColour(wxColor(0, 0, 0));
            }

            dc.SetBrush(brush);
            dc.DrawRectangle(x * m_nPixelSize, y * m_nPixelSize, m_nPixelSize, m_nPixelSize);
        }
    }
}

void cCanvas::OnPaint(wxPaintEvent& evt)
{
    wxBufferedPaintDC dc(this);
    this->PrepareDC(dc);
    this->OnDraw(dc);
}

void cCanvas::OnMouseLeftDown(wxMouseEvent& evt)
{
    wxPosition s = GetVisibleBegin();
    m_pSprite[(evt.GetY() / m_nPixelSize + s.GetRow()) * this->GetColumnCount() + (evt.GetX() / m_nPixelSize + s.GetCol())] = m_nColour;
    this->Refresh(false);
    evt.Skip();
}
