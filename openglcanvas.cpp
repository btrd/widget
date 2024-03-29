#include "wx/wx.h"
#include <wx/glcanvas.h>
#include "openglcanvas.h"
#include "GL/gl.h"
#include "mainframe.h"
#include "triangle.h"
#include "dialogs.h"

BEGIN_EVENT_TABLE(OpenGLCanvas, wxGLCanvas)
  EVT_PAINT(OpenGLCanvas::OnPaint)
  EVT_SIZE(OpenGLCanvas::OnSize)
  EVT_ERASE_BACKGROUND(OpenGLCanvas::OnEraseBackground)

  EVT_MOTION(OpenGLCanvas::OnMouseMove)
  EVT_LEFT_DOWN(OpenGLCanvas::OnLeftDown)
  EVT_LEFT_UP(OpenGLCanvas::OnLeftUp)
  EVT_RIGHT_DOWN(OpenGLCanvas::OnRightDown)
  EVT_MENU(POPUP_PROP, OpenGLCanvas::OnProp)
  EVT_MENU(POPUP_DELETE, OpenGLCanvas::OnDelete)
END_EVENT_TABLE()

OpenGLCanvas::OpenGLCanvas(CMainFrame *parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style,const wxString& name): wxGLCanvas(parent, id, pos, size, style, name) {
  p = parent;
  click = 0;
  selectTriangle = -1;
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

    glColor3d((double)tri.colour.Red(), (double)tri.colour.Green(), (double)tri.colour.Blue());
    glVertex2i(tri.p1.x, tri.p1.y);
    glVertex2i(tri.p2.x, tri.p2.y);
    glVertex2i(tri.p3.x, tri.p3.y);
    glEnd();

    glLineWidth(tri.thickness);
    glBegin(GL_LINE_LOOP);

    glColor3d(0,0,0);
    glVertex2i(tri.p1.x,tri.p1.y);
    glVertex2i(tri.p2.x,tri.p2.y);
    glVertex2i(tri.p3.x,tri.p3.y);
    glEnd();
    SwapBuffers();
  }
  glFlush();
}

void OpenGLCanvas::OnSize( wxSizeEvent& event ) {
  wxGLCanvas::OnSize(event);
  int w, h;
  GetClientSize(&w, &h);
  //glViewport(0, 0, (GLint) w, (GLint) h);
}

void OpenGLCanvas::OnEraseBackground( wxEraseEvent& event ) {

}

void OpenGLCanvas::OnMouseMove(wxMouseEvent& event) {
  if(p->is_drawing) {
    Draw();
    int w, h;
    GetClientSize(&w, &h);

    if(click == 1) { // Premier click
      glLineWidth(p->currentThickness);
      glBegin(GL_LINES);
      glColor3i(0,0,0);
      glVertex2i(tri.p1.x,tri.p1.y);
      glVertex2i(event.GetX()-w/2,-event.GetY()+h/2);
      glEnd();
    }
    else if(click == 2) { // 2e click
      glLineWidth(p->currentThickness);
      glBegin(GL_TRIANGLES);
      glColor3d((double)p->currentColor->Red(),(double)p->currentColor->Green(),(double)p->currentColor->Blue());
      glVertex2i(tri.p1.x,tri.p1.y);
      glVertex2i(tri.p2.x,tri.p2.y);
      glVertex2i(event.GetX()-w/2,-event.GetY()+h/2);
      glEnd();

      glLineWidth(p->currentThickness);
      glBegin(GL_LINE_LOOP);
      glColor3i(0,0,0);
      glVertex2i(tri.p1.x,tri.p1.y);
      glVertex2i(tri.p2.x,tri.p2.y);
      glVertex2i(event.GetX()-w/2,-event.GetY()+h/2);
      glEnd();
    }
    glFlush();
    SwapBuffers();
  }
}

