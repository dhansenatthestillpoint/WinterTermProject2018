#include "Entity.h"

Entity::Entity(Vec4f inputpos, Vec4f inputvel, Vec4f inputang, Vec4f inputavel):
  posvector(inputpos.x, inputpos.y, inputpos.z),
  velvector(inputvel.x, inputvel.y, inputvel.z),
  anglevector(inputang.x, inputang.y, inputang.z),
  angularvel(inputavel.x, inputavel.y, inputavel.z)
{/*
  this->posvector = *(new Vec4f(inputpos.x, inputpos.y, inputpos.z));
  this->velvector = *(new Vec4f(inputvel.x, inputvel.y, inputvel.z));
  this->anglevector = *(new Vec4f(inputang.x, inputang.y, inputang.z));
  this->angularvel = *(new Vec4f(inputavel.x, inputavel.y, inputavel.z));*/
}

void Entity::updatevelocity(Vec4f accelerationvec)
{
  this->velvector = this->velvector + accelerationvec;
}

void Entity::updateangle(Vec4f inputangle)
{
  this->anglevector = this->anglevector + inputangle;
}

void Entity::updateposition()
{
  this->posvector = this->posvector + this->velvector;
}

ShipClass::ShipClass(Vec4f inputpos, Vec4f inputvel, Vec4f inputang, Vec4f inputavel, int inputcount):
Entity (inputpos, inputvel, inputang, inputavel)
{
  initsystems(inputcount);
}

ShipClass::~ShipClass()
{
  delete&(this->posvector);
  delete&(this->velvector);
  delete&(this->anglevector);
  delete&(this->angularvel);
}

void ShipClass::initsystems(int systemcount/*, int *subsystemcount*/)
{
  this->systemlist = (SystemStorage*)malloc(sizeof(SystemStorage) * systemcount);
  /*for (int i = 0; i < systemscount; i++)                                                            
    {                                                                                                 
      this->systemlist[i] = malloc(sizeof(float) * subsystemcount[i]);                                
      }*/
}

void ShipClass::initsubsystems(int systemcount, int *subtypes, int *subcounts, float **subsystemvals)
{
  for (int i = 0; i < systemcount; i++)
    {
      this->systemlist[i].tempstorage = new SubsystemStorage(subtypes[i], subcounts[i], subsystemvals[i]);
    }
}

void ShipClass::printvectors()
{
  std::cout << "Position: ";
  this->posvector.printvector();
  std::cout << "\nVelocity: ";
  this->velvector.printvector();
  std::cout << "\nRotation: ";
  this->anglevector.printvector();
  std::cout << "\nAngularV: ";
  this->angularvel.printvector();
}

void ShipClass::removeship(int systemcount){
  for (int i = 0; i < systemcount; i++)
    {
      free(&this->systemlist[i]);
    }
  free(this->systemlist);
}

SystemStorage::SystemStorage(int inputnumber)
{
  this->systemnumber = inputnumber;
}

SubsystemStorage::SubsystemStorage(int inputnumber, int inputcount, float *inputvals)
{
  this->subsystemstorageidentifier = inputnumber;
  this->currentheat = 0;
  this->maxheat = inputvals[0];
  this->currenthealth = inputvals[1];
  this->maxhealth = inputvals[1];
  this->numcomponents = inputcount;
  this->componentvals = inputvals;
}

SubsystemStorage::~SubsystemStorage()
{
  free(this->componentvals);
}

int main()
{
  Vec4f testposvec = Vec4f(8, 0, 0);
  Vec4f testvelvec = Vec4f(0, 0, 20.3);
  Vec4f testangvec = Vec4f(0, 10, 0);
  Vec4f testangvel = Vec4f(18.8, 0, 0);
  ShipClass *tempclass = new ShipClass(testposvec, testvelvec, testangvec, testangvel, 0);
  tempclass->printvectors();
}
