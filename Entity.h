#ifndef ENTITY_H
#define ENTITY_H

#include "vec4.h"
#include <stdlib.h>

class Entity{
 public:
  Vec4f posvector;
  Vec4f velvector;
  Vec4f anglevector; //Coreesponds to curent heading, NOT cross 0 with current heading. will point in directionof nose of ship
  Vec4f angularvel;
  float *classvarlist;
  
  Entity(Vec4f inputpos, Vec4f inputvel, Vec4f inputang, Vec4f inputavel);
  
  void updateangle(Vec4f inputangle);
  void updatevelocity(Vec4f accelerationvector);
  void updateposition();
};

//enum sytemdesignationnumber{Hatches, Dragfins, EmergencyBoosterEngines, Shields};

class SubsystemStorage{
 public:
  int subsystemstorageidentifier;
  float currentheat;
  float maxheat;
  float currenthealth;
  float maxhealth;
  int numcomponents;
  float *componentvals;
  SubsystemStorage(int inputnumber, int inputcount, float *inputvals);
  ~SubsystemStorage();

};

class SystemStorage{
 public:
  //enum systemdesignationnumber systemnum;
  int systemnumber;
  int numsystems;
  SubsystemStorage *tempstorage;
  SystemStorage(int inputnumber/*, int subinputcount*/);

  void addspecifiedsystemval(int inputnum, float addamount);
  void modifyspecifiedsystemval(int inputnum, float modamount);
};

class ShipClass: public Entity{
 public:
  SystemStorage *systemlist;
  ShipClass(Vec4f inputpos, Vec4f inputvel, Vec4f inputang, Vec4f inputavel, int numsubsyms);
  ~ShipClass();
  void initsystems(int numsubsyms);
  void initsubsystems(int systemcount, int *subsystemtypes, int *subsystemcounts, float** subsystemvals);
  void printvectors();
  void removeship(int systemcount);
};

#endif


