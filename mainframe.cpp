#include <stdio.h>
#include <stdlib.h>
#include <wx/wx.h>
//#include <wx/accel.h>
#include <fstream>
//#include <sstream>
#include "mainframe.h"
#include "dialogs.h"

BEGIN_EVENT_TABLE(CMainFrame, wxFrame)
  EVT_MENU(MENU_NEW, CMainFrame::OnNew)
  EVT_MENU(MENU_OPEN, CMainFrame::OnOpen)
  EVT_MENU(MENU_SAVE, CMainFrame::OnSave)
  EVT_MENU(MENU_QUIT, CMainFrame::OnQuit)
  EVT_MENU(MENU_SIZE, CMainFrame::OnSize)
  EVT_MENU(MENU_COLOR, CMainFrame::OnColor)
  EVT_MENU(MENU_TRIANGLE, CMainFrame::OnTriangle)
  EVT_MENU(MENU_VERSION, CMainFrame::OnVersion)
  EVT_MENU(MENU_TOOLBAR, CMainFrame::OnToolbar)
  EVT_MENU(MENU_DRAW, CMainFrame::OnDraw)
END_EVENT_TABLE()

CMainFrame::CMainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame((wxFrame *)NULL, -1, title, pos, size) {
  currentThickness = 5;
  currentColor = new wxColour(wxT("red"));
  is_drawing = FALSE;
  num_tri = 0;
  canvas = new OpenGLCanvas(this, CANVAS, wxDefaultPosition, wxDefaultSize, 0, wxT("GLCanvas") );
}

int CMainFrame::getThickness() {
  return currentThickness;
}

void CMainFrame::setThickness(int e) {
  currentThickness = e;
}

wxColour* CMainFrame::getCouleur() {
  return currentColor;
}

void CMainFrame::setCouleur(wxColour* c) {
  currentColor = c;
}

bool CMainFrame::getDrawing() {
  return currentThickness;
}

void CMainFrame::CreateMyToolbar() {
  m_toolbar=CreateToolBar(wxNO_BORDER | wxTB_HORIZONTAL, TOOLBAR_TOOLS);
  
  wxBitmap toolBarBitmaps[4];
  toolBarBitmaps[0] = wxBitmap(wxT("new.bmp"),wxBITMAP_TYPE_BMP);
  toolBarBitmaps[1] = wxBitmap(wxT("open.bmp"),wxBITMAP_TYPE_BMP);
  toolBarBitmaps[2] = wxBitmap(wxT("save.bmp"),wxBITMAP_TYPE_BMP);
  toolBarBitmaps[3] = wxBitmap(wxT("draw.bmp"),wxBITMAP_TYPE_BMP);

  m_toolbar->SetToolBitmapSize(wxSize(toolBarBitmaps[0].GetWidth(), toolBarBitmaps[0].GetHeight()));

  m_toolbar->AddTool(MENU_NEW, wxT("New"), toolBarBitmaps[0]);
  m_toolbar->AddTool(MENU_OPEN, wxT("Open"), toolBarBitmaps[1]);
  m_toolbar->AddTool(MENU_SAVE, wxT("Save"), toolBarBitmaps[2]);

  m_toolbar->AddSeparator();

  m_toolbar->AddCheckTool(MENU_DRAW, wxT("Draw"), toolBarBitmaps[3]);

  m_toolbar->Realize();
  SetToolBar(m_toolbar);
}

void CMainFrame::ShowToolbar() {
  m_toolbar->Show();
}

void CMainFrame::HideToolbar() {
  m_toolbar->Hide();
}
bool CMainFrame::GetVisibility() {
  return m_toolbar->IsShownOnScreen();
}

