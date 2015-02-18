#ifndef __DIALOGS_H__
#define __DIALOGS_H__

#include <wx/spinctrl.h>
#include "triangle.h"
#include "mainframe.h"

enum { VERSION_TEXT=10000, THICKNESS_TEXT, THICKNESS_SLIDER, COLOR_TEXT, COLOR_RADIO, TRIANGLE_LIST, BUTTON_PROP, BUTTON_DELETE, ID_PROP_TEXT, THICKNESS_PROP_TEXT, PROP_CTRL, PROP_SPIN};

class VersionDialog: public wxDialog {
  public:
    VersionDialog(wxWindow *parent, wxWindowID id, const wxString &title);
  
  private:
    DECLARE_EVENT_TABLE();
};

class ThicknessDialog: public wxDialog {
  public:
    ThicknessDialog(wxWindow *parent, wxWindowID id, const wxString &title);
    int getThickness();

  private:
    DECLARE_EVENT_TABLE();
    wxSlider *thicknessSlider;
};

class ColorDialog: public wxDialog {
  public:
    ColorDialog(wxWindow *parent, wxWindowID id, const wxString &title);
    wxColour* getColor();
    
  private:
    DECLARE_EVENT_TABLE();
    wxRadioBox *colorRadio;
};

class TriangleDialog: public wxDialog {
  public:
    TriangleDialog(CMainFrame *parent, wxWindowID id, const wxString &title);
    wxListBox * getListBox();

  private:
    DECLARE_EVENT_TABLE();
    wxListBox *listBox;
    Triangle tab_tri [5];
    void OnProp(wxCommandEvent& event);
    void OnDelete(wxCommandEvent& event);
};

class PropDialog: public wxDialog {
  public:
    wxSpinCtrl *spin;
    wxRadioBox *radio;
    PropDialog(wxWindow *parent, wxWindowID id, const wxString &title, int id_tri, Triangle tri);
  
  private:
    DECLARE_EVENT_TABLE();
};

class FileDialog: public wxFileDialog {
  public:
    FileDialog(wxWindow* parent, const wxString& message, const wxString& defaultDir, const wxString& defaultFile, const wxString& wildcard, long style);
  
};

#endif
