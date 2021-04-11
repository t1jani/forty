#include "Application.h"
#include "Forty.h"

// Printing
#if wxUSE_PRINTING_ARCHITECTURE
wxRichTextPrinting* Application::GetPrinting() const {
	return m_printing;
}

#endif // wxUSE_PRINTING_ARCHITECTURE

bool Application::OnInit() {

	// Get the display size in pixel
	wxSize size = wxGetDisplaySize();
	// Set size of the frame on startup
	//			x	  y
	size.Scale(0.50, 0.75);

	Forty* forty = new Forty("Forty", size);

#if wxUSE_PRINTING_ARCHITECTURE
	m_printing = new wxRichTextPrinting();
	m_printing->SetFooterText("Page @PAGENUM@", wxRICHTEXT_PAGE_ALL, wxRICHTEXT_PAGE_RIGHT);

	// Set parent window to allow print preview windows aware of its parent.
	m_printing->SetParentWindow(forty);
#endif

	forty->Show(true);
	return true;
}