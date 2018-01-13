#include <gdkmm/general.h> 
#include <cairomm/context.h>
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm/drawingarea.h>
#include <gdk/gdk.h>
#include <gdk/gdkpixbuf.h>
#include <glib.h>
#include <stdio.h>
#define WIDTH 400
#define HEIGHT 400

class MyArea : public Gtk::DrawingArea
{
public:
  MyArea();
  virtual ~MyArea();

protected:
  //Override default signal handler:
  bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
};



MyArea::MyArea()
{
}

MyArea::~MyArea()
{
}

bool MyArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
  Gtk::Allocation allocation = get_allocation();
  const int width = allocation.get_width();
  const int height = allocation.get_height();
 

  //create pixbuf
  Glib::RefPtr< Gdk::Pixbuf > pixbuf = Gdk::Pixbuf::create_from_file("assets/sunrise.png");
  //pixbuf to cairo 
  Gdk::Cairo::set_source_pixbuf (cr,pixbuf , 0, 0);
  //draw the cairo object
  cr->paint();


  return true;
}

int main(int argc, char** argv)
{
  auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

  Gtk::Window window;
  window.set_title("poop");
  window.set_default_size(WIDTH, HEIGHT);
  MyArea area;
  window.add(area);
  area.show();

  return app->run(window);
}
