#include "wx/wx.h"
#include <wx/glcanvas.h>
#include "openglcanvas.h"
#include "GL/gl.h"
#include "GL/freeglut.h"
#include "mainframe.h"

BEGIN_EVENT_TABLE(OpenGLCanvas, wxGLCanvas)
  EVT_PAINT(OpenGLCanvas::OnPaint)
  EVT_SIZE(OpenGLCanvas::OnSize)
  EVT_ERASE_BACKGROUND(OpenGLCanvas::OnEraseBackground)
END_EVENT_TABLE()

OpenGLCanvas::OpenGLCanvas(CMainFrame *parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style,const wxString& name): wxGLCanvas(parent, id, pos, size, style, name) {
  p = parent;
}
OpenGLCanvas::~OpenGLCanvas(void) {

}
void OpenGLCanvas::OnPaint( wxPaintEvent& event ) {
  wxPaintDC dc(this);
  SetCurrent();
  Draw();
  SwapBuffers();
}
void OpenGLCanvas::Draw() {
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  int w, h;
  GetClientSize(&w, &h);
  glOrtho(-w/2., w/2., -h/2., h/2., -1., 3.);

  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();

  glClearColor( .3f, .4f, .6f, 1 );
  glClear( GL_COLOR_BUFFER_BIT);

  for (int i = 0; i < p->num_tri; ++i) {
    Triangle tri = p->tab_tri[i];
    glBegin(GL_TRIANGLES);
    glVertex2i(tri.p1.x, tri.p1.y);

    glColor3d((double)tri.colour.Red(),(double)tri.colour.Green(),(double)tri.colour.Blue());
    glVertex2i(tri.p1.x,tri.p1.y);
    glVertex2i(tri.p2.x,tri.p2.y);
    glVertex2i(tri.p3.x,tri.p3.y);
    glEnd();

    glLineWidth(tri.thickness);
    glBegin(GL_LINE_LOOP);

    glColor3d(0,0,0);
    glVertex2i(tri.p1.x,tri.p1.y);
    glVertex2i(tri.p2.x,tri.p2.y);
    glVertex2i(tri.p3.x,tri.p3.y);
    glEnd();
  }
  glFlush();
}
void OpenGLCanvas::OnSize( wxSizeEvent& event ) {
  wxGLCanvas::OnSize(event);
  int w, h;
  GetClientSize(&w, &h);
}
void OpenGLCanvas::OnEraseBackground( wxEraseEvent& event ) {

}
