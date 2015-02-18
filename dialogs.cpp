#include <stdio.h>
#include <stdlib.h>
#include <wx/wx.h>
#include <wx/accel.h>
#include <wx/spinctrl.h>
#include <iterator>

#include "dialogs.h"
#include "triangle.h"

BEGIN_EVENT_TABLE(VersionDialog, wxDialog)
END_EVENT_TABLE ()

VersionDialog::VersionDialog(wxWindow *parent, wxWindowID id, const wxString &title) :
wxDialog( parent, id, title) {
  wxBoxSizer *item0 = new wxBoxSizer( wxVERTICAL );

  wxStaticText *item1 = new wxStaticText(this, VERSION_TEXT, wxT("Version 1.0"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );

  wxButton *item2 = new wxButton(this, wxID_OK, wxT("OK"), wxDefaultPosition);

  item0->Add( item1, 0, wxALIGN_CENTRE|wxALL, 5 );
  item0->Add( item2, 0, wxALIGN_CENTRE|wxALL, 5 );

  this->SetAutoLayout( TRUE );
  this->SetSizer( item0 );
  item0->Fit( this );
  item0->SetSizeHints( this );
}

BEGIN_EVENT_TABLE(EpaisseurDialog, wxDialog)
END_EVENT_TABLE ()

EpaisseurDialog::EpaisseurDialog(wxWindow *parent, wxWindowID id, const wxString &title) :
wxDialog( parent, id, title) {
  wxBoxSizer *item0 = new wxBoxSizer( wxVERTICAL );

  wxStaticText *item1 = new wxStaticText(this, EPAISSEUR_TEXT, wxT("Choisir l'épaisseur de trait"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );

  epaisseurSlider = new wxSlider(this, EPAISSEUR_SLIDER, 1, 1, 10, wxDefaultPosition, wxSize(200, 50), wxSL_LABELS);

  wxButton *item3 = new wxButton(this, wxID_OK, wxT("OK"), wxDefaultPosition);

  item0->Add( item1, 0, wxALIGN_CENTRE|wxALL, 5 );
  item0->Add( epaisseurSlider, 0, wxALIGN_CENTRE|wxALL, 5 );
  item0->Add( item3, 0, wxALIGN_CENTRE|wxALL, 5 );

  this->SetAutoLayout( TRUE );
  this->SetSizer( item0 );
  item0->Fit( this );
  item0->SetSizeHints( this );
}
int EpaisseurDialog::getEpaisseur() {
  return epaisseurSlider->GetValue();
}

BEGIN_EVENT_TABLE(ColorDialog, wxDialog)
END_EVENT_TABLE ()

ColorDialog::ColorDialog(wxWindow *parent, wxWindowID id, const wxString &title) :
wxDialog( parent, id, title) {
  wxBoxSizer *item0 = new wxBoxSizer( wxVERTICAL );

  wxStaticText *item1 = new wxStaticText(this, COLOR_TEXT, wxT("Choisir la couleur"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );

  wxString strs8[] = { wxT("Red"), wxT("Green"), wxT("Blue") };
  colorRadio = new wxRadioBox(this, COLOR_RADIO, wxT("Couleur"), wxDefaultPosition, wxDefaultSize, 3, strs8);

  wxButton *item3 = new wxButton(this, wxID_OK, wxT("OK"), wxDefaultPosition);

  item0->Add( item1, 0, wxALIGN_CENTRE|wxALL, 5 );
  item0->Add( colorRadio, 0, wxALIGN_CENTRE|wxALL, 5 );
  item0->Add( item3, 0, wxALIGN_CENTRE|wxALL, 5 );

  this->SetAutoLayout( TRUE );
  this->SetSizer( item0 );
  item0->Fit( this );
  item0->SetSizeHints( this );
}

wxColour* ColorDialog::getColor() {
  wxColour* c = new wxColour(colorRadio->GetStringSelection());
  return c;
}

BEGIN_EVENT_TABLE(TriangleDialog, wxDialog)
  EVT_BUTTON(BUTTON_PROP, TriangleDialog::OnProp)
  EVT_BUTTON(BUTTON_DELETE, TriangleDialog::OnDelete)
END_EVENT_TABLE ()

TriangleDialog::TriangleDialog(CMainFrame *parent, wxWindowID id, const wxString &title) :
wxDialog( parent, id, title) {
  std::copy(parent->tab_tri, parent->tab_tri+5, tab_tri);

  wxBoxSizer *item0 = new wxBoxSizer( wxHORIZONTAL );
  wxBoxSizer *item1 = new wxBoxSizer( wxVERTICAL );
  wxBoxSizer *item2 = new wxBoxSizer( wxVERTICAL );

  wxStaticText *item3 = new wxStaticText(this, COLOR_TEXT, wxT("Liste des triangles"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );

  listBox = new wxListBox(this, TRIANGLE_LIST, wxDefaultPosition, wxDefaultSize);
  listBox->SetSelection(0);

  item1->Add( item3, 0, wxALIGN_CENTRE|wxALL, 5 );
  item1->Add( listBox, 0, wxALIGN_CENTRE|wxALL, 5 );

  wxButton *item5 = new wxButton(this, BUTTON_PROP, wxT("Propriétés"), wxDefaultPosition);
  wxButton *item6 = new wxButton(this, BUTTON_DELETE, wxT("Supprimer"), wxDefaultPosition);
  wxButton *item7 = new wxButton(this, wxID_OK, wxT("OK"), wxDefaultPosition);

  item2->Add( item5, 0, wxALIGN_CENTRE|wxALL, 5 );
  item2->Add( item6, 0, wxALIGN_CENTRE|wxALL, 5 );
  item2->Add( item7, 0, wxALIGN_CENTRE|wxALL, 5 );

  item0->Add( item1, 0, wxALIGN_CENTRE|wxALL, 5 );
  item0->Add( item2, 0, wxALIGN_CENTRE|wxALL, 5 );

  this->SetAutoLayout( TRUE );
  this->SetSizer( item0 );
  item0->Fit( this );
  item0->SetSizeHints( this );
}

wxListBox* TriangleDialog::getListBox() {
  return this->listBox;
}

void TriangleDialog::OnProp(wxCommandEvent& event) {
  wxListBox* lb = this->getListBox();
  int select = 0;
  select = lb->GetSelection();
  PropDialog vdlg(this, -1, wxT("Propriétés"), select, tab_tri[select]);
  vdlg.ShowModal();
  Triangle tri = tab_tri[select];
  tri.thickness = vdlg.spin->GetValue();
  wxString t = vdlg.radio->GetStringSelection();
  tri.colour = wxColour(t);
  tab_tri[select] = tri;
}

void TriangleDialog::OnDelete(wxCommandEvent& event) {
  wxListBox* lb = this->getListBox();
  int select = 0;
  select = lb->GetSelection();
  PropDialog vdlg(this, -1, wxT("Propriétés"), select, tab_tri[select]);
  vdlg.ShowModal();
  Triangle tri = tab_tri[select];
  tri.thickness = vdlg.spin->GetValue();
  wxString t = vdlg.radio->GetStringSelection();
  tri.colour = wxColour(t);
  tab_tri[select] = tri;
}

BEGIN_EVENT_TABLE(PropDialog, wxDialog)
END_EVENT_TABLE ()

PropDialog::PropDialog(wxWindow *parent, wxWindowID id, const wxString &title, int id_tri, Triangle tri) :
wxDialog( parent, id, title) {
  wxBoxSizer *item0 = new wxBoxSizer( wxVERTICAL );
  wxBoxSizer *item1 = new wxBoxSizer( wxVERTICAL );
  wxBoxSizer *item2 = new wxBoxSizer( wxHORIZONTAL );

  wxStaticText *item3 = new wxStaticText(this, ID_PROP_TEXT, wxT("Identifiant du triangle"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );

  wxString tri_string;
  tri_string << id_tri+1;
  wxTextCtrl *item4 = new wxTextCtrl(this, PROP_CTRL, wxT("Triangle " + tri_string));
  item4->SetEditable(false);

  wxStaticText *item5 = new wxStaticText(this, EPAISSEUR_PROP_TEXT, wxT("Epaisseur du trait"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );

  spin = new wxSpinCtrl(this, PROP_SPIN, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 10, tri.thickness);

  item1->Add( item3, 0, wxALIGN_CENTRE|wxALL, 5 );
  item1->Add( item4, 0, wxALIGN_CENTRE|wxALL, 5 );
  item1->Add( item5, 0, wxALIGN_CENTRE|wxALL, 5 );
  item1->Add( spin, 0, wxALIGN_CENTRE|wxALL, 5 );

  wxString strs8[] = { wxT("Red"), wxT("Green"), wxT("Blue") };

  int select = 0;

  if (tri.colour == wxColour(wxT("red")) )
    select = 0;
  else if (tri.colour == wxColour(wxT("green")) )
    select = 1;
  else if (tri.colour == wxColour(wxT("blue")) )
    select = 2;

  radio = new wxRadioBox(this, COLOR_RADIO, wxT("Couleur"), wxDefaultPosition, wxDefaultSize, 3, strs8);
  radio->SetSelection(select);

  item2->Add( item1, 0, wxALIGN_CENTRE|wxALL, 5 );
  item2->Add( radio, 0, wxALIGN_CENTRE|wxALL, 5 );

  wxButton *item8 = new wxButton(this, wxID_OK, wxT("OK"), wxDefaultPosition);

  item0->Add( item2, 0, wxALIGN_CENTRE|wxALL, 5 );
  item0->Add( item8, 0, wxALIGN_CENTRE|wxALL, 5 );

  this->SetAutoLayout( TRUE );
  this->SetSizer( item0 );
  item0->Fit( this );
  item0->SetSizeHints( this );
}

FileDialog::FileDialog(wxWindow* parent, const wxString& message, const wxString& defaultDir, const wxString& defaultFile, const wxString& wildcard, long style) : wxFileDialog(parent, message, defaultDir, defaultFile, wildcard, style) {
}
