#ifndef LIGHTING_H
#define LIGHTING_H

#include<functional>
#include"vec4.h"
#include <tuple>
#include <algorithm>
#include <math.h>


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
  Color (unsigned char r, unsigned char b, unsigned char g); 
}



//Light is a magic function which takes in the position and angle of an illuminated object, and returns a luminance and color.

class Light{

 public:
  Color color;
  Color operator()(Vec4f pos, Vec4f angle) const = 0;
  Light();
  virtual ~Light();

};



class Planet{
 public:
  


}






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
  DirectionalSource(Vec4f angle, double brightness,  int r, int  b, int g);
  std::tuple<double, unsigned char *> operator()(Vec4f pos, Vec4f angle) const;
  ~DirectionalSource();
};

class UniformSource: public Light{
 private:
  double brightness;
 public:
  unsigned char * color;
  UniformSource();
  UniformSource (double brightness,  int r, int  b, int g);
  std::tuple<double, unsigned char *> operator()(Vec4f pos, Vec4f angle) const;
};

namespace light{
  const Light * add ( const Light * L1, const Light * L2);
}




#endif
  