void CMainFrame::OnNew(wxCommandEvent& event) {
  num_tri = 0;
  wxMenuBar* menu_bar = this->GetMenuBar();
  menu_bar->Enable(MENU_TRIANGLE,false);
}
void CMainFrame::OnOpen(wxCommandEvent& event) {
  FileDialog vdlg(this, wxT("Select a file"), wxT(""), wxT("trian.tri"), wxT("*.tri"), wxOPEN);
  vdlg.ShowModal();
  std::ifstream fo(vdlg.GetPath().fn_str(), std::ios::in);
  if (!fo) {
    wxString errormsg, caption;
    errormsg.Printf(wxT("Unable to open file"));
    errormsg.Append(vdlg.GetPath());
    caption.Printf(wxT("Erreur"));
    wxMessageDialog msg(this, errormsg, caption, wxOK | wxCENTRE | wxICON_ERROR);
    msg.ShowModal();
    return ;
  }
  fo >> num_tri;

  for (int i = 0; i < num_tri; ++i) {
    Triangle tri;

    std::string tmp;
    fo >> tmp;
    tri.name = wxString::FromUTF8(tmp.c_str());
    fo >> tri.p1.x >> tri.p1.y >> tri.p2.x >> tri.p2.y >> tri.p3.x >> tri.p3.y;
    int r, g, b;
    fo >> r >> g >> b;
    tri.colour = wxColour(r, g, b);

    fo >> tri.thickness;

    tab_tri[i] = tri;
  }
  if (num_tri > 0) {
    wxMenuBar* menu_bar = this->GetMenuBar();
    menu_bar->Enable(MENU_TRIANGLE,true);
  }
}
void CMainFrame::OnSave(wxCommandEvent& event) {
  FileDialog vdlg(this, wxT("Save file"), wxT("˜"), wxT("trian.tri"), wxT("*.tri"), wxSAVE|wxFD_OVERWRITE_PROMPT );
  vdlg.ShowModal();
  std::ofstream fs(vdlg.GetPath().fn_str(), std::ios::out);

  if (!fs) {
    wxString errormsg, caption;
    errormsg.Printf(wxT("Unable to save file "));
    errormsg.Append(vdlg.GetPath());
    caption.Printf(wxT("Erreur"));
    wxMessageDialog msg(this, errormsg, caption, wxOK | wxCENTRE | wxICON_ERROR);
    msg.ShowModal();
    return ;
  }

  fs << num_tri << std::endl << std::endl;
  for (int i = 0; i < num_tri; ++i) {
    Triangle tri = tab_tri[i];

    fs << tri.name.mb_str() << std::endl;
    fs << tri.p1.x << " " << tri.p1.y << " " << tri.p2.x << " " << tri.p2.y << " " << tri.p3.x << " " << tri.p3.y << std::endl;
    fs << (int)tri.colour.Red() << " " << (int)tri.colour.Green() << " " << (int)tri.colour.Blue() << std::endl;
    fs << tri.thickness << std::endl << std::endl;
  }

}
void CMainFrame::OnQuit(wxCommandEvent& event) {
  Close(TRUE);
}
void CMainFrame::OnSize(wxCommandEvent& event) {
  ThicknessDialog vdlg(this, -1, wxT("Thickness"));
  vdlg.ShowModal();
  this->setThickness(vdlg.getThickness());
}
void CMainFrame::OnColor(wxCommandEvent& event) {
  ColorDialog vdlg(this, -1, wxT("Couleur"));
  vdlg.ShowModal();
  this->setCouleur(vdlg.getColor());
}
void CMainFrame::OnTriangle(wxCommandEvent& event) {
  TriangleDialog vdlg(this, -1, wxT("Triangle"));

  wxListBox * lb = vdlg.getListBox();

  lb->Clear();

  for (int i = 0; i < num_tri; ++i) {
    wxString chi;
    chi << i+1;
    lb->Append(tab_tri[i].name);
  }
  vdlg.ShowModal();
  if (num_tri == 0) {
    wxMenuBar* menu_bar = this->GetMenuBar();
    menu_bar->Enable(MENU_TRIANGLE,false);
  }
}
void CMainFrame::OnVersion(wxCommandEvent& event) {
  VersionDialog vdlg(this, -1, wxT("Version"));
  vdlg.ShowModal();
}
void CMainFrame::OnToolbar(wxCommandEvent& event) {
  if (GetVisibility()) {
    HideToolbar();
  } else {
    ShowToolbar();
  }
}
void CMainFrame::OnDraw(wxCommandEvent& event) {
  is_drawing = !is_drawing;
}

void CMainFrame::DeleteTriangle(int i) {
  std::copy(tab_tri + i + 1, tab_tri + num_tri, tab_tri + i);
  num_tri--;
}