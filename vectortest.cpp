#include "vec4.h"
#include <stdio.h>


int main(){
  double scaler[4][4] = {
    {2.0, 0.0,0.0,0.0}, {0.0,1.0,0.0,0.0}, {0.0,0.0,3.0,0.0}, {0.0,0.0,0.0,1.0}
  };

  double transform[4][4] = {
    {1.0, 0.0 ,0.0,4.0}, {0.0,1.0,0.0,3.0}, {0.0, 0.0,1.0,0.0}, {0.0,0.0,0.0,1.0}
  };

  Vec4f input (2.0,3.0,1.0);
  double result[4][4];
  vectors::matrix_multiply<double, 4>(scaler, transform, result) ;
    
  Vec4f res1 = result * input;
  Vec4f res2 = scaler * (transform * input); //* transform;
  Vec4f res3 = transform * (scaler * input);// * scaler;
  printf("input: %lf, %lf, %lf\n", input.x, input.y, input.z);
  printf("%lf, %lf, %lf\n", res1.x, res1.y, res1.z);
  printf("%lf, %lf, %lf\n", res2.x, res2.y, res2.z);
  printf("%lf, %lf, %lf\n", res3.x, res3.y, res3.z);

}
