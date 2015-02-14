
#ifndef __DIALOGS_H__
#define __DIALOGS_H__

enum { VERSION_TEXT=10000, EPAISSEUR_TEXT, EPAISSEUR_SLIDER, COLOR_TEXT, COLOR_RADIO, TRIANGLE_LIST, BUTTON_PROP, BUTTON_DELETE, ID_PROP_TEXT, EPAISSEUR_PROP_TEXT, PROP_CTRL, PROP_SPIN};

class VersionDialog: public wxDialog {
  public:
    VersionDialog(wxWindow *parent, wxWindowID id, const wxString &title);
  
  private:
    DECLARE_EVENT_TABLE();
};

class EpaisseurDialog: public wxDialog {
  public:
    EpaisseurDialog(wxWindow *parent, wxWindowID id, const wxString &title);
    int getEpaisseur();

  private:
    DECLARE_EVENT_TABLE();
    wxSlider *epaisseurSlider;
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
    TriangleDialog(wxWindow *parent, wxWindowID id, const wxString &title);
    wxListBox * getListBox();

  private:
    DECLARE_EVENT_TABLE();
    wxListBox *listBox;
    void OnProp(wxCommandEvent& event);
};

class PropDialog: public wxDialog {
  public:
    PropDialog(wxWindow *parent, wxWindowID id, const wxString &title, const wxString &textId);
  
  private:
    DECLARE_EVENT_TABLE();
};

class FileDialog: public wxFileDialog {
  public:
    FileDialog(wxWindow* parent, const wxString& message, const wxString& defaultDir, const wxString& defaultFile, const wxString& wildcard, long style);
  
};

#endif
