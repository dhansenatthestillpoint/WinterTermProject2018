#ifndef RENDERMENSCH_H
#define RENDERMENSCH_H


#include "vec4.h"
#include <gdk/gdkpixbuf.h>
#include "objectloader.h"
#include "rasterizer.h"
#include <algorithm>
#include "Entity.h"
#include "camera.h"
#include <vector>
#include "light_and_gravity.h"

//allows runtime generation of comparators, so that sorting by distance to camera is possible.
class z_cmp{
 private:
  Vec4f mcamera_pos;
 public:
  z_cmp(Vec4f camera_pos);
  bool operator()(Face f1, Face f2);
}



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
  //big ol array things are stored into
  std::vector<Vec4f> * all_v_vn;
  std::vector<Vec4f> * all_vt;
  std::vector<Face> * all_f;
  //some kind of model updates this every tick
  std::vector<Entity> * allEntities;
  unordered_map<std:: string, ObjectMap> ObjectMap allObjectMaps;

  int transform_matrix[4][4];
 public:
  //update size
  void set_pixbuf ( Glib::RefPtr< Gdk::Pixbuf > pixbuf, int rowstride, int nchannels, int width, int height);
  
  //main loop
  void render(double time =0.0);


  //constructor. Should be called exactly once:
  Renderer(std::vector<Entity> * entities, Camera * incamera );

  //destroy
  ~Rendered();

}




#endif
