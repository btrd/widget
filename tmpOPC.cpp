#include "wx/wx.h"
#include <wx/glcanvas.h>
#include "openglcanvas.h"
#include "GL/gl.h"
//#include <GL/glut.h>
#include "GL/freeglut.h"
#include <wx/accel.h>
#include "mainframe.h"
#include <wx/colour.h>

BEGIN_EVENT_TABLE(OpenGLCanvas, wxGLCanvas)

EVT_PAINT(OpenGLCanvas::OnPaint)
EVT_SIZE(OpenGLCanvas::OnSize)
EVT_ERASE_BACKGROUND(OpenGLCanvas::OnEraseBackground)

EVT_MOTION(OpenGLCanvas::OnMouseMove)
EVT_LEFT_DOWN(OpenGLCanvas::OnLeftDown)
EVT_LEFT_UP(OpenGLCanvas::OnLeftUp)
EVT_RIGHT_DOWN(OpenGLCanvas::OnRightDown)

END_EVENT_TABLE ()

using namespace std;

OpenGLCanvas::OpenGLCanvas(wxWindow *parent, wxWindowID id,const wxPoint& pos, const wxSize& size,long style, const wxString& name): wxGLCanvas(parent, id, pos, size, style, name)
{
  m_parent=(CMainFrame*)parent;
  moment=0;
}

OpenGLCanvas::~OpenGLCanvas(void)
{

}

void OpenGLCanvas::OnPaint(wxPaintEvent& event)
{
  wxPaintDC dc(this);
  SetCurrent();

  //instructions dans Draw()
  Draw();
  SwapBuffers();
}

void OpenGLCanvas::OnSize(wxSizeEvent& event)
{
  wxGLCanvas::OnSize(event);
  int w, h;

  GetClientSize(&w, &h);

  glViewport(0, 0, (GLint) w, (GLint) h);
}

void OpenGLCanvas::OnEraseBackground(wxEraseEvent& event)
{

}

void OpenGLCanvas::Draw()
{
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  int w, h;
  GetClientSize(&w, &h);
  //cout <<w<<" "<<h<<endl;
  glOrtho(-w/2., w/2., -h/2., h/2., -1., 3.);

  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();

  glClearColor( .3f, .4f, .6f, 1 );
  glClear( GL_COLOR_BUFFER_BIT);

  //cout<<"drawing triangles"<<endl;

  for(int i=0;i<m_parent->num_tri;i++)
  {
    glBegin(GL_TRIANGLES);
    cout<<"triangle "<<i<<endl;
    // triangle plein

    glColor3d((double)m_parent->tab_tri[i].colour->Red(),(double)m_parent->tab_tri[i].colour->Green(),(double)m_parent->tab_tri[i].colour->Blue()); // the color
    glVertex2i(m_parent->tab_tri[i].p1.x,m_parent->tab_tri[i].p1.y);
    glVertex2i(m_parent->tab_tri[i].p2.x,m_parent->tab_tri[i].p2.y);
    glVertex2i(m_parent->tab_tri[i].p3.x,m_parent->tab_tri[i].p3.y);
    glEnd();

    glLineWidth(m_parent->tab_tri[i].thickness);
    glBegin(GL_LINE_LOOP);
    // triangle vide
    glColor3d(0,0,0); // black
    glVertex2i(m_parent->tab_tri[i].p1.x,m_parent->tab_tri[i].p1.y);
    glVertex2i(m_parent->tab_tri[i].p2.x,m_parent->tab_tri[i].p2.y);
    glVertex2i(m_parent->tab_tri[i].p3.x,m_parent->tab_tri[i].p3.y);
    glEnd();
  }
  glFlush();
}

