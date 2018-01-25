#include<math.h>
#include<algorithm>
#include"rasterizer.h"

#define max std::max
#define min std::min
Rasterizer::Rasterizer(Glib::RefPtr< Gdk::Pixbuf > pixbuf, int roawstride, int nchannels, int width, int height ){}
//to be called when window is resized                                                                                                  
void Rasterizer::updateSize(int rowstride, int nchannels, int width, int height){}

void Rasterizer::rasterize (const Face * face, const char * texturefile, const int texwidth, const int texheight){
  Vec4f * minx = face->v[0];
  Vec4f * maxx = face->v[0];
  Vec4f * other = face ->v[0];
  //sort the veritces in the face
  //im sure theres a more efficient way to do this.
  for (int i=0; i<3; i++){
    if (face->v[i]->x <minx->x){
      minx = face->v[i];
    }    
    if (face->v[i]->x > maxx ->x){
      maxx = face ->v[i];
    }
  }
  for (int i =0; i<3; i++){
    if (face->v[i]!= minx && face->v[i]!=maxx){
      other = face->v[i];
    }
  }
  //loop over pixels
  //loops in a way that excludes everthing outside the triangle. I'm pretty sure.
  double y_slope_1 = (maxx->y  - minx->y) /(max((float).00001, maxx->x -  minx->x));
  double y_slope_2 = (other->y - minx->y) /(max((float).00001, other->x - minx->x));
  double y_slope_3 = (maxx->y  - other->y)/(max((float).00001, maxx->x - other->x));
  bool going_up  = (y_slope_1 < y_slope_2);
  unsigned char r = face->light.get_r();
  unsigned char g = face->light.get_g();
  unsigned char b = face->light.get_b();
  if (going_up){ //necessitates copy pasting code, but it'll be way more effecient than the alternative
    for (int ix = (int)minx->x; ix < (int)maxx->x; ix++){
      int ycap1 = (int)(ix*y_slope_2 + minx->y); //get it all out of the loop
      int ycap2 = (int)((ix - maxx->x) * y_slope_3 + maxx->y); 
	for (int iy = (int)(ix*y_slope_1 + minx->y); iy < min (ycap1, ycap2); iy++){
	//get texture
	int texture_offset = 0; //This is a placeholder, Idk how to really get it. 
	//multiply by light

	//output
	int out_offset= ix*mchannels + iy*mrowstride;
	mpixbuf->get_pixels()[out_offset]=sqrt(texturefile[texture_offset] * r);
	mpixbuf->get_pixels()[out_offset+1]=sqrt(texturefile[texture_offset+1] * g);
	mpixbuf->get_pixels()[out_offset+2]=sqrt(texturefile[texture_offset+2] * b);

      }
    }
  }
	
	
	   

}
