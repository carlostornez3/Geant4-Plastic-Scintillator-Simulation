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
#include "G4SubtractionSolid.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4String.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
    MyDetectorConstruction();
    ~MyDetectorConstruction();
    G4LogicalVolume *GetScoringVolume() const{return fScoringVolume;}
    void ScintillatorProperties(G4String type,G4String geometry,G4int thickness);
    virtual G4VPhysicalVolume *Construct();
    static G4String scintillatorType;
    static G4String scintillatorGeometry;
    static G4int scintillatorThickness;
    G4double wavelength, lightOutput;
    void hexagonalGeometry();
    void rectangularGeometry();

private: 
    G4LogicalVolume *logicDetector;
    G4LogicalVolume *logicDetectorZ;
    G4LogicalVolume *logicDetectorX;
    G4LogicalVolume *logicDetectorY;
    G4LogicalVolume *fScoringVolume;
    G4double thickness;
    G4int nCols,nRows;
    virtual void ConstructSDandField();
    
    
    G4Box *solidWorld,*solidDetector, *innerBox,*externalBox,*sensorBox,*solidDetector2;
    G4LogicalVolume *logicWorld,*logicSC, *logicMylar;
    G4VPhysicalVolume *physWorld,*physSC,*physDetector,*physMylar;
    G4VSolid* xtru, *xtruExternal, *xtruInner;
    G4SubtractionSolid  *externalInner, *externalSensor;

    G4RotationMatrix* yRot = new G4RotationMatrix;

    G4Material *worldMat,*SCMat, *mylarMat,*air;
    G4OpticalSurface *mirrorSurface;
    void DefineMaterialsBC();
    void DefineMaterialsEJ();
};
#endif
