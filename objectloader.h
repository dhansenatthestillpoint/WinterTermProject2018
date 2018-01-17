#ifndef OBJECT_LOADER_H
#define OBJECT_LOADER_H


#include "vec4.h"
#include <string>

class Triangle{
 public:
  // array of vertices, of length 3 with a null terminator.
  vec4f * vertices;
  vec4f normal; // normal vector.

  //constructor, takes in  3 vertices and a normal vector
  // mallocs the instance variable vertices, and assigns values
  Triangle(vec4f v1, vec4f v2, vec4f v3, vec4f norm);
  //destructor, frees vertices.
  ~Triangle()
}



class ObjectMap{
 private:
  vec4f * vertices;
  vec4f * normals;
 public:
  //list of faces
  Triangle * faces;
 
  //loads from file. Steps:
  //read through the file to count number of vertices (lines starting with v), normals(lines starting with vn), and faces(lines starting with f)
  //malloc vertices, normals, and faces 
  // read through the file again, load in vertices and normals.
  // triangulate each nontriangular face: e.g. a face with verts A B C D E F ... will become faces ABC ACD ADE AEF ...
  // make each face into a Triangle in faces. 
  // destroy vertices and normals, all info should have been copied successfully into faces.
  // also handle filenotfound exceptions somehow. 
  ObjectMap (std::string filename);
  
  //more methods here probly
  

  //accessor method
  Triangle * get_faces() const;


  //destructor, loops over faces, deleting each one (use delete *face;), then frees the whole array. 
  ~ObjectMap()
}






#endif
