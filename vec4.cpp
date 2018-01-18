#include "vec4.h"
#include <math.h>

Vec4::Vec4(int x, int y, int z){
  this->x=x;
  this->y=y;
  this->z=z;
  this->w=1;
}

Vec4::Vec4(int x, int y, int z, int w){
  this->x=x;
  this->y=y;
  this->z=z;
  this->w=w;
}


//addition
Vec4 operator+(Vec4 vec1,  Vec4 vec2){
  return Vec4(vec1.x+vec2.x, vec1.y+vec2.y, vec1.z+vec2.z, vec1.w+vec2.w);
}
//subtraction
Vec4 operator-(Vec4 vec1, Vec4 vec2){
  return Vec4(vec1.x-vec2.x, vec1.y-vec2.y, vec1.z-vec2.z, (vec1.w-vec2.w==0 ? 1: vec1.w-vec2.w) );


}

//scalar multiplication, not in place                                                                                                        
Vec4 operator * (Vec4 vec1, int f){
  return Vec4(f*vec1.x, f*vec1.y,f*vec1.z);
}

//matrix multiplication
// in a way that's hard coded, but cuts off a good bit of overhead
Vec4 operator * (int matrix[4][4], Vec4f vec1){
  return Vec4 (
		vec1.x * matrix[0][0] + vec1.y * matrix[0][1] + vec1.z * matrix[0][2] + vec1.w * matrix[0][3],
		vec1.x * matrix[1][0] + vec1.y * matrix[1][1] + vec1.z * matrix[1][2] + vec1.w * matrix[1][3],
		vec1.x * matrix[2][0] + vec1.y * matrix[2][1] + vec1.z * matrix[2][2] + vec1.w * matrix[2][3],
		vec1.x * matrix[3][0] + vec1.y * matrix[3][1] + vec1.z * matrix[3][2] + vec1.w * matrix[3][3]
		);

}



Vec4 Vec4::copy() const{
  return Vec4(this->x, this->y, this->z, this->w);
}

//normalizes w to 1 then takes the cross product over x,y,z                                                                                                   
Vec4 Vec4::cross( Vec4 vec2) const{
  Vec4 a= this->copy();
  a.normalize_w();
  Vec4 b= vec2.copy();
  b.normalize_w();
  return Vec4( a.y * b.z - a.z*b.y , a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x); 
}
// scales down by w                                                                                                                                           
void Vec4::normalize_w (){
  this->x= this->x/this->w;
  this->y= this->y/this->w;
  this->z= this->z/this->w;
}


// normalizes and takes the dot product over x, y, z.
int Vec4::dot( Vec4 vec2)const{
  Vec4 a= this->copy();
  a.normalize_w();
  Vec4 b= vec2.copy();
  b.normalize_w();
  return a.x*b.x + a.y*b.y +a.z*b.z ;
}

void Vec4::scale(int f){
  this->x = this->x*f;
  this->y = this->y*f;
  this->z = this->z*f;
}

//magintude in 3d
int  Vec4::magnitude() const{
  return (int)sqrt(pow(this->x,2) + pow(this->y,2)+pow(this->z, 2));
}






//now with floats
Vec4f::Vec4f(float x, float y, float z){
  this->x=x;
  this->y=y;
  this->z=z;
  this->w=1;
}

Vec4f::Vec4f(float x, float y, float z, float w){
  this->x=x;
  this->y=y;
  this->z=z;
  this->w=w;
}



Vec4f operator+(Vec4f vec1,  Vec4f vec2){
  return Vec4f(vec1.x+vec2.x, vec1.y+vec2.y, vec1.z+vec2.z, vec1.w+vec2.w);
}

Vec4f operator-(Vec4f vec1, Vec4f vec2){
  return Vec4f(vec1.x-vec2.x, vec1.y-vec2.y, vec1.z-vec2.z, (vec1.w-vec2.w==0 ? 1: vec1.w-vec2.w) );
}

Vec4f operator * (Vec4f vec1, double f){
  return Vec4f(f*vec1.x,f*vec1.y,f*vec1.z);
}

//matrix multiplication
Vec4f operator * ( double matrix[4][4], Vec4f vec1){
  return Vec4f (
	       
		vec1.x * matrix[0][0] + vec1.y * matrix[0][1] + vec1.z * matrix[0][2] + vec1.w * matrix[0][3],
                vec1.x * matrix[1][0] + vec1.y * matrix[1][1] + vec1.z * matrix[1][2] + vec1.w * matrix[1][3],
                vec1.x * matrix[2][0] + vec1.y * matrix[2][1] + vec1.z * matrix[2][2] + vec1.w * matrix[2][3],
                vec1.x * matrix[3][0] + vec1.y * matrix[3][1] + vec1.z * matrix[3][2] + vec1.w * matrix[3][3]
		
		);

}


//returns a copy of the current vector
Vec4f Vec4f::copy() const{
  return Vec4f(this->x, this->y, this->z, this->w);
}

//normalizes w to 1 then takes the cross product over x,y,z                                                                                                   
Vec4f Vec4f::cross( Vec4f vec2) const{
  Vec4f a= this->copy();
  a.normalize_w();
  Vec4f b= vec2.copy();
  b.normalize_w();
  return Vec4f( a.y * b.z - a.z*b.y , a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x); 
}
// scales down by w                                                                                                                                           
void Vec4f::normalize_w ()
{
  this->x= this->x/this->w;
  this->y= this->y/this->w;
  this->z= this->z/this->w;
}
//scales length to one (ignoring w)
void Vec4f:: normalize(){
  double magn = sqrt(pow(this->x,2) + pow(this->y,2)+pow(this->z, 2));
  if (magn){
    this->scale(1.0/magn);
  }
}
// normalizes and takes the dot product over x, y, z.

double Vec4f::dot( Vec4f vec2)const{
  Vec4f a= this->copy();
  a.normalize_w();
  Vec4f b= vec2.copy();
  b.normalize_w();
  return a.x*b.x + a.y*b.y +a.z*b.z ;
}

void Vec4f::scale(double f){
  this->x = this->x*f;
  this->y = this->y*f;
  this->z = this->z*f;
}


double Vec4f::magnitude()const{
  return sqrt(pow(this->x,2) + pow(this->y,2)+pow(this->z, 2));
}

/*
template <typename T, int N> void vectors::matrix_multiply( T matr1[N][N], T matr2[N][N], T result[N][N]){
  for (int i = 0; i<N; i++){
    for (int j=0; j<N; j++){
      result[i][j]=0;
      for (int k = 0; k<N; k++){
	result[i][j] = result[i][j] + matr1[i][k]*matr2[k][j];
      }
    }
  }
}
*/
