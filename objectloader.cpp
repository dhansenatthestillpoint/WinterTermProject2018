
#include "objectloader.h"
#include <fstream>
#include <string.h>
#include <stdio.h> //for sscanf
#include <iostream>

  //constructor, takes in  3 vertices and a normal vector
  // mallocs the instance variable vertices, and assigns values
Face::Face(int v1, int v2, int v3,int vt1, int vt2, int vt3,  int norm):
  vn(norm)
{
  v[0]=v1;
  v[1]=v2;
  v[2]=v3;
  vt[0]=vt1;
  vt[1]=vt2;
  vt[2]=vt3;
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
  vcount=0;
  vncount = 0;
  vtcount = 0;
  fcount = 0;
  radius = 0;
  //read through the file to count number of vertices (lines starting with v), normals(lines starting with vn), and faces(lines starting with f)          
  if (file.is_open()){
    while (getline(file, line)){

      if (line[0]=='v' && line[1] == 'n'){
	vncount++;

      } else if (line[0]=='v' && line[1] =='t'){
	vtcount++;
      }
      else if (line[0]=='v' && line[1]==' '){
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

  vertices = (Vec4f *)malloc(sizeof (Vec4f ) * (vcount +2));
  normals = (Vec4f *)malloc (sizeof (Vec4f) * (vncount +2));
  faces = (Face *)malloc(sizeof(Face *) * (fcount+2));
  textures = (Vec4f *)malloc(sizeof (Vec4f) * vtcount +2);
  // printf("%p\n%p\n%p\n", vertices, normals, faces);


  vcount=1;
  vncount = 1;
  vtcount =1;
  fcount = 1;
  // read through the file again, load in vertices and normals.    
  file.open(filename);

  if (file.is_open()){

    while (getline(file, line)){
      //      std::cout << line << "\n";
 
      char * c_line =(char *) line.c_str(); //convert to c string to split. 
    //vertices
    if (line[0]=='v' && line[1] == ' '){
      double x;
      double y;
      double z;
      sscanf(c_line, "v %lf %lf %lf\n", &x, &y, &z);
      Vec4f vecboi(x,y,z);
      radius = max(radius, vecboi.magnitude());
      vertices[vcount++]=vecboi;
    } else if (line[0]=='v' && line[1] == 'n'){
      double x;
      double y;
      double z;
      sscanf(c_line, "v %lf %lf %lf\n", &x, &y, &z);
      normals[vncount++]=Vec4f(x,y,z);
    }else if (line[0]=='v' && line[1] == 't') {
      double x;
      double y;
      sscanf(c_line, "v %lf %lf \n", &x, &y);
      textures[vtcount++] = Vec4f(x,y, 0);
    } else if (line[0]=='f'){
      int vert1;
      int norm;
      int vert2;
      int vert3;
      int trash;
      int vt1;
      int vt2;
      int vt3;
      int face_i = 0;
      sscanf(c_line, "f %d/%d/%d %d/%d/%d%s", &vert1, &vt1, &norm, &vert2, &vt2,  &trash, c_line );
	
      while (c_line != NULL)
      {
	  
	std::cout  << c_line << "\n";
	if ( std::sscanf(c_line, "%d/%d/%d%s", &vert3, &vt3, &trash, c_line) <4 ){//if fails to scan, scan without trailing string
	
	   c_line = NULL;
	  }
	faces[face_i]= Face(vert1, vert2, vert3, vt1, vt2, vt3, norm );//handling index out of bounds errors would be a good idea. 
	face_i++;
	vert2  = vert3;
	vt2 = vt3;
      }

    }
    }
    file.close();
  }
  //read in textures
  texturefile = "";
  file.open(fname.substr(fname.length() - 4)+".mtl");
  if (file.is_open()){
    while (getline(file, line)){
      if (line.substr(0,5).compare("map_Kd")==0){
	texturefile = line.substr(6);  
      }
    }
  }
}


ObjectMap::ObjectMap(ObjectMap o2):


  vcount (o2.vcount),
  vncount (o2.vncount),
  vtcount (o2.vtcount),
  fcount (o2.fcount),
  vertices (o2.vertices),
  normals(o2.normals),
  textures(o2.textures),
  faces(o2.faces),
  texturefile(o2.texturefile)
{}
  
 
Face * ObjectMap::get_faces() const{
  return faces;
}
Vec4f * ObjectMap::get_vertices() const{
  return vertices;
}
Vec4f * ObjectMap::get_normals() const{
  return normals;
}
Vec4f *ObjectMap::get_textures() const{
  return textures;
}





int ObjectMap::get_num_v() const{ return vcount;}
int ObjectMap::get_num_vn() const{ return vncount;}
int ObjectMap::get_num_vt() const{return vtcount;}
int ObjectMap::get_num_f() const{ return fcount;}
  




  //destructor, loops over faces, deleting each one (use delete *face;), then frees the whole array. 
ObjectMap::~ObjectMap(){
  //Face * originalfaces = faces;
  free (faces);
  free (vertices);
  free(normals);
  free(textures);
}





