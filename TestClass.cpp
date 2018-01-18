#include "TestClass.h"

TestClass::TestClass(posx, posy, posz, velx, vely, velz)
{
  this->posvector = Vec4f(posx, posy, posz);
  this->velcector = Vec4f(velx, vely, velz)
}

void TestClass::updatevelocity(Vec4f accelerationvec)
{
  this->velvector = this->velvector+accelerationvec;
}

void TestClass::updatepos()
{
  this->posvector = this->posvector + this->velvector;
}

void ShipClass::initialize(int numsubsyms, int *subsystemlist)
{
  this->subsystemlist = malloc(sizeof(SystemStorage) * numsubsyms);
}

ShipClass::ShipClass(float posx, float posy, float posz, float velx, float vely, float velz, int numsubsyms, int *subsystemlist): TestClass(posx, posy, posz, velx, vely, velz)
{
  initialize(numsubsyms, subsystemlist);
}






