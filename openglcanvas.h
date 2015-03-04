#ifndef __OPENGLCANVAS_H__
#define __OPENGLCANVAS_H__

#include "wx/wx.h"
#include <wx/glcanvas.h>
#include "mainframe.h"

//enum { EVT_PAINT, EVT_SIZE, EVT_ERASE_BACKGROUND };
class CMainFrame;

class OpenGLCanvas: public wxGLCanvas {
  public:
    OpenGLCanvas(CMainFrame *parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name);
    ~OpenGLCanvas(void);
  private:
    CMainFrame *p;
    
    DECLARE_EVENT_TABLE();
    void OnPaint( wxPaintEvent& event );
    void OnSize( wxSizeEvent& event );
    void OnEraseBackground( wxEraseEvent& event );
    void Draw();
};

#endif
