#include "vec4.h"
#include <stdio.h>
#include "light.h"
#include<math.h>


void doop(){  
  const Light * sun1 = new PointSource( Vec4f (0,0,30), 100, 255, 0, 255);
  const Light *  sun2 = new  PointSource(Vec4f (0.0,50.0,-30.0),50, 0, 255, 155);
  const Light * lighting = light::add(sun1, sun2); 
 

  for (double t=0.0; t<2*M_PI; t=t+(M_PI/10)){
    Vec4f pos = Vec4f(t, sin(t), cos(t));
    Vec4f angle = Vec4f(sin(t), cos(t), 1);
    //    printf("t:%f\n",t);
    //printf("lighting %x, sun1: %x , \n",&lighting, &sun1);
    std::tuple<double, unsigned char *> result = (*lighting)(pos, angle);
    //std::tuple<double, unsigned char *> result = sun1(pos,angle);
    printf("%f, %d, %d, %d\n", std::get<0>(result), std::get<1>(result)[0], std::get<1>(result)[1], std::get<1>(result)[2]);
    //    sun1->~Light();
    // sun2->~Light();
    // lighting->~Light();
    }

  delete lighting;
  
}
int main(){
  doop();
}
