#include <iostream>
#include "wx/wx.h" 
#include "mainframe.h"
#include "dialogs.h"

class MyApp: public wxApp {
	virtual bool OnInit();
	CMainFrame *m_MainFrame;
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit() {
	m_MainFrame = new CMainFrame(wxT("Windows"), wxPoint(50,50), wxSize(450,340));

	m_MainFrame->Show(TRUE);

  wxMenuBar *menu_bar = new wxMenuBar;

  wxMenu *file_menu = new wxMenu;
  wxMenu *display_menu = new wxMenu;
  wxMenu *opt_menu = new wxMenu;
  wxMenu *help_menu = new wxMenu;

  menu_bar->Append(file_menu, wxT("File"));
  menu_bar->Append(display_menu, wxT("Display"));
  menu_bar->Append(opt_menu, wxT("Options"));
  menu_bar->Append(help_menu, wxT("Help"));

  file_menu->Append(MENU_NEW, wxT("New\tCtrl-N"));
  file_menu->AppendSeparator();
  file_menu->Append(MENU_OPEN, wxT("Open\tCtrl-O"));
  file_menu->Append(MENU_SAVE, wxT("Save\tCtrl-S"));
  file_menu->AppendSeparator();
  file_menu->Append(MENU_QUIT, wxT("Quit\tCtrl-Q"));

  opt_menu->Append(MENU_THICKNESS, wxT("Thickness"));
  opt_menu->Append(MENU_COLOR, wxT("Color"));
  opt_menu->Append(MENU_TRIANGLE, wxT("Management of triangles"));
  menu_bar->Enable(MENU_TRIANGLE,false);

  help_menu->Append(MENU_VERSION, wxT("Version"));
 
  display_menu->AppendCheckItem(MENU_TOOLBAR, wxT("Toolbar"));
  display_menu->Check(MENU_TOOLBAR,TRUE);
  
  m_MainFrame->SetMenuBar(menu_bar);

  m_MainFrame->CreateMyToolbar();

  return TRUE;
} 


