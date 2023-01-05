#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH


#include "G4SystemOfUnits.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include <assert.h>
#include <cmath>
#include "G4TwoVector.hh"
#include "G4PhysicalConstants.hh"
#include "G4ExtrudedSolid.hh"
#include "G4Polyhedra.hh"
#include "G4TessellatedSolid.hh"
#include "G4OpticalPhysics.hh"
#include "detector.hh"
#include "G4GenericMessenger.hh"
// #include "G4Sphere.hh"
class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
    MyDetectorConstruction();
    ~MyDetectorConstruction();
    G4LogicalVolume *GetScoringVolume() const{return fScoringVolume;}

   virtual G4VPhysicalVolume *Construct();
private: 
    G4LogicalVolume *logicDetector;
    G4LogicalVolume *logicDetectorZ;
    G4LogicalVolume *logicDetectorX;
    G4LogicalVolume *logicDetectorY;
    G4LogicalVolume *fScoringVolume;
    
    G4int nCols,nRows;
    virtual void ConstructSDandField();
    
    G4GenericMessenger *fMessenger;
    
    G4Box *solidWorld,*solidDetector;
    G4LogicalVolume *logicWorld,*logicSC;
    G4VPhysicalVolume *physWorld,*physSC,*physDetector;
    G4VSolid* xtru;


    G4Material *worldMat,*SCMat;
    void DefineMaterials();
};
#endif