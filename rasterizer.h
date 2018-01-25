#ifndef RASTER_EYES_H
#define RASTER_EYES_H



#include "vec4.h"
#include "objectloader.h"
#include <string>
#include <gdkmm/general.h>
#include <cairomm/context.h>
#include <gdk/gdkpixbuf.h>
#include <stdlib.h>
#include <glib.h>
#include <glibmm/main.h>
#include <gdk/gdk.h>


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
  //Textures are hard
  void  rasterize (const Face * face, const char * texturefile, const int texwidth, const int texheight);
};




#endif
