#include "Entity.h"

Entity::Entity(float posx, float posy, float posz, float velx, float vely, float velz, float ang1, float ang2, float ang3, float avel1, float avel2, float avel3):
posvector(Vec4f(posx, posy, posz)),
anglevector(Vec4f(ang1, ang2, ang3)),
velvector(Vec4f(velx, vely, velz)),
angularvel(Vec4f(avel1, avel2, avel3))
{
}

void Entity::updatevelocity(Vec4f accelerationvec)
{
  this->velvector = this->velvector+accelerationvec;
}

void Entity::updateangle(Vec4f inputangle)
{
  this->anglevector = this->anglevector + inputangle;
}

void Entity::updateposition()
{
  this->posvector = this->posvector + this->velvector;
}

ShipClass::ShipClass(float posx, float posy, float posz, float velx, float vely, float velz, float avecx, float avecy, float avecz, float avelx, float avely, float avelz, int inputcount): Entity (posx, posy, posz, velx, vely, velz, avecx, avecy, avecz, avelx, avely, avelz)
{
  initsystems(inputcount);
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

void ShipClass::removeship(int systemcount){
  for (int i = 0; i < systemcount; i++)
    {
      free(&this->systemlist[i]);
    }
  free(this->systemlist);
}

SubsystemStorage::SubsystemStorage(int inputnumber, int inputcount, float *inputvals)
{

}

int main()
{
  
}
