#include "renderer.h"
#include <dirent.h>
#include<string>
#include <algorithm>  
z_cmp::z_cmp(Vec4f camera_pos):
  mcamera_pos(camera_pos);

//compares by distance to camera
bool z_cmp::z_cmp operator()(Face f1, Face f2){
  return (f1.v[0] - mcamera_pos).magnitude() < (f2.v[0] - mcamera_pos).magnitude();
}






  //update size
void Renderer::set_pixbuf ( Glib::RefPtr< Gdk::Pixbuf > pixbuf, int rowstride, int nchannels, int width, int height){
  mpixbuf =pixbuf;
  mrowstride =rowstride;
  mchannels =nchannels;
  mwidth  =width;
  mheight =height;
}

  //main loop
void Renderer::render(double time =0.0){
  //loop over all Entities.
  ObjectMap * current;
  Entity * curEnt; //o god of isaac and abraham, why do I do these things
  all_v_vn  =new std::vector<Vec4f>();
  all_vt  =new std::vector<Vec4f>();
  all_f  =new std::vector<Face>();
  int offset=0;
  int vt_offset=0;
  for (int ent_i = 0; ent_i <allEntities.size(); ent_i++){
    current = &allObjectMaps[ allEntities[ent_i].ship_model];
    curEnt =&allEntities[ent_i];
    //cull by viewing frustrum
    Vec4f aim = camera->get_aim();
    Vec4f rel_pos = curEnt->pos - camera->pos;
    double cam_z = camera->aim.dot(rel_pos);
    double radius = current->radius;
    Vec4f vert = camera->get_vertical() * camera->height;
    Vec4f horz= camera-> get_horizontal() * camera->width;
    if (cam_z > camera->near_plane - radius //front
	&& cam_z < camera->far_plane + radius //back
	&& rel_pos.dot ( (aim+vert).cross(camera->get_horizontal()).normalize()) < 0+radius //top
	&& rel_pos.dot ( (aim-vert).cross(camera->get_horizontal()).normalize()) > 0-radius //bottom
	&& rel_pos.dot ( (aim+horz).cross(camera->get_vertical()  ).normalize()) < 0+radius //right
	&& rel_pos.dot ( (aim-horz).cross(camera->get_vertical()  ).normalize()) > 0-radius //left    
	))
      {

	//these are local basis vectors, not remotely coordinates
	Vec4f ship_x = curEnt->anglevector.copy();
	ship_x.normalize();
	Vec4f ship_z = curEnt->rollvector.copy();
	ship_z.normalize();
	Vec4f ship_y = ship_z.cross(ship_x);
	ship_y.normalize();
	int local_to_global[4][4] = {
	  {ship_x.x, ship_y.x, ship_z.x, curEnt.posvector.x},
	  {ship_x.y, ship_y.y, ship_z.y, curEnt.posvector.y},
	  {ship_x.z, ship_y.z, ship_z.z, curEnt.posvector.z},
	  {0,0,0,1}
	}
	//add faces to face list,
	//vectors to veclist
	//texture vecs to texturelist 
	for (int i=0; i<current->get_num_v(); i++){
	  all_v_vn.push_back(local_to_global * current->vertices[i]); //add transformed vector to all_v_vn
	  
	}
	for (int i=0; i<i<current->get_num_vn(); i++){
	  all_v_vn.push_back(local_to_global * current->normals[i]);
	}
	for(int i=0; i<i<current->get_num_vt(); i++){
	  all_vt.push_back(current->textures[i]); //leave textures unchanged
	}  
	for(int i=0; i<i<current->get_num_f(); i++){
	  Face * curface= &(current->faces[i]);
	  all_f.push_back(Face(curface->v[0]+offset, curface->v[1]+offset, curface->v[2]+offset, curface->v[3]+offset, curface->vt[0]+vt_offset, curface->vt[1]+vt_offset, curface->vt[2]+vt_offset, curface->vn+offset+current->get_num_v())); //hooey mama thats a line of code. adds offset to each value in the face. I'll kick myself if I have to do something similar again and shoulda just sucked it up and writen a face::transform method. 
	}
      

      }//end culling if
  
	

    //sort facelist
    std::sort(all_f.begin, all_f.end, z_cmp(camera->posvector));
    //generate transform matrix. 

    for (int i=0; i<all_v_vn.size(); i++){
  //transform vectors by global coords to data on screen.  
  //
  //
  

    }




}


  //constructor. Should be called exactly once:
Renderer::Renderer(std::vector<Entity> * entities):
  allEntities(entities),
  camera(incamera)
{
  //load in obj files
  // count all obj files:
  DIR * dir  = opendir("assets");
  struct dirent * file;

  allObjectMaps = new unordered_map<std::string,ObjectMap >();
    
  dir = opendir("assets");
  while ( (file = readdir(dir))!='\0'){ //count the obj files                                                
    
    std::string fname =  file->d_name;
    int num_objectMaps =0;
    std::string fname_no_extension = fname.substr(fname.length() - 4);
    if (fname_no_extension.compare(".obj") == 0){
      AllObjectMaps[fname_no_extension]= ObjectMap (fname);
    }
    closedir(dir);
  }
}

  //destroy
    ~Rendered(){

      
    }

}




