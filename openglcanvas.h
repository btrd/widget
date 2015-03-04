#ifndef __OPENGLCANVAS_H__
#define __OPENGLCANVAS_H__

#include "wx/wx.h"
#include <wx/glcanvas.h>
#include "mainframe.h"

class CMainFrame;

enum {POPUP_MANAGE, POPUP_FILE, POPUP_VALUE};

class OpenGLCanvas: public wxGLCanvas {
  public:
    OpenGLCanvas(CMainFrame *parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name);
    void Draw();
  private:
    CMainFrame *p;
    int click;
    Triangle tri;

    DECLARE_EVENT_TABLE();
    void OnPaint(wxPaintEvent& event);
    void OnSize(wxSizeEvent& event);
    void OnEraseBackground(wxEraseEvent& event);
    void OnMouseMove(wxMouseEvent& event);
    void OnLeftUp(wxMouseEvent& event);
    void OnLeftDown(wxMouseEvent& event);
    void OnRightDown(wxMouseEvent& event);
};

#endif
