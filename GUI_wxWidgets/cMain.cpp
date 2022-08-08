#include "cMain.h"

wxBEGIN_EVENT_TABLE(cMain, wxMDIParentFrame)
EVT_MENU(10001, cMain::OnMenuNew)
EVT_MENU(10002, cMain::OnMenuOpen)
EVT_MENU(10003, cMain::OnMenuSave)
EVT_MENU(10004, cMain::OnMenuExit)
wxEND_EVENT_TABLE()



cMain::cMain() : wxMDIParentFrame(nullptr, wxID_ANY, "MineSweeper - wxWidgets GUI", wxPoint(30, 30), wxSize(800, 600))
{
	// Add a menu bar
	m_MenuBar = new wxMenuBar();
	this->SetMenuBar(m_MenuBar);

	// Add Menu for file operations
	wxMenu* menuFile = new wxMenu();
	menuFile->Append(10001, "New"); // The addresses listed would generally be named constants in a sep file
	menuFile->Append(10002, "Open");
	menuFile->Append(10003, "Save");
	menuFile->Append(10004, "Exit");

	// Add File Menu to Menu Bar
	m_MenuBar->Append(menuFile, "File");

	//Add a toolbar for palette
	m_ToolBar = this->CreateToolBar(wxTB_HORIZONTAL, wxID_ANY);


	for (int i = 0; i < 16; i++)
	{
		wxButton* b = new wxButton(m_ToolBar, 10100 + i, "", wxDefaultPosition, wxSize(40, 24), 0); // m_ToolBar is set to parent, "" sets the buttons to not have text
		b->SetBackgroundColour(palette[i]);
		b->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(cMain::OnSelectColor), nullptr, this);
		m_ToolBar->AddControl(b);
	}

	wxButton* b = new wxButton(m_ToolBar, 10100 + 16, "ALPHA", wxDefaultPosition, wxDefaultSize, 0);
	b->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(cMain::OnSelectColor), nullptr, this);
	m_ToolBar->AddControl(b);
	
	m_ToolBar->Realize();

}

cMain::~cMain()
{



}

void cMain::OnMenuNew(wxCommandEvent& evt)
{
	cEditorFrame* f = new cEditorFrame(this, "Test");
	f->New(16, 16);
	f->Show();
	evt.Skip();
}

void cMain::OnMenuOpen(wxCommandEvent &evt)
{
}

void cMain::OnMenuSave(wxCommandEvent &evt)
{
}

void cMain::OnMenuExit(wxCommandEvent &evt)
{
	Close();
	evt.Skip();
}

void cMain::OnSelectColor(wxCommandEvent& evt)
{
	int colour = evt.GetId() - 10100;
	if (GetActiveChild() != nullptr)
	{
		((cEditorFrame*)GetActiveChild())->SetColour(colour);
	}
}
