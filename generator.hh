#ifndef GENERATOR_HH
#define GENERATOR_HH
#include "G4GeneralParticleSource.hh"
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>

#include "construction.hh"

class MyPrimaryGenerator : public G4VUserPrimaryGeneratorAction{
public:
    MyPrimaryGenerator();
    ~MyPrimaryGenerator();
    G4double xCoordinate, yCoordinate,zCoordinate, vectorModule;
    virtual void GeneratePrimaries(G4Event*);
private:
G4ParticleGun *fParticleGun;
G4GeneralParticleSource *particleSource;
};


#endif