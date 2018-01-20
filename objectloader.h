#ifndef OBJECT_LOADER_H
#define OBJECT_LOADER_H


#include "vec4.h"
#include <string>

class Face{
 public:

  int v[3]; //vertices is 3space
  int vt[3]; //vertices on texture
  int vn;//normal

  
  //constructor, takes in  3 vertices and a normal vector
  // mallocs the instance variable vertices, and assigns values
  Face(int  v1, int v2, int v3, int vt1, int vt2, int vt3, int norm);
  //destructor, frees vertices.
  //  ~Triangle();

};



class ObjectMap{
 protected:
  int vcount;
  int vncount;
  int vtcount;
  int fcount;
 public:
  double radius;
  Vec4f * vertices;
  Vec4f * normals;
  Vec4f * textures;
  //list of faces
  Face  *  faces;
  std::string texturefile;
  //loads from file. Steps:
  //read through the file to count number of vertices (lines starting with v), normals(lines starting with vn), and faces(lines starting with f)
  //malloc vertices, normals, and faces 
  // read through the file again, load in vertices and normals.
  // triangulate each nontriangular face: e.g. a face with verts A B C D E F ... will become faces ABC ACD ADE AEF ...
  // make each face into a Triangle in faces. 
  // also handle filenotfound exceptions somehow. 
  ObjectMap (std::string filename);
  //explicit copy constructor

  ObjectMap (ObjectMap o2);
 
  

  //accessor methods
  Face * get_faces() const;
  Vec4f * get_vertices() const;
  Vec4f * get_normals() const;
  Vec4f * get_textures() const;
  int  get_num_v() const;
  int get_num_vn() const;
  int get_num_vt() const;
  int get_num_f() const;
  //destructor, loops over faces, deleting each one (use delete *face;), then frees the whole array. 
  ~ObjectMap();
};






#endif
