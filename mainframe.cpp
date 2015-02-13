#include <stdio.h>
#include <stdlib.h>
#include <wx/wx.h>
#include <wx/accel.h>
#include <fstream>

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
  EVT_MENU(TOOLBAR_TOOLS, CMainFrame::OnTools)
  EVT_MENU(MENU_DRAW, CMainFrame::OnDraw)
END_EVENT_TABLE()

CMainFrame::CMainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame((wxFrame *)NULL, -1, title, pos, size) 
{
  epaisseurtraitcourante = 5;
  couleurcourante = new wxColour(wxT("red"));
  is_drawing = FALSE;
  num_tri = 0;
}

int CMainFrame::getEpaisseur() {
  return epaisseurtraitcourante;
}

void CMainFrame::setEpaisseur(int e) {
  epaisseurtraitcourante = e;
}

wxColour* CMainFrame::getCouleur() {
  return couleurcourante;
}

void CMainFrame::setCouleur(wxColour* c) {
  couleurcourante = c;
}

bool CMainFrame::getDrawing() {
  return epaisseurtraitcourante;
}

void CMainFrame::CreateMyToolbar() {
  m_toolbar=CreateToolBar(wxNO_BORDER | wxTB_HORIZONTAL, TOOLBAR_TOOLS);
  
  wxBitmap toolBarBitmaps[4];
  toolBarBitmaps[0] = wxBitmap(wxT("new.bmp"),wxBITMAP_TYPE_BMP);
  toolBarBitmaps[1] = wxBitmap(wxT("open.bmp"),wxBITMAP_TYPE_BMP);
  toolBarBitmaps[2] = wxBitmap(wxT("save.bmp"),wxBITMAP_TYPE_BMP);
  toolBarBitmaps[3] = wxBitmap(wxT("draw.bmp"),wxBITMAP_TYPE_BMP);

  m_toolbar->SetToolBitmapSize(wxSize(toolBarBitmaps[0].GetWidth(), toolBarBitmaps[0].GetHeight()));

  m_toolbar->AddTool(MENU_NEW, wxT("Nouveau"), toolBarBitmaps[0]);
  m_toolbar->AddTool(MENU_OPEN, wxT("Ouvrir"), toolBarBitmaps[1]);
  m_toolbar->AddTool(MENU_SAVE, wxT("Sauvegarder"), toolBarBitmaps[2]);

  m_toolbar->AddSeparator();

  m_toolbar->AddCheckTool(MENU_DRAW, wxT("Dessiner"), toolBarBitmaps[3]);

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
  FileDialog vdlg(this, wxT("Choose a file"), wxT("˜"), wxT("trian"), wxT("*.tri"), wxOPEN);
  vdlg.ShowModal();
}
void CMainFrame::OnOpen(wxCommandEvent& event) {
  FileDialog vdlg(this, wxT("Choose a file"), wxT("˜"), wxT("trian"), wxT("*.tri"), wxOPEN);
  vdlg.ShowModal();
  std::ifstream fo(vdlg.GetPath().fn_str(), std::ios::in);
}
void CMainFrame::OnSave(wxCommandEvent& event) {
  FileDialog vdlg(this, wxT("Choose a file"), wxT("˜"), wxT("trian"), wxT("*.tri"), wxSAVE|wxFD_OVERWRITE_PROMPT );
  vdlg.ShowModal();
}
void CMainFrame::OnQuit(wxCommandEvent& event) {
  Close(TRUE);
}
void CMainFrame::OnSize(wxCommandEvent& event) {
  EpaisseurDialog vdlg(this, -1, wxT("Epaisseur"));
  vdlg.ShowModal();
  this->setEpaisseur(vdlg.getEpaisseur());
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
  lb->Append(wxT("Triangle 1"));
  lb->Append(wxT("Triangle 2"));
  lb->SetSelection(1);

  vdlg.ShowModal();
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
void CMainFrame::OnTools(wxCommandEvent& event) {

}
void CMainFrame::OnDraw(wxCommandEvent& event) {
  is_drawing = !is_drawing;
}
