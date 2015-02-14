#ifndef __MAINFRAME_H__
#define __MAINFRAME_H__

#include "wx/wx.h"
#include "triangle.h"

enum { MENU_NEW, MENU_OPEN, MENU_SAVE, MENU_QUIT, MENU_SIZE, MENU_COLOR, MENU_TRIANGLE, MENU_VERSION, MENU_TOOLBAR, TOOLBAR_TOOLS, MENU_DRAW };

class CMainFrame: public wxFrame {
  public:
  	CMainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    void CreateMyToolbar();
    void ShowToolbar();
    void HideToolbar();
    bool GetVisibility();
    int getEpaisseur();
    void setEpaisseur(int e);
    wxColour* getCouleur();
    void setCouleur(wxColour* c);
    bool getDrawing();

  private:

    wxToolBar *m_toolbar;
    int epaisseurtraitcourante;
    wxColour *couleurcourante;
    bool is_drawing;
    int num_tri;
    Triangle tab_tri [5];

  	DECLARE_EVENT_TABLE();

    void OnNew(wxCommandEvent& event);
    void OnOpen(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);
    void OnQuit(wxCommandEvent& event);
    void OnSize(wxCommandEvent& event);
    void OnColor(wxCommandEvent& event);
    void OnTriangle(wxCommandEvent& event);
    void OnVersion(wxCommandEvent& event);
    void OnToolbar(wxCommandEvent& event);
    void OnTools(wxCommandEvent& event);
    void OnDraw(wxCommandEvent& event);
    void OnColor1(wxCommandEvent& event);
};

#endif
