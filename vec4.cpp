#include "vec4.h"


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



Vec4 operator+(Vec4 vec1,  Vec4 vec2){
  return Vec4(vec1.x+vec2.x, vec1.y+vec2.y, vec1.z+vec2.z, vec1.w+vec2.w);
}

Vec4 Vec4::copy(){
  return Vec4(this->x, this->y, this->z, this->w);
}

//normalizes w to 1 then takes the cross product over x,y,z                                                                                                   
Vec4 Vec4::cross( Vec4 vec2){
  Vec4 a= this->copy();
  a.normalize();
  Vec4 b= vec2.copy();
  b.normalize();
  return Vec4( a.y * b.z - a.z*b.y , a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x); 
}
// scales down by w                                                                                                                                           
void Vec4::normalize (){}
// normalizes and takes the dot product over x, y, z.
int Vec4::dot( Vec4 vec2){
  Vec4 a= this->copy();
  a.normalize();
  Vec4 b= vec2.copy();
  b.normalize();
  return a.x*b.x + a.y*b.y +a.z*b.z ;
}

void Vec4::scale(int f){
  this->x = this->x*f;
  this->y = this->y*f;
  this->z = this->z*f;
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

Vec4f Vec4f::copy(){
  return Vec4f(this->x, this->y, this->z, this->w);
}

//normalizes w to 1 then takes the cross product over x,y,z                                                                                                   
Vec4f Vec4f::cross( Vec4f vec2){
  Vec4f a= this->copy();
  a.normalize();
  Vec4f b= vec2.copy();
  b.normalize();
  return Vec4f( a.y * b.z - a.z*b.y , a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x); 
}
// scales down by w                                                                                                                                           
void Vec4f::normalize (){}
// normalizes and takes the dot product over x, y, z.
double Vec4f::dot( Vec4f vec2){
  Vec4f a= this->copy();
  a.normalize();
  Vec4f b= vec2.copy();
  b.normalize();
  return a.x*b.x + a.y*b.y +a.z*b.z ;
}

void Vec4f::scale(int f){
  this->x = this->x*f;
  this->y = this->y*f;
  this->z = this->z*f;
}
