#ifndef CAMERA_H
#define CAMERA_H

#include "Entity.h"

class Camera: public Entity{
  //these are private because their length should always be one.
 private:
  //camera up
  Vec4f mvertical;
  //camera right
  Vec4f mhorizontal;
  //forward
  Vec4f maim;
 public:
  double near_plane;
  double far_plane;
  double height;
  double width;
  friend bool operator==(Camera c1, Camera c2);
  
  void set_vertical(Vec4f vertical);
  void set_horizontal(Vec4f horizontal);
  void set_aim(Vec4f aim);

  Vec4f get_vertical();
  Vec4f get_horizontal();
  Vec4f get_aim();
};










#endif

