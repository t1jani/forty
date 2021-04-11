#pragma once

#include <wx/wx.h>

#include <wx/richtext/richtextctrl.h>
#include <wx/richtext/richtextbuffer.h>
#include <wx/richtext/richtextprint.h>

class Application : public wxApp {
public:
	// Called on application startup
	virtual bool OnInit();

	// Printing
#if wxUSE_PRINTING_ARCHITECTURE
	wxRichTextPrinting* m_printing;
	wxRichTextPrinting* GetPrinting() const;

#endif // wxUSE_PRINTING_ARCHITECTURE

};