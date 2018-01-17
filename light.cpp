#include "light.h"


Light::Light(){
  color=NULL;
}

AddedLight::AddedLight( const Light * light1, const Light * light2):
  L1(light1),
  L2(light2)
{
  color = (unsigned char *)malloc(4*sizeof(unsigned char));
  //printf("Added color alloc: %p, at %p\n",(void *)color, (void *)this);
}


AddedLight::AddedLight(){
  color=NULL;
  L1 = NULL;
  L2 = NULL;
}




Light::~Light(){

  if (color){
    //printf("Generic color free: %p , at %p\n",(void *)color, (void *)this);
    free (color);
  }
}

AddedLight::~AddedLight(){
  if (color){
    // printf("Added color free: %p , at %p\n",(void *)color, (void *)this);
    free (color);
  }
  if (L1){
    delete L1;
  }
  if (L2){
    delete L2;
  }
}


std::tuple<double, unsigned char *> AddedLight::operator()(Vec4f pos, Vec4f angle) const {

  if (L1!=NULL && L2!=NULL){


    std::tuple<double, unsigned char *> light1 = (*L1)(pos, angle);
    std::tuple<double, unsigned char *> light2 = (*L2)(pos, angle);
    //adds the two colors together, in the way that colors are supposed to be mixed (i.e squares, averages, then roots) 
      for (int i = 0; i<3; i++){                           
	int c1 = (int)(pow((int)std::get<1>(light1)[i],2) * (double)std::min(std::get<0>(light1), (double)MAX_LIGHT)/MAX_LIGHT);
	int c2 = (int)(pow((int)std::get<1>(light2)[i],2) * (double)std::min(std::get<0>(light2), (double)MAX_LIGHT)/MAX_LIGHT);
        color[i]= (unsigned char)sqrt((c1+c2)/2);
      }

      return std::make_tuple(std::get<0>(light1)+std::get<0>(light2), color);
    
    

  } else if (L1){
    return (*L1)(pos, angle);
  } else if (L2){
    return (*L2)(pos, angle);
  }else {
    color[0]=0;
    color[1]=0;
    color[2]=0;
    return std::make_tuple(0.0, color);
  }
}
 


PointSource::PointSource(Vec4f pos, double brightness, int  r, int  b, int  g):
  mpos(pos),
  brightness(brightness)
{
  color = (unsigned char*)malloc(4*sizeof(unsigned char));
  //printf("Point Source Color alloc: %x in %x\n",color, this);
  color[0] = (unsigned char)(r%256);
  color[1]= (unsigned char)(b%256);
  color[2]=(unsigned char)(g%256);
}
//yay math
std::tuple<double, unsigned char *> PointSource::operator()(Vec4f pos, Vec4f angle) const{

  Vec4f dir = pos-mpos;
  double rawstrength = brightness / pow(dir.magnitude(),2);
  dir.scale(-1); //this means that light is strongest when directly opposite the vector produced by a deosil crossproduct of the face. Cause we love that right hand rule
  double angledstrength = std::max(0.0,dir.dot(angle));
  return std::make_tuple(angledstrength, color);
}

PointSource::PointSource():
  mpos (Vec4f(0.0,0.0,0.0)),
  brightness (0)
{
}


PointSource::~PointSource(){
  if (color){
    //    printf("Color free: %p , at %p\n",color, this);
    free (color);
  }
}


const Light  *  light::add ( const Light * L1, const Light * L2){
    return new  AddedLight(L1, L2);
}

DirectionalSource::DirectionalSource():
  mdir (Vec4f(0.0,0.0,0.0)),
  brightness (0)
{
}


DirectionalSource::~DirectionalSource(){
  if (color){
    //    printf("Color free: %p , at %p\n",color, this);                                                          
    free (color);
  }
}


DirectionalSource::DirectionalSource(Vec4f dir, double brightness, int  r, int  b, int  g):
  mdir(dir),
  brightness(brightness)
{
  color = (unsigned char*)malloc(4*sizeof(unsigned char));
  //printf("Point Source Color alloc: %x in %x\n",color, this);                                                    
  color[0] = (unsigned char)(r%256);
  color[1]= (unsigned char)(b%256);
  color[2]=(unsigned char)(g%256);

  mdir.scale(-1); //just get this over with now
}


std::tuple<double, unsigned char *> DirectionalSource::operator()(Vec4f pos, Vec4f angle) const{
  double angledstrength = std::max(0.0,mdir.dot(angle));
  return std::make_tuple(angledstrength, color);
}
