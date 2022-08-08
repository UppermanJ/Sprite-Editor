#include "cEditorFrame.h"
 

wxBEGIN_EVENT_TABLE(cEditorFrame, wxMDIChildFrame)
EVT_SLIDER(20001, cEditorFrame::OnZoomChange)
wxEND_EVENT_TABLE()

cEditorFrame::cEditorFrame(wxMDIParentFrame* parent, wxString sName) : wxMDIChildFrame(parent, wxID_ANY, sName)
{
	m_Canvas = new cCanvas(this);

	m_StatusBar = this->CreateStatusBar(2, wxSTB_DEFAULT_STYLE, wxID_ANY);
	m_ZoomSlider = new wxSlider(m_StatusBar, 20001, 8, 1, 32);
}

cEditorFrame::~cEditorFrame()
{
}

void cEditorFrame::SetColour(int c)
{
}

bool cEditorFrame::Save(wxString sFileName)
{
	return false;
}

bool cEditorFrame::Open(wxString sFileName)
{
	return false;
}

bool cEditorFrame::New(int r, int c)
{
	delete[] m_pSprite;
	m_pSprite = new unsigned char[r * c]{ 0 };
	m_Canvas->SetSpriteData(r, c, m_pSprite);
	sprBase = olcSprite(c, r);

	return false;
}

void cEditorFrame::OnZoomChange(wxCommandEvent& evt)
{
	m_StatusBar->SetStatusText(wxString("Zoom: ") << m_ZoomSlider->GetValue(), 1);
	m_Canvas->SetPixelSize(m_ZoomSlider->GetValue());
	evt.Skip();
}
