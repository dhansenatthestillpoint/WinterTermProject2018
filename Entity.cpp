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
  this->anglevector = anglevector.addangles(inputangle);
}

void Entity::updateposition()
{
  this->posvector = this->posvector + this->velvector;
}

void Entity::setposition(Vec4f inputvec)
{
  this->posvector = inputvec;
}

void Entity::setvelocity(Vec4f inputvec)
{
  this->velvector = velvector;
}

void Entity::setangle(Vec4f inputvec)
{
  //  if (this->validangle(inputvec) == 1)
  //{
      //tan 45 == 1
      this->anglevector.x = inputvec.x;
      this->anglevector.y = inputvec.y;
      this->anglevector.z = inputvec.z;
      //}
}

double Entity::toradians(double inputangle)
{
  return inputangle * (M_PI / 180.0);
}

Vec4f Entity::getheading()
{
  return Vec4f(cos(toradians(this->anglevector.y)) * cos(toradians(this->anglevector.z)), -1 * cos(toradians(this->anglevector.y)) * cos(toradians(this->anglevector.z)), sin(toradians(this->anglevector.y)));
}

Vec4f Entity::getlocalz()
{
  return Vec4f((sin(toradians(this->anglevector.x)) * sin(toradians(this->anglevector.z)) - (cos(toradians(this->anglevector.x)) * cos(toradians(this->anglevector.z)) * sin(toradians(this->anglevector.y)))), (cos(toradians(this->anglevector.z)) * sin(toradians(this->anglevector.x)) + (cos(toradians(this->anglevector.x)) * sin(toradians(this->anglevector.y)) * sin(toradians(this->anglevector.z)))), (cos(toradians(this->anglevector.x)) * cos(toradians(this->anglevector.y))));
}

/*
int Entity::validangle(Vec4f inputvec)
{
  double testvalue = pow(inputvec.x, 2) + pow(inputvec.y, 2) + pow(inputvec.z, 2);
  if (testvalue >= 0.99999999 && testvalue <= 1.00000001)
    {
      return 1;
    }
  else
    {
      return 0;
    }
}
*/

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
  tempclass->updateangle(Vec4f(20.0, 18.0, 38.0));
  tempclass->printvectors();
}
