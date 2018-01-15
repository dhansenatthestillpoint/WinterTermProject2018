#include "vec4.h"
#include <stdio.h>


int main(){
  Vec4 a = Vec4(1,2,3);
  Vec4 b = Vec4(4,5,6);
  Vec4 added= a+b;
  Vec4 crossed = a.cross(b);
  int dotted = a.dot(b);
  printf("add: %d,%d, %d \n cross: %d, %d, %d\n dot: %d\n", added.x, added.y, added.z, crossed.x, crossed.y, crossed.z, dotted);

  Vec4f af = Vec4f(1.1,2.2,3.3);
  Vec4f bf = Vec4f(4.111,5.63,6.3232);
  Vec4f addedf= af+bf;
  Vec4f crossedf = af.cross(bf);
  double dottedf = af.dot(bf);
  printf("add: %f,%f, %f \n cross: %f, %f, %f\n dot: %f\n", addedf.x, addedf.y, addedf.z, crossedf.x, crossedf.y, crossedf.z, dottedf);
}
