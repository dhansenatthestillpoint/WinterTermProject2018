#include "renderer.h"
#include <dirent.h>
#include<string>
#include <algorithm>  
z_cmp::z_cmp(Vec4f camera_pos):
  mcamera_pos(camera_pos){}

//compares by distance to camera
bool z_cmp::operator()(Face f1, Face f2){
  return ((*(f1.v[0]) - mcamera_pos).magnitude() < (*(f2.v[0]) - mcamera_pos).magnitude());
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
void Renderer::render(double time){
  //loop over all Entities.
  ObjectMap * current;
  Entity * curEnt; //o god of isaac and abraham, why do I do these things
  all_v  =new std::vector<Vec4f>();
  all_vn  =new std::vector<Vec4f>();
  all_f  =new std::vector<Face *>();
  int offset=0;
  int vn_offset =0;
  //precalculate anything that doesn't include rel_pos, or current
  Vec4f aim = camera->get_aim();
  Vec4f vert = camera->get_vertical() * camera->height;
  Vec4f horz= camera-> get_horizontal() * camera->width;
  Vec4f cull_top = (aim+vert).cross(camera->get_horizontal()   ).normalize();
  Vec4f cull_bottom = (aim-vert).cross(camera->get_horizontal()).normalize();
  Vec4f cull_right = (aim+horz).cross(camera->get_vertical()   ).normalize();
  Vec4f cull_left = (aim-horz).cross(camera->get_vertical()    ).normalize();

  for (int ent_i = 0; ent_i <allEntities->size(); ent_i++){
    current = allObjectMaps[allEntities->at(ent_i)->ship_model];
    curEnt =(allEntities->at(ent_i));
    //cull by viewing frustrum

    Vec4f rel_pos = curEnt->posvector - camera->posvector;
    double cam_z = camera->get_aim().dot(rel_pos);
    double radius = current->radius;
    if (cam_z > camera->near_plane - radius //front
	&& cam_z < camera->far_plane + radius //back
	&& rel_pos.dot (cull_top)    < 0+radius //top
	&& rel_pos.dot (cull_bottom) > 0-radius //bottom
	&& rel_pos.dot (cull_right)  < 0+radius //right
	&& rel_pos.dot (cull_left)   > 0-radius //left    
	)
      {

	//these are local basis vectors, not coordinates
	Vec4f ship_x = curEnt->anglevector.copy();
	ship_x.normalize();
	Vec4f ship_z = curEnt->rollvector.copy(); 
	ship_z.normalize();
	Vec4f ship_y = ship_z.cross(ship_x);
	ship_y.normalize();
	double local_to_global[4][4] = {
	  {ship_x.x, ship_y.x, ship_z.x, curEnt->posvector.x},
	  {ship_x.y, ship_y.y, ship_z.y, curEnt->posvector.y},
	  {ship_x.z, ship_y.z, ship_z.z, curEnt->posvector.z},
	  {0,0,0,1}
	};
	double rotation_only[4][4] = {
	  {ship_x.x, ship_y.x, ship_z.x, 0},
	  {ship_x.y, ship_y.y, ship_z.y, 0},
	  {ship_x.z, ship_y.z, ship_z.z, 0},
	  {0,0,0,1}
	};
	//add faces to face list,
	//vectors to veclist
	//texture vecs to texturelist 

	//move v, transform to global
	for (int i=0; i<current->get_num_v(); i++){
	  all_v->push_back(local_to_global * current->vertices[i]); //add transformed vector to all_v_vn
	  
	}
	
	for (int i=0; i<current->get_num_vn(); i++){
	  all_vn->push_back(local_to_global * current->normals[i]);
	}
		/*
	for(int i=0; i<i<current->get_num_vt(); i++){
	  all_vt.push_back(current->textures[i]); //leave textures unchanged
	  } */ 
	//Vec4f * start_of_old_v  = current->get_v();
	//Vec4f * start_of_old_vn = current->get_vn();
	//copy all faces, update
	for(int i=0; i< current->get_num_f(); i++){
	  Face  * curface= new  Face((current->faces[i]));//copy?
	  curface->light = light.get_Light(curface->v[0], curface->vn);
	  curface->update_v(&(all_v[offset]));
	  curface->update_vn(&(all_vn[vn_offset]));
	  all_f.push_back(curface);
	}
      

      }//end culling if
  
	

    //sort facelist
    std::sort(all_f.begin, all_f.end, z_cmp(camera->posvector));
    //generate transform matrix. 
    if (!(oldcamera=(*camera))){//only do this math if the camera has moved
      double Vx = (camera -> get_vertical()).x;
      double Ux = (camera -> get_horizontal()).x;
      double Vy = (camera -> get_vertical()).y;
      double Uy = (camera -> get_horizontal()).y;
      double x_factor = mwidth * Ux*Uy /(camera->width  * (Vx*Uy - Vy*Ux));
      double y_factor = mheight* Vx*Vy /(camera->height * (Ux*Vy - Uy*Vx));
      //screen x
      transform_matrix[0][0] = x_factor * ( 1 - aim.x * aim.x + aim.x * aim.y);
      transform_matrix[0][1] = x_factor * (-1 + aim.y * aim.y - aim.x * aim.y) ;
      transform_matrix[0][2] = x_factor * (     aim.y * aim.z - aim.x * aim.z) ;
      transform_matrix[0][3] = camera->width; //puts coordinates positive
      //screen y
      transform_matrix[1][0] = y_factor * ( 1 - aim.x * aim.x + aim.x * aim.y);
      transform_matrix[1][1] = y_factor * (-1 + aim.y * aim.y - aim.x * aim.y);
      transform_matrix[1][2] = y_factor * (     aim.y * aim.z - aim.x * aim.z);
      transform_matrix[1][3] = camera->height;
      //the screen is flat my dudes. Like maybe some other useful info could go here but  ¯\_(ツ)_/¯
      transform_matrix[2][0] = 0;
      transform_matrix[2][1] = 0;
      transform_matrix[2][2] = 0;
      transform_matrix[2][3] = 0;
      //and mystic w
      transform_matrix[2][0] = 0;
      transform_matrix[3][1] = 0;
      transform_matrix[3][2] = 0;
      transform_matrix[3][3] = 1;

    }
    for (int i=0; i<all_v_vn.size(); i++){
  //transform vectors by global coords to data on screen.
      Vec4f p_prime = all_v_vn[i]-camera->posvector;
      all_v_vn[i] = transform_matrix * p_prime; 
      all_v_vn[i].scale(1/(p_prime.dot(aim)));
    }

			
 
    //rasterize faces. pass by value
    for (int i=0; i<all_f.size(); i++){
      Rasterizer.rasterize(&(f[i]));
    }


}


  //constructor. Should be called exactly once:
Renderer::Renderer(std::vector<Entity> * entities, Camera * incamera, CelestialBody * solar_system):
  allEntities(entities),
  camera(incamera),
  light(solar_system)
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




