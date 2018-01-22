#ifndef CELESTIAL_BODIES_H
#define CELESTIAL_BODIES_H


#include<functional>
#include"vec4.h"
#include <vector>
#include <algorithm>
#include <math.h>
#include "Entity.h"
#include "color.h"


//Abstract class for celestial bodies
class CelestialBody: public Entity{
 private:
  Color mcolor;
 public:
  
  virtual Color get_Light(Vec4f pos, Vec4f angle) const =0;
  virtual Vec4f get_Gravity(Vec4f pos) const = 0;

}
//Makes a sun with gravity and light emanating from it. 
class Sun: public CelestialBody{
 public:
  Sun(Vec4f pos, Color color, int mass);
  
  Color get_Light(Vec4f pos, Vec4f angle) const override;
  Color get_Gravity(Vec4f pos, Vec4f angle) const override;

}
//Planet class has a body it orbits, and and a light source it reflects/casts shadows. 
//Also works for moons and death stars
class Planet: public CelestialBody{
 private:
  CelestialBody * mLightSource;
  CelestialBody * mGravitySource;
 public:
  Color get_Light(Vec4f pos, Vec4f angle) const override;
  Color get_Gravity(Vec4f pos, Vec4f angle) const override;

  Planet (CelestialBody * LightSource, CelestialBody * GravitySource,Color color, int mass);
}
//aggregate class for groups of celestial bodies.
class System: public CelestialBody{
 private:
  std::vector<CelestialBody *> bodies;
 public:
  //sums over its component bodies.
  Color get_Light(Vec4f pos, Vec4f angle) const override;
  Color get_Gravity(Vec4f pos, Vec4f angle) const override;
  void add(CelestialBody * body);
  System();
}
