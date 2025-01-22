/******************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  seagrass Plugin
 * Author:   Mike Rossiter
 *
 ***************************************************************************
 *   Copyright (C) 2025 by Mike Rossiter                                   *
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
 * Massive thanks here:
 * https://stackoverflow.com/questions/14149099/raycasting-algorithm-with-gps-coordinates
 * 
 */

#include "seagrassgui_impl.h"
#include "icons.h"
#include "seagrass_pi.h"
#include "seagrassgui.h"

#include "wx/dir.h"
#include <cmath>
#include <list>
#include <wx/progdlg.h>
#include <wx/wx.h>

#ifdef __ANseagrassOID__
wxWindow* g_Window;
#endif

#define FAIL(X)                                                                \
    do {                                                                       \
        error = X;                                                             \
        goto failed;                                                           \
    } while (0)

Dlg::Dlg(wxWindow* parent, seagrass_pi* ppi)
    : m_Dialog(parent)
{
    this->Fit();
    dbg = false; // for debug output set to true

    pPlugIn = ppi;
    pParent = parent;

    pPlugIn->m_bShowseagrass = false;

#ifdef __ANseagrassOID__

    m_binResize = false;

    g_Window = this;
    GetHandle()->setStyleSheet(qtStyleSheet);
    Connect(wxEVT_LEFT_UP, wxMouseEventHandler(Dlg::OnMouseEvent));

    Connect(wxEVT_MOTION, wxMouseEventHandler(Dlg::OnMouseEvent));

#endif
}

Dlg::~Dlg() { }

#ifdef __ANseagrassOID__
wxPoint g_startPos;
wxPoint g_startMouse;
wxPoint g_mouse_pos_screen;

void Dlg::OnPopupClick(wxCommandEvent& evt)
{
    switch (evt.GetId()) {
    case ID_SOMETHING:
        m_binResize = true;
        break;
        // case ID_SOMETHING_ELSE:
        //   break;
    }
}

void Dlg::OnDLeftClick(wxMouseEvent& event)
{
    wxMenu mnu;
    mnu.Append(ID_SOMETHING, "Resize...");
    // mnu.Append(ID_SOMETHING_ELSE, "Do something else");
    mnu.Connect(wxEVT_COMMAND_MENU_SELECTED,
        wxCommandEventHandler(Dlg::OnPopupClick), NULL, this);
    PopupMenu(&mnu);
}

void Dlg::OnMouseEvent(wxMouseEvent& event)
{
    if (m_binResize) {
        wxSize currentSize = g_Window->GetSize();
        wxSize par_size = GetOCPNCanvasWindow()->GetClientSize();
        wxPoint par_pos = g_Window->GetPosition();
        if (event.LeftDown()) {
            m_resizeStartPoint = event.GetPosition();
            m_resizeStartSize = currentSize;
            m_binResize2 = true;
        }

        if (m_binResize2) {
            if (event.Dragging()) {
                wxPoint p = event.GetPosition();

                wxSize dragSize = m_resizeStartSize;

                dragSize.y = p.y; //  - m_resizeStartPoint.y;
                dragSize.x = p.x; //  - m_resizeStartPoint.x;
                ;
                /*
                if ((par_pos.y + dragSize.y) > par_size.y)
                    dragSize.y = par_size.y - par_pos.y;

                if ((par_pos.x + dragSize.x) > par_size.x)
                    dragSize.x = par_size.x - par_pos.x;
        */
                // not too small
                dragSize.x = wxMax(dragSize.x, 150);
                dragSize.y = wxMax(dragSize.y, 150);

                int x = wxMax(0, m_resizeStartPoint.x);
                int y = wxMax(0, m_resizeStartPoint.y);
                int xmax = ::wxGetDisplaySize().x - GetSize().x;
                x = wxMin(x, xmax);
                int ymax = ::wxGetDisplaySize().y
                    - (GetSize().y); // Some fluff at the bottom
                y = wxMin(y, ymax);

                g_Window->Move(x, y);
            }
            if (event.LeftUp()) {
                wxPoint p = event.GetPosition();

                wxSize dragSize = m_resizeStartSize;

                dragSize.y = p.y;
                dragSize.x = p.x;

                // not too small
                dragSize.x = wxMax(dragSize.x, 150);
                dragSize.y = wxMax(dragSize.y, 150);

                g_Window->SetSize(dragSize);

                m_binResize = false;
                m_binResize2 = false;
            }
        }
    } else {
        if (event.Dragging()) {
            m_resizeStartPoint = event.GetPosition();
            int x = wxMax(0, m_resizeStartPoint.x);
            int y = wxMax(0, m_resizeStartPoint.y);
            int xmax = ::wxGetDisplaySize().x - GetSize().x;
            x = wxMin(x, xmax);
            int ymax = ::wxGetDisplaySize().y
                - (GetSize().y); // Some fluff at the bottom
            y = wxMin(y, ymax);

            g_Window->Move(x, y);
        }
    }
}

