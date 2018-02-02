#ifndef CELESTIAL_BODIES_H
#define CELESTIAL_BODIES_H


#include "light_and_gravity.h"
#define GRAVITATIONAL_CONSTANT 1


//Makes a sun with gravity and light emanating from it. 
  Sun::Sun(Vec4f pos, Color color, int mass):
    Entity(args_go_here),//todo once Entity is complete.         
    mmass(mass),
    mcolor(color)
{};
Color Sun::get_Light(Vec4f pos, Vec4f angle) const{
  Vec4f dir = pos-posvector;
  return mcolor / (int)(pow(dir.magnitude(),2)* std::max(0.0,-1*angle.dot(dir))) ;
}
Vec4f Sun::get_Gravity(Vec4f pos) const{
  Vec4f dir = pos-posvector;
  return GRAVITATIONAL_CONSTANT*mmass /(pow(dir.magnitude(),2)); //this gives acceleration due to gravity. (not gravitational force.)
}
//Planet class has a body it orbits, and and a light source it reflects/casts shadows. 
//Also works for moons and death stars

Color Planet::get_Light(Vec4f pos, Vec4f angle) const{
  //todo, i'm like halfway done with the math
}
Vec4f Planet::get_Gravity(Vec4f pos) const{
  Vec4f dir = pos-posvector;
  return GRAVITATIONAL_CONSTANT*mmass /(pow(dir.magnitude(),2));
};

Planet::Planet (CelestialBody * LightSource, CelestialBody * GravitySource, Color color, int mass, Vec4f pos):
  Entity(args_go_here),//todo once Entity is complete.
  mLightSource(LightSource),
  mCelestialBody(CelestialBody)
  mmass = mass;
{
  //todo: initialize velocity to be the right speed for a roughly circular orbit. 
}

//sums over its component bodies.
Color SolarSystem::get_Light(Vec4f pos, Vec4f angle) const{
  Color total = Color(0,0,0);
  for(CelestialBody current: bodies){
    total=total+current->get_Light(pos, angle);
    }
  return total;
}
Vec4f SolarSystem::get_Gravity(Vec4f pos) const{
  Vec4f total;
  for(CelestialBody current:bodies){
    total=total+current->get_Gravity(pos);
  }
  return total;
}
  


void SolarSystem::add(CelestialBody * body){
  if (body){
    bodies->push_back(body);
  }
}
SolarSystem::SolarSystem(){
  bodies = new std::vector<CelestialBody *>;
}
SolarSystem::~SolarSystem(){
  delete bodies;
}


//this one's easy
ConstantLight::ConstantLight(Color color):mcolor(color){}
Color ConstantLight::get_Light(Vec4f pos, Vec4f angle) const{return color}
Vec4f ConstantLight::get_Gravity(Vec4f pos) const {return Vec4f(0,0,0)}
};

#endif