void OpenGLCanvas::OnLeftUp(wxMouseEvent& event) {
  if(p->is_drawing) {
    click++;

    int w, h;
    GetClientSize(&w, &h);

    if(click == 1) {
      tri.p1.x = event.GetX()-w/2;
      tri.p1.y =- event.GetY()+h/2;
      tri.thickness = p->currentThickness;
      tri.colour= wxColour((int)p->currentColor->Red(),(int)p->currentColor->Green(),(int)p->currentColor->Blue(),wxALPHA_OPAQUE);
    }
    else if(click == 2) {
      tri.p2.x = event.GetX()-w/2;
      tri.p2.y =- event.GetY()+h/2;
    }
    else if(click == 3) {
      tri.p3.x=event.GetX()-w/2;
      tri.p3.y=-event.GetY()+h/2;

      if(p->num_tri < MAX_TRI) {
        wxString s;
        s << p->num_tri+1;
        p->tab_tri[p->num_tri].name = wxT("Tri " + s);
        p->tab_tri[p->num_tri].p1 = tri.p1;
        p->tab_tri[p->num_tri].p2 = tri.p2;
        p->tab_tri[p->num_tri].p3 = tri.p3;
        p->tab_tri[p->num_tri].colour = tri.colour;
        p->tab_tri[p->num_tri].thickness = tri.thickness;
        p-> num_tri++;

        if(p->num_tri>0) {    
          wxMenuBar* menu_bar = p->GetMenuBar();
          menu_bar->Enable(MENU_TRIANGLE,true);
        }
        this->Draw();
      }
      else {
        std::cout << "tableau full ! not saving" << std::endl;
      }
      click=0;
    }
  }
}

void OpenGLCanvas::OnLeftDown(wxMouseEvent& event) {

}

void OpenGLCanvas::OnRightDown(wxMouseEvent& event) {
  int w, h;
  GetClientSize(&w, &h);
  int x = event.GetX()-w/2;
  int y =- event.GetY()+h/2;
  selectTriangle = InTriangle(x, y);
  if(selectTriangle > -1) {
    wxMenu popupMenu;

    popupMenu.Append(POPUP_PROP, wxT("Propriety triangle"));
    popupMenu.Append(POPUP_DELETE, wxT("Delete triangle"));

    PopupMenu( &popupMenu, event.GetX(), event.GetY() );
  } else {
    wxMenu popupMenu;

    popupMenu.Append(MENU_OPEN, wxT("Open file"));
    popupMenu.Append(MENU_SAVE, wxT("Save file"));

    popupMenu.AppendSeparator();

    popupMenu.Append(MENU_COLOR, wxT("Current colour"));
    popupMenu.Append(MENU_THICKNESS, wxT("Current thickness"));

    popupMenu.AppendSeparator();

    popupMenu.Append(MENU_TRIANGLE, wxT("Manage triangles"));

    PopupMenu( &popupMenu, event.GetX(), event.GetY() );
  }
}

int OpenGLCanvas::InTriangle(int x, int y) {
  for (int i = 0; i < p->num_tri; ++i) {
    Triangle tri = p->tab_tri[i];
    if(tri.IsPointInTriangle(x, y))
      return i;
  }
  return -1;
}

void OpenGLCanvas::OnDelete(wxCommandEvent& event) {
  if (selectTriangle > -1) {
    p->DeleteTriangle(selectTriangle);
    p->canvas->Draw();
  }
}

void OpenGLCanvas::OnProp(wxCommandEvent& event) {
  if(selectTriangle > -1) {
    PropDialog vdlg(this, -1, wxT("Properties"), selectTriangle, p->tab_tri[selectTriangle]);
    vdlg.ShowModal();
    Triangle tri = p->tab_tri[selectTriangle];
    tri.name = vdlg.text->GetValue();
    tri.thickness = vdlg.spin->GetValue();
    wxString t = vdlg.radio->GetStringSelection();
    tri.colour = wxColour(t);
    p->tab_tri[selectTriangle] = tri;
    p->canvas->Draw();
  }
}