void Dlg::sizeplus(wxCommandEvent& event)
{
    wxSize currentSize = g_Window->GetSize();
    wxSize plusSize;

    plusSize.x = abs(currentSize.x * 1.2);
    plusSize.y = abs(currentSize.y * 1.2);

    // not too large
    int xmax = ::wxGetDisplaySize().x - GetSize().x;
    plusSize.x = wxMin(plusSize.x, xmax);
    int ymax
        = ::wxGetDisplaySize().y - (GetSize().y); // Some fluff at the bottom
    plusSize.y = wxMin(plusSize.y, ymax);

    g_Window->SetSize(plusSize);
}

void Dlg::sizeminus(wxCommandEvent& event)
{
    wxSize currentSize = g_Window->GetSize();
    wxSize minusSize;

    minusSize.x = currentSize.x - 50;
    minusSize.y = currentSize.y - 50;

    g_Window->SetSize(minusSize);
}

#endif // End of Android functions for move/resize

void Dlg::Addpoint(TiXmlElement* Route, wxString ptlat, wxString ptlon,
    wxString ptname, wxString ptsym, wxString pttype)
{
    // add point
    TiXmlElement* RoutePoint = new TiXmlElement("rtept");
    RoutePoint->SetAttribute("lat", ptlat.mb_str());
    RoutePoint->SetAttribute("lon", ptlon.mb_str());

    TiXmlElement* Name = new TiXmlElement("name");
    TiXmlText* text = new TiXmlText(ptname.mb_str());
    RoutePoint->LinkEndChild(Name);
    Name->LinkEndChild(text);

    TiXmlElement* Symbol = new TiXmlElement("sym");
    TiXmlText* text1 = new TiXmlText(ptsym.mb_str());
    RoutePoint->LinkEndChild(Symbol);
    Symbol->LinkEndChild(text1);

    TiXmlElement* Type = new TiXmlElement("type");
    TiXmlText* text2 = new TiXmlText(pttype.mb_str());
    RoutePoint->LinkEndChild(Type);
    Type->LinkEndChild(text2);
    Route->LinkEndChild(RoutePoint);
    // done adding point
}

void Dlg::OnPSGPX(wxCommandEvent& event) { OpenXML(); }

void Dlg::OnClose(wxCloseEvent& event) { pPlugIn->OnseagrassDialogClose(); }

