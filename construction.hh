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
#include <tuple>
#include "G4SDManager.hh"
#include "barSD.hh"
#include "photonSD.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
    MyDetectorConstruction();
    ~MyDetectorConstruction();
    G4LogicalVolume *GetScoringVolume() const{return fScoringVolume;}
    void rectangularPhysicalVolume(G4double length, G4double width, G4double thickness,G4double sensorLength, G4double Xcoordinate, G4double Ycoordinate, G4double Zcoordinate,G4Material* MylarM ,G4Material *material, G4VPhysicalVolume *physicalVolume, G4LogicalVolume *logicalDetector, G4LogicalVolume *airLayer, G4String nombre);
    void ScintillatorProperties(G4String type,G4String geometry,G4int thickness, G4String numberOfSensors, G4String arrangement);
    void BeamTestConfiguration(G4String arrangement, G4String particleName, G4String numberOfParticles, G4String particleEnergy, G4String numberOfEvents);

    void CreateRPC(G4double length, G4double width, G4double thickness,G4double Xcoordinate, G4double Ycoordinate, G4double Zcoordinate,G4Material* gasMaterial ,G4Material *firstLayerMaterial, G4Material *secondLayerMaterial,  G4String nombre);
        

    virtual G4VPhysicalVolume *Construct();
    static G4String scintillatorType;
    static G4String scintillatorGeometry;
    static G4int scintillatorThickness;
    static G4int copyNumberSC;
    static G4String scintillatorNumberOfSensors;
    static G4String scintillatorArrangement;
    static G4String NumberOfEvents;
    static G4String ParticleEnergy;
    static G4String NumberOfParticles;
    static G4String ParticleName;

   
    G4double wavelength, lightOutput;
    void hexagonalGeometry();
    void rectangularGeometry();
   // void CreateRectangularShell(G4SubtractionSolid *shell,G4double length, G4double width, G4double thickness, G4double shellThickness);
private: 
    G4LogicalVolume *logicDetector;
   

    G4LogicalVolume *logicDetectorZ;
    G4LogicalVolume *logicDetectorX;
    G4LogicalVolume *logicDetectorY;
    G4LogicalVolume *fScoringVolume;
    G4double thickness;
    G4int nCols,nRows;

    G4LogicalVolume *logicDetectorX1 ;
        G4LogicalVolume *logicDetectorY1;
        G4LogicalVolume *logicDetectorBC;
        G4LogicalVolume *logicDetectorCZ;
        G4LogicalVolume *logicDetectorFerm;
        G4LogicalVolume *logicDetectorEJS0;
        G4LogicalVolume *logicDetectorEJS1;
        G4LogicalVolume *logicDetectorEJS2;
        G4LogicalVolume *logicDetectorAcorde;
        G4LogicalVolume *logicDetectorUnamEJ;
        G4LogicalVolume *logicDetectorX2;
        G4LogicalVolume *logicDetectorEJ1,*logicDetectorEJ2,*logicDetectorEJ3,*logicDetectorEJ4,*logicDetectorEJ5,*logicDetectorEJ6,*logicDetectorEJ7,*logicDetectorEJ8;
        G4LogicalVolume *logicDetectorHex,*logicDetectorTR,*logicDetectorDUMP;
        G4LogicalVolume *logicPhotoSensorUpHex, *logicPhotoSensorDownHex;
    virtual void ConstructSDandField();
    
    
    G4Box *solidWorld,*solidDetector, *innerBox,*externalBox,*sensorBox,*solidDetector2;
    G4LogicalVolume *logicWorld,*logicSC, *logicMylar;
    G4LogicalVolume *logicSCX1, *logicSCY1;
    G4VPhysicalVolume *physWorld,*physSC,*physDetectorX1,*physDetectorX2,*physDetector,*physMylar,*physDetectorY1,*physDetectorY2,*physDetector1,*physDetector2, *upperDetector, *lowerDetector;
    G4VSolid* xtru, *xtruExternal, *xtruInner;
    G4SubtractionSolid  *externalInner, *externalSensor1, *externalSensor2,*externalSensor;

    G4VPhysicalVolume *physX1,*physY1, *physBC, *physCZ, *physFerm, *physEJS1, *physEJS2, *physEJS0, *physAcorde, *physUnamEJ, *physX2;

    G4RotationMatrix* yRot = new G4RotationMatrix;

    G4Material *worldMat,*SCMat, *mylarMat,*air,*BCMat, *EJMat;
    G4Material *poly;
    G4Material *aluminium;
    G4Material* Freon;
    G4Material *copper;
    G4OpticalSurface *mirrorSurface;
    void DefineMaterialsBC();
    void DefineMaterialsEJ(); 
    void DefineAllScintillatorsMaterial();
};
#endif
