///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "seagrassgui.h"

///////////////////////////////////////////////////////////////////////////

m_Dialog::m_Dialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer9111;
	bSizer9111 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxVERTICAL );

	m_staticText1511 = new wxStaticText( this, wxID_ANY, wxT("Vessel location"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1511->Wrap( -1 );
	m_staticText1511->SetFont( wxFont( 20, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );

	bSizer7->Add( m_staticText1511, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );


	bSizer9111->Add( bSizer7, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer1311;
	bSizer1311 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer14111112;
	bSizer14111112 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText32111112 = new wxStaticText( this, wxID_ANY, wxT("Latitude    "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText32111112->Wrap( -1 );
	bSizer14111112->Add( m_staticText32111112, 0, wxALL, 5 );

	m_lat = new wxTextCtrl( this, wxID_ANY, wxT("50.347776"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer14111112->Add( m_lat, 0, wxALL, 5 );


	bSizer1311->Add( bSizer14111112, 0, wxEXPAND, 5 );


	bSizer9111->Add( bSizer1311, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText7 = new wxStaticText( this, wxID_ANY, wxT("Longitude"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	bSizer14->Add( m_staticText7, 0, wxALL, 5 );

	m_lon = new wxTextCtrl( this, wxID_ANY, wxT("4.125299"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer14->Add( m_lon, 0, wxALL, 5 );


	bSizer9111->Add( bSizer14, 0, wxEXPAND, 5 );

	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer9111->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );

	wxBoxSizer* bSizer71;
	bSizer71 = new wxBoxSizer( wxVERTICAL );

	m_button3111 = new wxButton( this, wxID_ANY, wxT("Select Habitat .gpx"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer71->Add( m_button3111, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 5 );


	bSizer9111->Add( bSizer71, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer72;
	bSizer72 = new wxBoxSizer( wxVERTICAL );

	m_checkBox30 = new wxCheckBox( this, wxID_ANY, wxT("30 ft: Eelgrass grows here."), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer72->Add( m_checkBox30, 0, wxALL|wxEXPAND, 5 );

	m_checkBox11 = new wxCheckBox( this, wxID_ANY, wxT("10 ft: Please slow down."), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer72->Add( m_checkBox11, 0, wxALL, 5 );

	m_checkBox6 = new wxCheckBox( this, wxID_ANY, wxT("6 ft:  Potential threat to eelgrass—boaters slow down."), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer72->Add( m_checkBox6, 0, wxALL, 5 );


	bSizer9111->Add( bSizer72, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxVERTICAL );

	m_staticText4 = new wxStaticText( this, wxID_ANY, wxT("Seagrass .gpx directory:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	bSizer9->Add( m_staticText4, 0, wxALL, 5 );

	m_textCtrl_gpx = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer9->Add( m_textCtrl_gpx, 0, wxALL|wxEXPAND, 5 );


	bSizer9111->Add( bSizer9, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer9111 );
	this->Layout();
	bSizer9111->Fit( this );
	m_Timer.SetOwner( this, m_Timer.GetId() );

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( m_Dialog::OnDLeftClick ) );
	m_staticText1511->Connect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( m_Dialog::OnDLeftClick ), NULL, this );
	m_button3111->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_Dialog::OnSelectGPX ), NULL, this );
	this->Connect( m_Timer.GetId(), wxEVT_TIMER, wxTimerEventHandler( m_Dialog::OnTimer ) );
}

m_Dialog::~m_Dialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( m_Dialog::OnDLeftClick ) );
	m_staticText1511->Disconnect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( m_Dialog::OnDLeftClick ), NULL, this );
	m_button3111->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_Dialog::OnSelectGPX ), NULL, this );
	this->Disconnect( m_Timer.GetId(), wxEVT_TIMER, wxTimerEventHandler( m_Dialog::OnTimer ) );

}