bool Dlg::OpenXML()
{
    Position my_position;

    my_positions.clear();

    int response = wxID_CANCEL;
    int my_count = 0;

    wxString CurrentDocPath;
    wxString filename;

    wxString px, py;
    wxString inters = "";

    wxString s = "/";
    const char* pName = "seagrass_pi";
    wxString m_gpx_path = GetPluginDataDir(pName) + s + "data" + s;

    // wxMessageBox(m_gpx_path);

    wxFileDialog* OpenDialog = new wxFileDialog(this,
        _("Import GPX Route file"), m_gpx_path, wxT(""),
        wxT("GPX files (*.gpx)|*.gpx|All files (*.*)|*.*"), wxFD_OPEN);
    if (OpenDialog->ShowModal()
        == wxID_OK) { // if the user click "Open" instead of "Cancel"

        if (OpenDialog->GetPath() != wxEmptyString) {
            filename = OpenDialog->GetPath();
            // wxMessageBox(filename);
        } else {
            wxMessageBox(_("No file selected"));
            return false;
        }
    }

    // Clean up after ourselves
    OpenDialog->Destroy();

    TiXmlDocument doc;
    wxString error;

    if (!doc.LoadFile(filename.mb_str())) {
        FAIL(_("Failed to load file: ") + filename);

    } else {
        TiXmlElement* root = doc.RootElement();

        if (!strcmp(root->Value(), "trk"))
            FAIL(_("trk Invalid xml file"));

        int count = 0;
        for (TiXmlElement* e = root->FirstChildElement(); e;
             e = e->NextSiblingElement())
            count++;

        int i = 0;
        int n = 0;
        Point my_point;
        my_point.x = 999;
        my_point.y = 999;
        m_points.clear();

        for (TiXmlElement* e = root->FirstChildElement(); e;
             e = e->NextSiblingElement(), i++) {

            // wxMessageBox(e->Value());
            if (!strcmp(e->Value(), "trk")) {

                for (TiXmlElement* f = e->FirstChildElement(); f;
                     f = f->NextSiblingElement()) {

                    if (!strcmp(f->Value(), "trkseg")) {

                        for (TiXmlElement* g = f->FirstChildElement(); g;
                             g = g->NextSiblingElement()) {

                            // wxMessageBox(g->Value());

                            if (!strcmp(g->Value(), "trkpt")) {

                                wxString rte_lat
                                    = wxString::FromUTF8(g->Attribute("lat"));
                                wxString rte_lon
                                    = wxString::FromUTF8(g->Attribute("lon"));

                                // wxMessageBox(rte_lat);
                                double value = 666;
                                rte_lat.ToDouble(&value);
                                my_point.y = value;
                                rte_lon.ToDouble(&value);
                                my_point.x = value;

                                // wxString inters = wxString::Format("%f",
                                // my_point.x); wxMessageBox(inters);

                                m_points.push_back(my_point);
                            }
                        }
                    }
                }
            }
        }           
    }
    double myval = 0;

    py = m_lat->GetValue();
    if (!py.ToDouble(&myval)) { /* error! */
    };
    point.y = myval;

    //inters = wxString::Format("%f", point.y);
    //wxMessageBox(inters);

    px = m_lon->GetValue();
    if (!px.ToDouble(&myval)) { /* error! */
    };
    point.x = myval;

    //inters = wxString::Format("%f", point.x);
    //wxMessageBox(inters);

    // point.x = 4.125299;
    // point.y = 50.347776;

    bool is_inside = pointInPolygon(point, m_points);
    if (is_inside)
        wxMessageBox("inside");
    else
        wxMessageBox("outside");

    return true;

failed:

    wxMessageDialog mdlg(this, error, _("seagrass"), wxOK | wxICON_ERROR);
    mdlg.ShowModal();

    return false;
}

bool Dlg::pointInPolygon(Point& p, vector<Point>& polygon)
{
    int c = 0;
    Point p1 = p;
    int n = polygon.size(); // 4
    vector<Point>::iterator it;

    Point p0;
    p0.x = 0;
    p0.y = 0;
   
    p0 = m_points[n-1];

    for (it = polygon.begin(); it != polygon.end(); ++it) {
        if (p0.y != it->y) {
            // scale latitude of $test_point so that $p0 maps to 0 and $p1 to 1:
            double interp = (p.y - p0.y) / (it->y - p0.y);
            // does the edge intersect the latitude of $test_point?
            // (note: use >= and < to avoid double-counting exact endpoint hits)
            if (interp >= 0 && interp < 1) {
                // longitude of the edge at the latitude of the test point:
                // (could use fancy spherical interpolation here, but for small
                // regions linear interpolation should be fine)
                double longi = interp * it->x + (1 - interp) * p0.x;
                // is the intersection east of the test point?
                if (longi < p.x) {
                    // if so, count it:
                    c++;
                }
            }
        }
        p0 = *it;
    }
    // if the number of edges we passed through is even, then it's not in the
    // poly.
    return c % 2 != 0;
}
