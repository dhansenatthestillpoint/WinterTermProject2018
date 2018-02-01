#include <gdkmm/general.h>
#include <cairomm/context.h>
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm/drawingarea.h>
#include <gdk/gdk.h>
#include <gdk/gdkpixbuf.h>
#include <glib.h>
#include <glibmm/main.h>
#include <stdio.h>
#include "renderer.h"

#define WIDTH 400
#define HEIGHT 400
#define FPS 60
#define TICKMS 1000/FPS

class MyArea : public Gtk::DrawingArea
{
 public:
  MyArea();
  virtual ~MyArea();
  Glib::RefPtr< Gdk::Pixbuf > pixbuf;
  Renderer * renderer;
 protected:
  //Override default signal handlers:                                            
  bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
  bool on_timeout();
};
