


#include "light_and_gravity.h"

#define GRAVITATIONAL_CONSTANT 1

CelestialBody::CelestialBody(Vec4f position, Vec4f avel, Color color):
  Entity (position, Vec4f(0,0,0), Vec4f(0,0,0), avel),
  mcolor(color)
{
}


//Makes a sun with gravity and light emanating from it. 
Sun::Sun(Vec4f pos, Color color, int mass):
  CelestialBody(pos, Vec4f(0,0,1), color),
  mmass(mass)
{}

Color Sun::get_Light(Vec4f pos, Vec4f angle) const{
  Vec4f dir = pos-posvector;
  double dirmagn = dir.dot(dir);
  if (dirmagn< pow(shipmodel->radius,2)){
    return Color(mcolor);
  }
  return mcolor / (int)(dirmagn* std::max(0.0,-1*angle.dot(dir))) ;
}
Vec4f Sun::get_Gravity(Vec4f pos) const{
  Vec4f dir = pos-posvector;
  double dirmagn = dir.dot(dir);
  dir.normalize();
  return dir * (GRAVITATIONAL_CONSTANT*mmass/dirmagn); //this gives acceleration due to gravity. (not gravitational force.)
}
//Planet class has a body it orbits, and and a light source it reflects/casts shadows. 
//Also works for moons and death stars

Color Planet::get_Light(Vec4f pos, Vec4f angle) const{
  //todo, i'm like halfway done with the math
  return Color(0,0,0);
}
Vec4f Planet::get_Gravity(Vec4f pos) const{
  Vec4f dir = pos-posvector;
  double dirmagn = dir.dot(dir);
  dir.normalize();
  return dir * (GRAVITATIONAL_CONSTANT*mmass/dirmagn);
};

<<<<<<< HEAD
Planet::Planet (CelestialBody * LightSource, CelestialBody * GravitySource, Color color, int mass, Vec4f pos):
  Entity(args_go_here),//todo once Entity is complete.
  mLightSource(LightSource),
  mCelestialBody(CelestialBody)
  mmass = mass;
=======
Planet::Planet (CelestialBody * LightSource, CelestialBody * GravitySource,Color color, int mass, Vec4f pos, double radius):
  CelestialBody(pos, Vec4f(0,0,0.77), color),//theres a better way to assign spin. but I'm so done with this project.
  mLightSource(LightSource),
  mGravitySource(GravitySource),
  mradius(radius),
  mmass(mass)
>>>>>>> refs/remotes/origin/master
{
  Vec4f relpos = mGravitySource -> posvector  - posvector;
  double velmagn = relpos.magnitude() * mGravitySource->get_Gravity(posvector).magnitude();
  Vec4f veldir = mGravitySource->angularvel.cross(relpos);
  veldir.normalize();
  this->velvector = veldir * velmagn;
}





//sums over its component bodies.
Color SolarSystem::get_Light(Vec4f pos, Vec4f angle) const{
  Color total = Color(0,0,0);
  for(CelestialBody * current: *bodies){
    total=total+current->get_Light(pos, angle);
    }
  return total;
}
Vec4f SolarSystem::get_Gravity(Vec4f pos) const{
  Vec4f total;
  for(CelestialBody * current: *bodies){
    total=total+current->get_Gravity(pos);
  }
  return total;
}
  


void SolarSystem::add(CelestialBody * body){
  if (body){
    bodies->push_back(body);
  }
}
SolarSystem::SolarSystem(): CelestialBody(Vec4f(0,0,0), Vec4f(0,0,0), Color(0,0,0))
{
  bodies = new std::vector<CelestialBody *>;
}



//this one's easy
ConstantLight::ConstantLight(Color color): CelestialBody(Vec4f(0,0,0), Vec4f(0,0,0), color){}
Color ConstantLight::get_Light(Vec4f pos, Vec4f angle) const{return mcolor;}
Vec4f ConstantLight::get_Gravity(Vec4f pos) const {return Vec4f(0,0,0);}



