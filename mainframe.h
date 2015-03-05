#ifndef __MAINFRAME_H__
#define __MAINFRAME_H__

#include <wx/html/helpctrl.h>
#include "wx/wx.h"
#include "triangle.h"
#include "openglcanvas.h"

enum { MENU_NEW, MENU_OPEN, MENU_SAVE, MENU_QUIT, MENU_THICKNESS, MENU_COLOR, MENU_TRIANGLE, MENU_VERSION, MENU_HELP, MENU_TOOLBAR, TOOLBAR_TOOLS, MENU_DRAW, CANVAS, POPUP_PROP, POPUP_DELETE };

const int MAX_TRI = 50;

class OpenGLCanvas;

class CMainFrame: public wxFrame {
  public:
  	CMainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    void CreateMyToolbar();
    void DeleteTriangle(int i);

    Triangle tab_tri [MAX_TRI];
    int num_tri;
    int currentThickness;
    bool is_drawing;
    OpenGLCanvas *canvas;
    wxColour *currentColor;
    wxHtmlHelpController help;

  private:
    wxToolBar *m_toolbar;

  	DECLARE_EVENT_TABLE();

    void OnNew(wxCommandEvent& event);
    void OnOpen(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);
    void OnQuit(wxCommandEvent& event);
    void OnSize(wxCommandEvent& event);
    void OnColor(wxCommandEvent& event);
    void OnTriangle(wxCommandEvent& event);
    void OnVersion(wxCommandEvent& event);
    void OnHelp(wxCommandEvent& event);
    void OnToolbar(wxCommandEvent& event);
    void OnDraw(wxCommandEvent& event);

    std::string replaceSpace(wxString s);
    wxString replaceUnderscore(std::string s);
};

#endif
