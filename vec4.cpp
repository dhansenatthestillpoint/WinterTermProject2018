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
