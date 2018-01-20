#ifndef RASTER_EYES_H
#define RASTER_EYES_H

#include "vec4.h"
#include <gdk/gdkpixbuf.h>
#include "objectloader.h"

class Rasterizer{
 private:
  Glib::RefPtr< Gdk::Pixbuf > mpixbuf;
  int mrowstride;
  int mchannels;
  int mwidth;
  int mheight;


 public:
  //constructor
  Rasterizer(Glib::RefPtr< Gdk::Pixbuf > pixbuf, int rowstride, int nchannels, int width, int height ); 
  //to be called when window is resized
  void updateSize(int rowstride, int nchannels, int width, int height);
  
  void rasterize (Face face, int z);
}




#endif
