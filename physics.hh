#ifndef PHYSICS_HH
#define PHYSICS_HH

#include "G4VModularPhysicsList.hh"

class MyPhysicsList : public G4VModularPhysicsList{
  public:
    MyPhysicsList();
    ~MyPhysicsList();
};

#endif
