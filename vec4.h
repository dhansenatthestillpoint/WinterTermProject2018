#ifndef VEC_FOUR_H
#define VEC_FOUR_H

#include <iostream>

//4d vector with integer values
class Vec4{
 public:
  int x;
  int y;
  int z;
  int w;
  //constructors
  Vec4();
  Vec4(int x, int y, int z);
  Vec4(int x, int y, int z, int w);
  // vector addition
  friend Vec4 operator+( Vec4 vec1,  Vec4 vec2);
  //and subtractio
  friend Vec4 operator-(Vec4 vec1, Vec4 vec2);
  //scalar multiplication, not in place
  friend Vec4 operator* (Vec4 vec1, int f);
  //matrix multiplication
  friend Vec4 operator* (int matrix[4][4], Vec4 vec1);
  //euqality
  friend bool  operator==(Vec4 vec1, Vec4 vec2);

  friend bool operator!=(Vec4 vec1, Vec4 vec2);

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

  void printvector() const;
};


//4d vector for floats
class Vec4f{
 public:
  float x;
  float y;
  float z;
  float w;
  //constructors                                                                                                                                                
  Vec4f();
  Vec4f(float x, float y, float z);
  Vec4f(float x, float y, float z, float w);
  // vector addition                                                                                                                                            
  friend Vec4f operator+( Vec4f vec1,  Vec4f vec2);

  friend Vec4f operator-(Vec4f vec1, Vec4f vec2);

  //scalar multiplication, not in place                                                                                                        
  friend Vec4f operator * (Vec4f vec1, double f);

  //matrix multiplication                                                                                             
  friend Vec4f operator * (double matrix[4][4], Vec4f vec1 );

  double wrapangle(double inputangle) const;
  Vec4f addangles(Vec4f inputvec);

  friend bool operator!=(Vec4f vec1, Vec4f vec2);
  friend bool operator==(Vec4f vec1, Vec4f vec2);


  //normalizes w to 1 then takes the cross product over x,y,z                                                                                                   
  Vec4f cross( Vec4f vec2) const;
  // scales down by w
  void normalize_w ();
  // scales down by magnitude
  Vec4f normalize();

  // normalizes and takes the dot product  
  double dot(Vec4f vec2) const;
  //copies                                                                                                                                                      
  Vec4f copy() const;
  //scale         
  void scale(double f);
  //magnitude, ignoring w
  double magnitude() const;

  void printvector() const;
};

namespace vectors{
  //square matrix multiplication, of numerical type T, and size N x N.
  template<typename T, int N>  void matrix_multiply( T matr1[N][N], T matr2[N][N], T result[N][N]){
    for (int i = 0; i<N; i++){
      for (int j=0; j<N; j++){
	result[i][j]=0;
	for (int k = 0; k<N; k++){
	  result[i][j] = result[i][j] + matr1[i][k]*matr2[k][j];
	}
      }
    }
    
  }
};

#endif
