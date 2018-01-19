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
  
  Entity(float posx, float posy, float posz, float velx, float vely, float velz, float ang1, float ang2, float ang3, float avelx, float avely, float avelz);
  
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

};

class SystemStorage{
 public:
  //enum systemdesignationnumber systemnum;
  int systemdnumber;
  int numsystems;
  SubsystemStorage *tempstorage;
  SystemStorage(int inputnumber, int inputcount);

  void addspecifiedsystemval(int inputnum, float addamount);
  void modifyspecifiedsystemval(int inputnum, float modamount);
};

class ShipClass: public Entity{
 public:
  SystemStorage *systemlist;
  ShipClass(float posx, float posy, float posz, float velx, float vely, float velz, float avecx, float avecy, float avecz, float avec1, float avec2, float avec3, int numsubsyms);

  void initsystems(int numsubsyms);
  void initsubsystems(int systemcount, int *subsystemtypes, int *subsystemcounts, float** subsystemvals);
  void removeship(int systemcount);
};

#endif


