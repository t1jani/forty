#include "Forty.h"
#include "Application.h"

// Logo
#ifndef wxHAS_IMAGES_IN_RESOURCES 
#include "sample.xpm"
#endif


// Event Table
wxBEGIN_EVENT_TABLE(Forty, wxFrame)
	EVT_MENU(ID_Quit, Forty::OnQuit)
	EVT_MENU(ID_About, Forty::OnAbout)

	EVT_MENU(ID_Open, Forty::OnOpen)
	EVT_MENU(ID_Save, Forty::OnSave)
	EVT_MENU(ID_SaveAs, Forty::OnSaveAs)

	//EVT_MENU(ID_Font, Forty::Font)

	#if wxUSE_PRINTING_ARCHITECTURE
	EVT_MENU(ID_Print, Forty::OnPrint)
	EVT_MENU(ID_Preview, Forty::OnPreview)
	#endif
wxEND_EVENT_TABLE()

// Initialize Application
wxIMPLEMENT_APP(Application);

Forty::Forty(const wxString& title, const wxSize& size)
	: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, size) {
	menubar = new wxMenuBar;

	// If on OSX, select the apppropriate variant of the native widget
#ifdef __WXMAC__
	SetWindowVariant(wxWINDOW_VARIANT_SMALL);
#endif

	// Set frame icon         
	SetIcon(wxICON(sample));

	// File menu options
	file = new wxMenu;
	edit = new wxMenu;
	help = new wxMenu;

	// Menu Items
	help->Append(ID_About, "&About\tF1", "Show about dialog");

	file->Append(ID_Open, "&Open\tCtrl+O", "Open a file");
	file->Append(ID_Save, "&Save\tCtrl+S", "Save a file");
	file->Append(ID_SaveAs, "&Save As...\tCtrl+Shift+S", "Save a new file");
	file->Append(ID_Preview, "Print Pre&view\tCtrl+Shift+S", "Previw Document");
	file->Append(ID_Print, "&Print\tCtrl+P", "Print Document");
	file->AppendSeparator();
	file->Append(ID_Quit, "&Exit\tCtrl+Q", "Close Application");

	edit->Append(wxID_UNDO, _("&Undo\tCtrl+Z"));
	edit->Append(wxID_REDO, _("&Redo\tCtrl+Y"));
	edit->AppendSeparator();
	edit->Append(wxID_CUT, _("Cu&t\tCtrl+X"));
	edit->Append(wxID_COPY, _("&Copy\tCtrl+C"));
	edit->Append(wxID_PASTE, _("&Paste\tCtrl+V"));
	edit->AppendSeparator();
	edit->Append(wxID_SELECTALL, _("Select A&ll\tCtrl+A"));
	edit->AppendSeparator();
	edit->Append(ID_Font, "&Font\tCtrl+I", "Change Font");

	// Add Menubar Items
	menubar->Append(file, "&File");
	menubar->Append(edit, "&Edit");
	menubar->Append(help, "&Help");

	// Attach the menu bar to the frame
	SetMenuBar(menubar);

	Center();

	// Initialize the RichTextCtrl
	m_richTextCtrl = new wxRichTextCtrl(this);

}

// P.S. WXUNUSED is a macro used for the wxEvent parameter of a hollow event handler to make some compilers not to complain about unused parameters.

// Handles quiting text editor
void Forty::OnQuit(wxCommandEvent& WXUNUSED(event)) { Close(true); }

// About Dialog
void Forty::OnAbout(wxCommandEvent& WXUNUSED(event)) {
	wxString msg;
	msg.Printf("Forty simple text editor. \n(c) Tijani Lawal, 2020");
	wxMessageBox(msg, "About Forty Text Editor", wxOK | wxICON_INFORMATION);
}

// Open File Dialog
void Forty::OnOpen(wxCommandEvent& WXUNUSED(event)) {
	wxString filePath;
	wxString fileName;
	wxArrayInt fileTypes;

	wxString filter = wxRichTextBuffer::GetExtWildcard(false, false, &fileTypes);
	if (!filter.empty()) {
		filter += "|";
	}
	filter += "All files (*.*)|*.*";

	wxFileDialog dialog(this, _("Choose a filename"), filePath, fileName, filter, wxFD_OPEN);

	if (dialog.ShowModal() == wxID_OK) {
		wxString path = dialog.GetPath();
		if (!path.empty()) {
			int filterIndex = dialog.GetFilterIndex();
			int fileType = (filterIndex < (int)fileTypes.GetCount())
				? fileTypes[filterIndex] : wxRICHTEXT_TYPE_TEXT;
			m_richTextCtrl->LoadFile(path, fileType);
		}
	}
}

// Save File Dialog
void Forty::OnSave(wxCommandEvent& event) {
	if (m_richTextCtrl->GetFilename().empty()) {
		OnSaveAs(event);
		return;
	}
	m_richTextCtrl->SaveFile();
}

// SaveAs File Dialog
void Forty::OnSaveAs(wxCommandEvent& WXUNUSED(event)) {
	wxString filter = wxRichTextBuffer::GetExtWildcard(false, true);
	wxString filePath;
	wxString fileName;

	wxFileDialog dialog(this, _("Choose a filename"), filePath, fileName, filter, wxFD_SAVE);

	if (dialog.ShowModal() == wxID_OK) {
		wxString path = dialog.GetPath();

		if (!path.empty()) {
			m_richTextCtrl->SaveFile(path);
		}
	}
}

#if wxUSE_PRINTING_ARCHITECTURE
// Printing File
void Forty::OnPrint(wxCommandEvent& WXUNUSED(event)) {
	wxGetApp().GetPrinting()->PrintBuffer(m_richTextCtrl->GetBuffer());
}

// Preview File
void Forty::OnPreview(wxCommandEvent& WXUNUSED(event)) {
	wxGetApp().GetPrinting()->PreviewBuffer(m_richTextCtrl->GetBuffer());
}

#endif // wxUSE_PRINTING_ARCHITECTURE

// Font Selection Dialog
//void Forty::OnFont(wxCommandEvent& event){}