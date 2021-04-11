#pragma once

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wx.h"

#include "wx/richtext/richtextctrl.h"
#include <wx/richtext/richtextbuffer.h>


// IDS for controls and menu commands
enum {
	// Menu Items
	ID_Quit = wxID_EXIT,
	ID_About = wxID_ABOUT,

	ID_Open = wxID_OPEN,
	ID_Save = wxID_SAVE,
	ID_SaveAs = wxID_SAVEAS,

	ID_Print = wxID_PRINT,
	ID_Preview = wxID_PREVIEW,
	ID_Font
};

class Forty : public wxFrame {
public:
	Forty(const wxString& title, const wxSize& size);

	// Window Menubar
	wxMenuBar* menubar;
	wxMenu* file;
	wxMenu* edit;
	wxMenu* help;

	// Event Handlers
	void OnQuit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);

	void OnOpen(wxCommandEvent& event);
	void OnSave(wxCommandEvent& event);
	void OnSaveAs(wxCommandEvent& event);

	//void OnFont(wxCommandEvent& event);

#if wxUSE_PRINTING_ARCHITECTURE
	void OnPrint(wxCommandEvent& event);
	void OnPreview(wxCommandEvent& event);
#endif // wxUSE_PRINTING_ARCHITECTURE


private:
	// any class wishing to process wxWidgets events must use this macro
	DECLARE_EVENT_TABLE()

	wxRichTextCtrl* m_richTextCtrl;

};


