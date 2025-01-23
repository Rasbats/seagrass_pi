///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/statline.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/checkbox.h>
#include <wx/timer.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class m_Dialog
///////////////////////////////////////////////////////////////////////////////
class m_Dialog : public wxFrame
{
	private:

	protected:
		wxStaticText* m_staticText1511;
		wxStaticText* m_staticText32111112;
		wxStaticText* m_staticText7;
		wxStaticLine* m_staticline1;
		wxButton* m_button3111;
		wxStaticText* m_staticText4;

		// Virtual event handlers, override them in your derived class
		virtual void OnDLeftClick( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnSelectGPX( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTimer( wxTimerEvent& event ) { event.Skip(); }


	public:
		wxTextCtrl* m_lat;
		wxTextCtrl* m_lon;
		wxCheckBox* m_checkBox30;
		wxCheckBox* m_checkBox11;
		wxCheckBox* m_checkBox6;
		wxTextCtrl* m_textCtrl_gpx;
		wxTimer m_Timer;

		m_Dialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_FRAME_STYLE|wxRESIZE_BORDER|wxSTAY_ON_TOP|wxTAB_TRAVERSAL );

		~m_Dialog();

};

