#ifndef RENDERMENSCH_H
#define RENDERMENSCH_H

//holy includes batman
#include "vec4.h"
#include "objectloader.h"
#include "rasterizer.h"
#include <algorithm>
#include "Entity.h"
#include "Camera.h"
#include <vector>
#include "light_and_gravity.h"
#include <gdkmm/general.h>
#include <cairomm/context.h>
#include <gdk/gdkpixbuf.h>
#include <glib.h>
#include <glibmm/main.h>
#include <gdk/gdk.h>
#include <unordered_map>
#define ARRSIZE 8



//allows runtime generation of comparators, so that sorting by distance to camera is possible.
class z_cmp{
 private:
  Vec4f mcamera_pos;
 public:
  z_cmp(Vec4f camera_pos);
  bool operator()(Face * f1, Face * f2);
};



class Renderer{
 private:
  Glib::RefPtr< Gdk::Pixbuf > mpixbuf;
  int mrowstride;
  int mchannels;
  int mwidth;
  int mheight;
  CelestialBody * light;
  Camera * camera;
  Camera oldcamera;
  Rasterizer * rasterizer;
  //big ol array things are stored into
  std::vector<Vec4f> * all_v;
  std::vector<Vec4f> * all_vn;
  std::vector<Face *> * all_f;
  //some kind of model updates this every tick
  std::vector<Entity *> * allEntities;


  double transform_matrix[4][4];
 public:
  //update size
  void set_pixbuf ( Glib::RefPtr< Gdk::Pixbuf > pixbuf, int rowstride, int nchannels, int width, int height);
  
  //main loop
  void render(double time =0.0);


  //constructor. Should be called exactly once. (unless you got a multiplayer game going?)
  Renderer(std::vector<Entity * > * entities, Camera * incamera, CelestialBody * solar_system );

  //destroy
  ~Renderer();

};




#endif
