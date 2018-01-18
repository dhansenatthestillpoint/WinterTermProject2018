
#include "objectloader.h"
#include <fstream>
#include <string.h>
#include <stdio.h> //for sscanf
#include <iostream>

  //constructor, takes in  3 vertices and a normal vector
  // mallocs the instance variable vertices, and assigns values
Triangle::Triangle(Vec4f v1, Vec4f v2, Vec4f v3, Vec4f norm):
  normal(norm)
{
  vertices = (Vec4f *)malloc (sizeof(Vec4f)* 4);
  vertices[0]=v1;
  vertices[1]=v2;
  vertices[2]=v3;
}
  //destructor, frees vertices.
Triangle::~Triangle(){

  if (vertices){
    free(vertices);
  }

}





 
  //loads from file. Steps:
  //read through the file to count number of vertices (lines starting with v), normals(lines starting with vn), and faces(lines starting with f)
  //malloc vertices, normals, and faces 
  // read through the file again, load in vertices and normals.
  // triangulate each nontriangular face: e.g. a face with verts A B C D E F ... will become faces ABC ACD ADE AEF ...
  // make each face into a Triangle in faces. 
  // destroy vertices and normals, all info should have been copied successfully into faces.
  // also handle filenotfound exceptions somehow. 
ObjectMap::ObjectMap (std::string filename){ //TODO

  std::ifstream file;
  file.open(filename);
  std::string line;
  int vcount=0;
  int vncount = 0;
  int fcount = 0;
  //read through the file to count number of vertices (lines starting with v), normals(lines starting with vn), and faces(lines starting with f)          
  if (file.is_open()){
    while (getline(file, line)){
      //      std::cout << line << \n;

      if (line[0]=='v' && line[1] == 'n'){
	vncount++;
      }else if (line[0]=='v'){
	vcount++;
      } else if (line[0]=='f'){
	fcount=fcount-2;
	int i = 0;

	while (i != std::string::npos){ //counts number of vertices, subtracts 2, and adds that to fcount.
	  i = line.find(" ", i+1);
	  fcount++;
	}

      }
    }

    file.close();

  }else{
    //maybe handle errors here?
    ;
  }
  //malloc vertices, normals, and faces 
  //  printf("%d\n%d\n%d\n", vcount, vncount, fcount);

  vertices = (Vec4f *)malloc(sizeof (Vec4f) * (vcount +2));
  normals = (Vec4f *)malloc (sizeof (Vec4f) * (vncount +2));
  faces = (Triangle *)malloc(sizeof(Triangle *) * (fcount+2));
  // printf("%p\n%p\n%p\n", vertices, normals, faces);


  vcount=1;
  vncount = 1;
  fcount = 1;
  // read through the file again, load in vertices and normals.    
  file.open(filename);

  if (file.is_open()){

    while (getline(file, line)){
      std::cout << line << "\n";
 
      char * c_line =(char *) line.c_str(); //convert to c string to split. 
    //vertices
    if (line[0]=='v' && line[1] == ' '){
      double x;
      double y;
      double z;
      sscanf(c_line, "v %lf %lf %lf\n", &x, &y, &z);
      vertices[vcount++]=Vec4f(x,y,z);
    } else if (line[0]=='v' && line[1] == 'n'){
      double x;
      double y;
      double z;
      sscanf(c_line, "v %lf %lf %lf\n", &x, &y, &z);
      normals[vncount++]=Vec4f(x,y,z);
    } else if (line[0]=='f'){
      int vert1;
      int norm;
      int vert2;
      int vert3;
      int trash;
      int face_i = 0;
      sscanf(c_line, "f %d//%d %d//%d%s", &vert1,&norm, &vert2, &trash, c_line );
	
      while (c_line != NULL)
      {
	  
	std::cout  << c_line << "\n";
	if ( std::sscanf(c_line, "%d//%d%s", &vert3, &trash, c_line) <3 ){//if fails to scan, scan without trailing string
	
	   c_line = NULL;
	  }
	  faces[face_i]= Triangle(vertices[vert1], vertices[vert2], vertices[vert3], normals[norm] );//handling index out of bounds errors would be a good idea. 
	face_i++;
	vert2  = vert3;
      }

    }
    }
    file.close();
  }
  free (vertices);
  free (normals);
}

  
 





  

  //accessor method
Triangle * ObjectMap::get_faces() const{
  return faces;
}


  //destructor, loops over faces, deleting each one (use delete *face;), then frees the whole array. 
ObjectMap::~ObjectMap(){
  Triangle * originalfaces = faces;
  // for (int i = 0; faces[i] != NULL; i++){
  //        faces->~Triangle();
	// }
  free (faces);

}