void OpenGLCanvas::OnMouseMove(wxMouseEvent& event)
{
  if(m_parent->is_drawing)
  {
    /*glClearColor( .3f, .4f, .6f, 1 );
    glClear( GL_COLOR_BUFFER_BIT);
    cout<<"draw"<<endl;*/
    Draw();
    int w, h;
    GetClientSize(&w, &h);

    //cout<<"mouse moving"<<endl;
    /*if(moment==0) // setting center
    {
      glMatrixMode( GL_PROJECTION );
      glLoadIdentity();
      int w, h;
      GetClientSize(&w, &h);
      int c_w,c_h;
      c_w=event.GetX();
      c_h=event.GetY();
      glOrtho(0, w, h, 0, -1., 3.);
      //glOrtho(-c_w, w-c_w, -h, h-c_h, -1., 3.);
      //glOrtho(-w/2., w/2., -h/2., h/2., -1., 3.);

      glMatrixMode( GL_MODELVIEW );
      glLoadIdentity();
    }*/
    if(moment==1) // 1 point présent
    {
      cout<<"moment 1"<<endl;
      glLineWidth(m_parent->epaisseurtraitcourante);
      glBegin(GL_LINES);
      glColor3i(0,0,0);
      glVertex2i(tr.p1.x,tr.p1.y);
      glVertex2i(event.GetX()-w/2,-event.GetY()+h/2);
      glEnd();
    }
    else if(moment==2) // 2 points présents
    {
      cout<<"moment 2 "<<(int)m_parent->couleurcourante.Red()<<(int)m_parent->couleurcourante.Green()<<(int)m_parent->couleurcourante.Blue()<<endl;
      glLineWidth(m_parent->epaisseurtraitcourante);
      glBegin(GL_TRIANGLES);
      glColor3d((double)m_parent->couleurcourante.Red(),(double)m_parent->couleurcourante.Green(),(double)m_parent->couleurcourante.Blue());
      glVertex2i(tr.p1.x,tr.p1.y);
      glVertex2i(tr.p2.x,tr.p2.y);
      glVertex2i(event.GetX()-w/2,-event.GetY()+h/2);
      glEnd();

      glLineWidth(m_parent->epaisseurtraitcourante);
      glBegin(GL_LINE_LOOP);
      glColor3i(0,0,0);
      glVertex2i(tr.p1.x,tr.p1.y);
      glVertex2i(tr.p2.x,tr.p2.y);
      glVertex2i(event.GetX()-w/2,-event.GetY()+h/2);
      glEnd();
    }
    glFlush();
  }
}

void OpenGLCanvas::OnLeftUp(wxMouseEvent& event)
{
  if(m_parent->is_drawing)
  {
    moment++;
    cout<<"left up : "<<event.GetX()<<" "<<event.GetY()<<" moment "<<moment<<endl;

    int w, h;
    GetClientSize(&w, &h);

    if(moment==1)
    {
      tr.p1.x=event.GetX()-w/2;
      tr.p1.y=-event.GetY()+h/2;
      tr.thickness=m_parent->epaisseurtraitcourante;
      tr.colour=new wxColour((int)m_parent->couleurcourante.Red(),(int)m_parent->couleurcourante.Green(),(int)m_parent->couleurcourante.Blue(),wxALPHA_OPAQUE);
    }
    else if(moment==2)
    {
      tr.p2.x=event.GetX()-w/2;
      tr.p2.y=-event.GetY()+h/2;
    }
    else if(moment==3)
    {
      tr.p3.x=event.GetX()-w/2;
      tr.p3.y=-event.GetY()+h/2;

      if(m_parent->num_tri<5)
      {
        m_parent->tab_tri[m_parent->num_tri].p1=tr.p1;
        m_parent->tab_tri[m_parent->num_tri].p2=tr.p2;
        m_parent->tab_tri[m_parent->num_tri].p3=tr.p3;
        m_parent->tab_tri[m_parent->num_tri].colour=tr.colour;
        m_parent->tab_tri[m_parent->num_tri].thickness=tr.thickness;
        m_parent-> num_tri++;

        if(m_parent->num_tri>0)
        {
          m_parent->menu_bar->Enable(MENU_GESTION,true);
        }
        m_parent->canvas->Draw();
      }
      else
      {
        cout<<"tableau full ! not saving"<<endl;
      }
      moment=0;
    }
  }
}

void OpenGLCanvas::OnLeftDown(wxMouseEvent& event)
{
  if(m_parent->is_drawing)
  {
    //cout<<"left down"<<endl;
  }
}

void OpenGLCanvas::OnRightDown(wxMouseEvent& event)
{
  wxMenu popupmenu;
  wxMenu* fichier= new wxMenu;
  wxMenu* gestion= new wxMenu;
  wxMenu* valeurs= new wxMenu;

  fichier->Append(MENU_OPEN, wxT("Ouvrir fichier"));
  fichier->Append(MENU_SAVE, wxT("Sauvegarder fichier"));

  gestion->Append(MENU_GESTION, wxT("Gestion des triangles"));

  valeurs->Append(MENU_COLOR, wxT("Couleurs courantes"));
  valeurs->Append(MENU_EPAISSEUR, wxT("Epaisseur courante"));

  popupmenu.Append(POPUP_FICHIER, wxT("Fichier"), fichier);
  popupmenu.Append(POPUP_GESTION, wxT("Gestion"), gestion);
  popupmenu.Append(POPUP_VALEURS, wxT("Valeurs courantes"), valeurs);

  PopupMenu( &popupmenu, event.GetX(), event.GetY() );
}