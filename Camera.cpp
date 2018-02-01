

#include "Camera.h"

Camera::Camera(Vec4f pos, Vec4f inputangle,   double nearplane, double farplane,double viewheight, double viewwidth):
  Entity (pos, Vec4f(0,0,0), inputangle, Vec4f(0,0,0)),
  near_plane(nearplane),
  far_plane(farplane),
  height(viewheight),
  width(viewwidth),
  oldangle(inputangle)
{
  
  updateangles();  
}

Camera::Camera():
  Entity (Vec4f(0,0,0), Vec4f(0,0,0), Vec4f(0,0,0), Vec4f(0,0,0)),
  near_plane(0.0),
  far_plane(0.0),
  height(0.0),
  width(0.0),
  oldangle(Vec4f(0.0,0.0,0.0))
{}

bool operator==(Camera c1, Camera c2){
  return c1.anglevector == c2.anglevector && c1.posvector == c2.posvector && c1.far_plane == c2.far_plane && c1.width == c2.width && c1.height == c2.height;
}




Vec4f Camera::get_vertical(){
    if (this->anglevector != oldangle){
      updateangles();
    }
    return maim;
  }
Vec4f Camera::get_horizontal(){
  if (this->anglevector != oldangle){
    updateangles();
  }
    return maim;
}
Vec4f Camera::get_aim(){
  if (this->anglevector != oldangle){
    updateangles();
  }
  return maim;
}

void Camera::updateangles(){
  maim = this->getheading();
  maim.normalize();
  mvertical = this->getlocalz();
  mvertical.normalize();
  mhorizontal = maim.cross(mvertical);
  oldangle = anglevector;
  
}



