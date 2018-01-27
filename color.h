#ifndef RAINBOWS_ARE_GAY_H
#define RAINBOWS_ARE_GAY_H

//implements colors in a way that they add nicely, and colors can be blown out if overlit                                                      
class Color{
 private:
  int r;
  int b;
  int g;
  mutable int root_r;
  mutable int root_b;
  mutable int root_g;
  void calculate_roots() const;
 public:
  //just straight up adds
  friend Color operator+(const Color c1, const Color c2);
  //geometric mean
  friend Color operator*(const Color c1, const Color c2);
  unsigned char get_r() const;
  unsigned char get_b() const;
  unsigned char get_g() const;
  friend Color operator*(const int scale, const Color c2);
  friend Color operator*(const Color c2 ,const int scale);
  friend Color operator/(const Color c2 ,const int scale);

 //input normal rbg vals                                                                                                                      
  Color (unsigned char R, unsigned char G, unsigned char B);
  //same as above if useSquareRoots = true, else input is rbg vals squared.                                                                    
  Color (int R, int G, int B, bool useSquareRoots=true);
  
};


#endif
