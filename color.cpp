#include <algorithm>
#include"color.h"
#include <math.h>
//the lower this const is, the more blown out
#define BLOWOUT_CONST 8

//implements colors in a way that they add nicely, and colors can be blown out if overlit                                                      
//adds
Color operator+(const Color c1,const  Color c2)  {
  return Color(c1.r+c2.r, c1.g+c2.g, c1.b+c2.b, false);
}
Color operator*( const Color c1,const  Color c2) {
  c1.calculate_roots();
  c2.calculate_roots();
  return Color(c1.root_r*c2.root_r, c1.root_g*c2.root_g,c1.root_b*c2.root_b, false);
}

void Color::calculate_roots() const {
  if (root_r == -1){
    root_r = sqrt(r);
    root_g = sqrt(g);
    root_b = sqrt(b);
  }
}
unsigned char Color::get_r() const
{
  calculate_roots();
  return (unsigned char)(std::min(255, root_r + (std::max(root_b-256,0) + std::max(root_g-256, 0))/BLOWOUT_CONST));
}
unsigned char Color::get_b() const
{
  calculate_roots();
  return (unsigned char)(std::min(255, root_b + (std::max(root_r-256,0) +std::max(root_g-256, 0))/BLOWOUT_CONST));
}

unsigned char Color::get_g() const
{
  calculate_roots();
  return (unsigned char)(std::min(255, root_g + (std::max(root_r-256,0) +std::max(root_b-256, 0))/BLOWOUT_CONST));
}

  //input normal rbg vals
Color::Color (unsigned char R, unsigned char G, unsigned char B){
  r = pow((int)R,2);
  G = pow((int)G,2);
  B = pow((int)B,2);
  root_r=-1;
  root_g=-1;
  root_b=-1;
}
  //same as above if useSquareRoots = true, else input is rbg vals squared.
Color::Color (int R, int G, int B, bool useSquareRoots){
  if (useSquareRoots){
    r = pow(R,2);
    G = pow(G,2);
    B = pow(B,2);

  } else{
    r=R;
    g=G;
    b=B;
  }
  root_r=-1;
  root_g=-1;
  root_b=-1;

};



