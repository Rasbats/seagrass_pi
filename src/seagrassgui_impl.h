/******************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  seagrass Plugin
 * Author:   Mike Rossiter
 *
 ***************************************************************************
 *   Copyright (C) 2013 by Mike Rossiter                                   *
 *   $EMAIL$                                                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************
 */

#ifndef _CALCULATORGUI_IMPL_H_
#define _CALCULATORGUI_IMPL_H_

#ifdef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "seagrass_pi.h"
#include "seagrassgui.h"

#include "NavFunc.h"
#include "tinyxml.h"

#include <list>
#include <vector>

#include "qtstylesheet.h"
#include <wx/graphics.h>
#include <wx/window.h>
#include <wx/menu.h>
#include <wx/aui/aui.h>
#include <wx/textfile.h>
#include <wx/filedlg.h>
#include <cmath>
#include <iostream>
#include <wx/defs.h>
#include <wx/msgdlg.h>
#include <wx/timer.h>
#include <wx/dirdlg.h>
#include "nmea0183.h"
#include <wx/tokenzr.h>

struct Point {
    // Coordinates of the point
    double x, y;
};

#ifdef __ANseagrassOID__
#include <wx/qt/private/wxQtGesture.h>
#endif


#define ID_SOMETHING 2001
#define ID_SOMETHING_ELSE 2002

using namespace std;

class seagrass_pi;
class Position;
class NMEA0183;

class Dlg : public m_Dialog {
public:
    Dlg(wxWindow* parent, seagrass_pi* ppi);
    ~Dlg();

    wxWindow* pParent;
    seagrass_pi* pPlugIn;

#ifdef __ANseagrassOID__
    void OnMouseEvent(wxMouseEvent& event);    
    wxPoint m_resizeStartPoint;
    wxSize m_resizeStartSize;
    bool m_binResize;
    bool m_binResize2;

    void OnPopupClick(wxCommandEvent& evt);
    void OnDLeftClick(wxMouseEvent& event);
    void sizeplus(wxCommandEvent& event);
    void sizeminus(wxCommandEvent& event);


#endif

    void OnPSGPX(wxCommandEvent& event);
    void OnSelectGPX(wxCommandEvent& event);
    bool OpenXML();

    vector<Position> my_positions;
    vector<Position> my_points;

    void Addpoint(TiXmlElement* Route, wxString ptlat, wxString ptlon,
        wxString ptname, wxString ptsym, wxString pttype);

    wxString rte_start;
    wxString rte_end;
    void NMEAStringAll(wxString& sentence);
    void OnTimer(wxTimerEvent&);
    PlugIn_Position_Fix_Ex m_lastfix, m_lasttimerfix;

private:
    void OnClose(wxCloseEvent& event);
    double lat1, lon1, lat2, lon2;
    bool error_found;
    bool dbg;

    bool pointInPolygon(Point& p, vector<Point>& polygon);
    wxString m_gpx_path;

    vector<Point> m_points;
    Point point;
    bool is_inside;
    wxString dirname;

    void ReadGPX();
    void OnCreateDirectory(wxCommandEvent& event);
    void NMEAString(wxString& string);
    NMEA0183 m_NMEA0183; // Used to parse NMEA Sentences
    short mPriDepth;
    double mydepth;
};

class Position {
public:
    wxString lat, lon, wpt_num;
    Position *prev, *next; /* doubly linked circular list of positions */
    int routepoint;
};

#endif
