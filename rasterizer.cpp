#include<math.h>
#include<algorithm>
#include"rasterizer.h"

#define max std::max
#define min std::min
#define NUM_CHANNELS 3

Rasterizer::Rasterizer(Glib::RefPtr< Gdk::Pixbuf > pixbuf, int roawstride, int nchannels, int width, int height ){}
//to be called when window is resized                                                                                                  
void Rasterizer::updateSize(int rowstride, int nchannels, int width, int height){}

void Rasterizer::rasterize (const Face * face){
  std::cout << face->v[0]->x <<"\n";
  const unsigned char * texturefile = face->texture_image;
  const int texwidth = face->texwidth;
  const int texheight = face -> texheight;
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
  double Vox = face->v[0]->x;
  double Voy = face->v[0]->y;
  double Vix = face->v[1]->x;
  double Viy = face->v[1]->y;
  double Vux = face->v[2]->x;
  double Vuy = face->v[2]->y;
  double Tox = face->vt[0]->x;
  double Toy = face->vt[0]->y;
  double Tix = face->vt[1]->x;
  double Tiy = face->vt[1]->y;
  double Tux = face->vt[2]->x;
  double Tuy = face->vt[2]->y;
  double denom = (Viy*Vox - Vix*Voy - Viy*Vux + Voy*Vux + Vix*Vuy - Vox*Vuy);
  //hooray for integers being slightly faster
  int texture_map[4][4] = {
    {(int)floor((Tux*(Voy - Viy) + Tox*(Viy - Vuy) + Tix*(Vuy - Voy))/denom), 
     (int)floor((Tux*(Vix - Vox) + Tix*(Vox - Vux) + Tox*(Vux - Vix))/denom), 
     (int)floor((Tux*(Viy*Vox - Vix*Voy) + Tox*(Vix*Vuy - Viy*Vux) + Tix*(Voy*Vux - Vox*Vuy))/denom), 
      0},
    {(int)floor((Tuy*(Voy - Viy) + Toy*(Viy - Vuy) + Tiy*(Vuy - Voy))/denom),
     (int)floor((Tuy*(Vix - Vox) + Tiy*(Vox - Vux) + Toy*(Vux - Vix))/denom),
     (int)floor((Tuy*(Viy*Vox - Vix*Voy) + Toy*(Vix*Vuy - Viy*Vux) + Tiy*(Voy*Vux - Vox*Vuy))/denom), 
      0},
    {0,0 ,1 , 0}, 
    {0, 0, 0, 1}
  }; 


  if (going_up){ //necessitates copy pasting code, but it'll be way more effecient than the alternative
    for (int ix = max(0,(int)minx->x); ix < min(mwidth, (int)maxx->x); ix++){
      int ycap1 = (int)(ix*y_slope_2 + minx->y); //get it all out of the loop
      int ycap2 = (int)((ix - maxx->x) * y_slope_3 + maxx->y); 
      int looptop  = min (ycap1, min(ycap2, mheight));
      for (int iy = max(0,(int)(ix*y_slope_1 + minx->y)); iy < looptop; iy++){
	//get texture
	  Vec4 texcoords = texture_map * Vec4(ix, iy, 0,0);
	  int texture_offset = texcoords.x * NUM_CHANNELS + texcoords.y * texwidth; 
	//multiply by light and 
	//output
	int out_offset= ix*mchannels + iy*mrowstride;
	mpixbuf->get_pixels()[out_offset]=(unsigned char) min( 255,(int)sqrt(texturefile[texture_offset] * r));
	mpixbuf->get_pixels()[out_offset+1]=(unsigned char) min( 255,(int)sqrt(texturefile[texture_offset+1] * g));
	mpixbuf->get_pixels()[out_offset+2]=(unsigned char) min( 255,(int)sqrt(texturefile[texture_offset+2] * b));

      }
    }
  } else {
      for (int ix = max(0,(int)minx->x); ix< min(mwidth, (int)maxx->x); ix++){
	int ycap1 = (int)(ix*y_slope_2 + minx->y); 
	int ycap2 = (int)((ix - maxx->x) * y_slope_3 + maxx->y);
	int looptop  = max (ycap1, max(ycap2,mheight));
	for (int iy = max(0,(int)(ix*y_slope_1 + minx->y)); iy > looptop; iy--){
	  //get texture                            
          Vec4 texcoords = texture_map * Vec4(ix, iy, 0,0);
          int texture_offset = texcoords.x * NUM_CHANNELS + texcoords.y * texwidth;
	  //multiply by light and output
	  int out_offset= ix*mchannels + iy*mrowstride;
	  mpixbuf->get_pixels()[out_offset]=(unsigned char) min( 255,(int)sqrt(texturefile[texture_offset] * r));
	  mpixbuf->get_pixels()[out_offset+1]=(unsigned char) min( 255,(int)sqrt(texturefile[texture_offset+1] * g));
	  mpixbuf->get_pixels()[out_offset+2]=(unsigned char) min( 255,(int)sqrt(texturefile[texture_offset+2] * b));

	}
      }
  }
	
	
	   

}
