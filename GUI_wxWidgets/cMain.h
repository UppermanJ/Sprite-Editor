#pragma once
#include "wx/wx.h"
#include "cEditorFrame.h"


class cMain : public wxMDIParentFrame
{
public:
	cMain();
	~cMain();

private:
	wxToolBar* m_ToolBar = nullptr; //
	wxMenuBar* m_MenuBar = nullptr;

	void OnMenuNew(wxCommandEvent &evt);
	void OnMenuOpen(wxCommandEvent &evt);
	void OnMenuSave(wxCommandEvent &evt);
	void OnMenuExit(wxCommandEvent &evt);

	void OnSelectColor(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
};

