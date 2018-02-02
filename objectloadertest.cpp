#include <stdio.h>
#include "objectloader.h"

int main(){
  ObjectMap * current  = new ObjectMap("assets/Cube.obj");
  std::cout << current->get_num_f() << "\n";

  Face * shmurp = current->faces;
  shmurp++;
  while(shmurp){
    //    shmurp-> print();
    shmurp++;
  }
}
