#ifndef LIGHTING_H
#define LIGHTING_H

#include<functional>
#include"vec4.h"
#include <tuple>
#include <algorithm>
#include <math.h>

#define MAX_LIGHT 1


//Light is a magic function which takes in the position and angle of an illuminated object, and returns a luminance and color.

class Light{

 public:
  unsigned char * color;
  virtual std::tuple<double, unsigned char *> operator()(Vec4f pos, Vec4f angle) const = 0;
  Light();
  virtual ~Light();

};


//adds two light sources
class AddedLight: public Light{
 private:
  const Light *  L1;
  const Light *  L2;
 public:
  unsigned char * color;

  std::tuple<double, unsigned char *> operator()(Vec4f pos, Vec4f angle) const override ;
  AddedLight( const Light * L1, const Light * L2);
  AddedLight();
  ~AddedLight();
};
// makes a point source (e.g. a lamp)

class PointSource: public Light{
 public:
  Vec4f mpos;
  unsigned char * color;
  double brightness;

  PointSource();
  PointSource(Vec4f pos, double brightness, int r, int b, int g);
  std::tuple<double, unsigned char *> operator()(Vec4f pos, Vec4f angle) const override;
  ~PointSource();
};
class DirectionalSource: public Light{
 private:
  Vec4f mdir;
  double brightness;
 public:
  unsigned char * color;
  DirectionalSource();
  DirectionalSource(Vec4f angle, double brightness, unsigned char r, unsigned char b, unsigned char g);
  std::tuple<double, unsigned char *> operator()(Vec4f pos, Vec4f angle) const;

};
/*
class UniformSource: public Light{
 private:
  double brightness;
 public:
  unsigned char * color;
 
}
*/
namespace light{
  const Light * add ( const Light * L1, const Light * L2);
}




#endif
  
