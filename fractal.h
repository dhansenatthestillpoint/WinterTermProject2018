#ifndef FRACTAL_H
#define FRACTAL_H
#include <gdkmm/general.h>
#include <cairomm/context.h>
#include <gdk/gdkpixbuf.h>
#include <stdlib.h>
#include <glib.h>
#include <glibmm/main.h>
#include <gdk/gdk.h>
#define ARRSIZE 8


//sets the values of arr
void init_fractal ();


//updates arr, and pixbuf.
void update(Glib::RefPtr< Gdk::Pixbuf > pixbuf, int rowstride, int nchannels);

void addv3(guchar * result, char * a, char * b, char  * c);


#endif
