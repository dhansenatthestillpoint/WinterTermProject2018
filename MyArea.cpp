#include "MyArea.h"
#include "fractal.h"
#include <stdlib.h> 

MyArea::MyArea()
{
  //runs the timer, but I have no idea what goes on behind the scenes
  Glib::signal_timeout().connect( sigc::mem_fun(*this, &MyArea::on_timeout), TICKMS );
  //initialize pixbuf
  pixbuf = Gdk::Pixbuf::create_from_file("assets/sunrise512.png");
}

MyArea::~MyArea()
{
}

bool MyArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
  Gtk::Allocation allocation = get_allocation();
  const int width = allocation.get_width();
  const int height = allocation.get_height();


  int rowstride = pixbuf->get_rowstride();
  int nchannels = pixbuf->get_n_channels();

  //set values
  update(pixbuf, rowstride, nchannels);
  
  //pixbuf to cairo                                                             
  Gdk::Cairo::set_source_pixbuf (cr,pixbuf , 0, 0);
  //draw the cairo object                                                       
  cr->paint();


  return true;
}


bool MyArea::on_timeout()
{
  // force our program to redraw the entire clock.
  auto win = get_window();
  if (win)
    {
      Gdk::Rectangle r(0, 0, get_allocation().get_width(),
		       get_allocation().get_height());
      win->invalidate_rect(r, false);
    }
  return true;
}
