#ifndef VEC_FOUR_H
#define VEC_FOUR_H



//4d vector with integer values
class Vec4{
 public:
  int x;
  int y;
  int z;
  int w;
  //constructors
  Vec4(int x, int y, int z);
  Vec4(int x, int y, int z, int w);
  // vector addition
  friend Vec4 operator+( Vec4 vec1,  Vec4 vec2);
  //and subtractio
  friend Vec4 operator-(Vec4 vec1, Vec4 vec2);

  //normalizes w to 1 then takes the cross product over x,y,z
  Vec4 cross( Vec4 vec2) const;
  // scales down by w
  void normalize_w ();
  // normalizes and takes the dot product
  int dot(Vec4 vec2) const;
  //copies
  Vec4 copy() const;
  //scale
  void scale(int f);
  //magnitude, ignoring w
  int magnitude() const;
};


//4d vector for floats
class Vec4f{
 public:
  float x;
  float y;
  float z;
  float w;
  //constructors                                                                                                                                                
  Vec4f(float x, float y, float z);
  Vec4f(float x, float y, float z, float w);
  // vector addition                                                                                                                                            
  friend Vec4f operator+( Vec4f vec1,  Vec4f vec2);

  friend Vec4f operator-(Vec4f vec1, Vec4f vec2);
  //normalizes w to 1 then takes the cross product over x,y,z                                                                                                   
  Vec4f cross( Vec4f vec2) const;
  // scales down by w
  void normalize_w ();
  // scales down by magnitude
  void normalize();

  // normalizes and takes the dot product  
  double dot(Vec4f vec2) const;
  //copies                                                                                                                                                      
  Vec4f copy() const;
  //scale         
  void scale(double f);
  //magnitude, ignoring w
  double magnitude() const;
};

#endif
