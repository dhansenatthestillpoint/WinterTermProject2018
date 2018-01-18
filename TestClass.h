class TestClass{
 public:
  Vec4f posvector;
  Vec4f velvector;
  float *classvarlist;
  
  TestClass(float posx, float posy, float posz, float velx, float vely, float velz);
  
  void updatevelocity(Vec4f accelerationvector);
  void updateposition();
};

class ShipClass: public TestClass
{
 public:
  int *subsystemlist;
  ShipClass(float posx, float posy, float posz, float velx, float vely, float velz, int numsubsyms, int *inputlist);

  void initialize(int numsubsyms, int *inputlist);
}

enum sytemdesignationnumber{Hatches, Dragfins, EmergencyBoosterEngines, Shields};

class SystemStorage{
 public:
  enum systemdesignationnumber systemnum;
  int numsubsys;
  float *subsystemvals;
  SystemStorage(int inputdesignationnumber, int inputsubsystemcount, float *subsystemvals);

  void addspecifiedsystemval(int inputnum, float addamount);
  void modifyspecifiedsystemval(int inputnum, float modamount);
}
