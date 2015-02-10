
#ifndef __MAINFRAME_H__
#define __MAINFRAME_H__

#include "wx/wx.h"

enum { MENU_NEW, MENU_OPEN, MENU_SAVE, MENU_QUIT, MENU_SIZE, MENU_COLOR, MENU_TRIANGLE, MENU_VERSION, MENU_TOOLBAR, TOOLBAR_TOOLS, MENU_DRAW };

class CMainFrame: public wxFrame {
  public:
  	CMainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    void CreateMyToolbar();
    void ShowToolbar();
    void HideToolbar();
    bool GetVisibility();

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
    void OnToolbar(wxCommandEvent& event);
    void OnTools(wxCommandEvent& event);
    void OnDraw(wxCommandEvent& event);
};

#endif
