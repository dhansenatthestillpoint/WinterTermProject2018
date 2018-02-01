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
  //get_Gravity returns a vector representing acceleration due to gravity. This way the mass of the thing being gravitated cancels with itself
  //F =ma, F = G m1 m2 / r^2, thus a = G m2/r^2. And since only some things make gravity, we don't have to worry about the effect of nearby ships on planetary mechanics. 
  virtual Vec4f get_Gravity(Vec4f pos) const = 0;

};
//Makes a sun with gravity and light emanating from it. 
class Sun: public CelestialBody{
 private:

  int mmass;
 public:
  Sun(Vec4f pos, Color color, int mass);
  
  Color get_Light(Vec4f pos, Vec4f angle) const override;
  Vec4f get_Gravity(Vec4f pos) const override;

};
//Planet class has a body it orbits, and and a light source it reflects/casts shadows. 
//Also works for moons and death stars
class Planet: public CelestialBody{
 private:
  CelestialBody * mLightSource;
  CelestialBody * mGravitySource;
  double mradius;

 public:
  Color get_Light(Vec4f pos, Vec4f angle) const override;
  Vec4f get_Gravity(Vec4f pos) const override;

  Planet (CelestialBody * LightSource, CelestialBody * GravitySource,Color color, int mass, Vec4f pos, double radius);
};
//aggregate class for groups of celestial bodies.
class SolarSystem: public CelestialBody{
 private:
  std::vector<CelestialBody *> bodies;
 public:
  //sums over its component bodies.
  Color get_Light(Vec4f pos, Vec4f angle) const override;
  Vec4f get_Gravity(Vec4f pos) const override;
  void add(CelestialBody * body);
  SolarSystem();
};

class ConstantLight: public CelestialBody{
 public:
  ConstantLight(Color color);
  Color get_Light(Vec4f pos, Vec4f angle) const override;
  Vec4f get_Gravity(Vec4f pos) const override;
};

#endif
