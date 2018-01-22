#ifndef CELESTIAL_BODIES_H
#define CELESTIAL_BODIES_H


#include<functional>
#include"vec4.h"
#include <vector>
#include <algorithm>
#include <math.h>
#include "Entity.h"
//implements colors in a way that they add nicely, and colors can be blown out if overlit
class Color{
 private:
  int r;
  int b;
  int g;
 public:
  friend Color operator+(Color c1, Color c2);
  unsigned char r() const;
  unsigned char b() const;
  unsigned char g() const;
  //input normal rbg vals
  Color (unsigned char r, unsigned char b, unsigned char g);
  //same as above if useSquareRoots = true, else input is rbg vals squared.
  Color (int r, int b, int g, bool useSquareRoots=true);
};

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
