#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction(){
    nCols = 100;
    nRows = 100;
    
    fMessenger=new G4GenericMessenger(this,"/detector/","Detector Construction");
    fMessenger->DeclareProperty("nCols",nCols,"Number of Columns");
    fMessenger->DeclareProperty("nRows",nRows,"Number of Rows");
    
    DefineMaterials();
}
MyDetectorConstruction::~MyDetectorConstruction(){}

void MyDetectorConstruction::DefineMaterials(){
    G4OpticalParameters::Instance()->SetScintFiniteRiseTime(true);
    G4NistManager *nist = G4NistManager::Instance();
    worldMat = nist->FindOrBuildMaterial("G4_AIR");
    SCMat = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");

    G4int numberOfEntries=13;
    std::vector<G4double> energy={1.239841939*eV/0.5,1.239841939*eV/0.490,1.239841939*eV/0.480,1.239841939*eV/0.470,1.239841939*eV/0.460,1.239841939*eV/0.450,1.239841939*eV/0.440,1.239841939*eV/0.430,1.239841939*eV/0.420,1.239841939*eV/0.408,1.239841939*eV/0.400,1.239841939*eV/0.390,1.239841939*eV/0.380};
    std::vector<G4double> rindexSC={1.58,1.58,1.58,1.58,1.58,1.58,1.58,1.58,1.58,1.58,1.58,1.58,1.58,};
    std::vector<G4double> rindexWorld={1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0};
    std::vector<G4double> fraction={0.,0.025,0.05,0.08,0.12,0.2,0.35,0.45,0.55,1.,0.88,0.25,0.05};
    std::vector<G4double> abs={160.*cm,160.*cm,160.*cm,160.*cm,160.*cm,160.*cm,160.*cm,160.*cm,160.*cm,160.*cm,160.*cm,160.*cm,160.*cm};

    G4MaterialPropertiesTable *mptSC=new G4MaterialPropertiesTable();
    G4MaterialPropertiesTable *mptWorld=new G4MaterialPropertiesTable();
    mptSC->AddProperty("RINDEX",energy, rindexSC,numberOfEntries);
    mptWorld->AddProperty("RINDEX",energy, rindexWorld,numberOfEntries);
    mptSC->AddProperty("SCINTILLATIONCOMPONENT1",energy,fraction,numberOfEntries);
    mptSC->AddConstProperty("SCINTILLATIONYIELD", 10./keV);
    mptSC->AddConstProperty("RESOLUTIONSCALE", 1.);
    mptSC->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 1.8*ns);
    mptSC->AddConstProperty("SCINTILLATIONRISETIME1", 0.7*ns);
    mptSC->AddProperty("ABSLENGTH",energy,abs,numberOfEntries);
    SCMat->SetMaterialPropertiesTable(mptSC);
    worldMat->SetMaterialPropertiesTable(mptWorld);
   
}

G4VPhysicalVolume *MyDetectorConstruction::Construct(){
    const G4int nsect = 6;
    std::vector<G4TwoVector> polygon(nsect);
    G4double ang = twopi/nsect;
    G4double rmax = 3.*cm;
    for (G4int i = 0; i < nsect; ++i)
    {
    G4double phi = i*ang;
    G4double cosphi = std::cos(phi);
    G4double sinphi = std::sin(phi);
    polygon[i].set(rmax*cosphi, rmax*sinphi);
    }
    G4TwoVector offsetA(0,0), offsetB(0,0);
    G4double scaleA = 1, scaleB = 1;

    

    G4double xWorld = 0.5*m, yWorld= 0.5*m, zWorld = 0.5*m;
    
    solidWorld= new G4Box("solidWorld",xWorld,yWorld,zWorld);
    logicWorld = new G4LogicalVolume(solidWorld,worldMat, "logicWorld");
    physWorld =new G4PVPlacement(0,G4ThreeVector(0.,0.,0.),logicWorld,"physWorld",0,false,0,true);
    
    /*
    G4Sphere *solidTest= new G4Sphere("solidTest",0,3.*cm,0,2*3.14159,0,3.14159);
    G4LogicalVolume *logicTest = new G4LogicalVolume(solidTest,SCMat, "logicSC");
    G4VPhysicalVolume *physTest =new G4PVPlacement(0,G4ThreeVector(0.,0.,0.),logicTest,"physTest",logicWorld,false,0,true);
    */
    xtru = new G4ExtrudedSolid("xtru", polygon, 0.25*cm, offsetA, scaleA, offsetB, scaleB);
    logicSC= new G4LogicalVolume(xtru,SCMat, "logicSC");
    physSC =new G4PVPlacement(0,G4ThreeVector(0.,0.,5.*cm),logicSC,"physSC",logicWorld,false,0,true);
/*
    solidDetector = new G4Box("solidDetector",xWorld/nRows,yWorld/nCols,0.01*m);
    logicDetector = new G4LogicalVolume(solidDetector,worldMat,"logicalDetector");
    for(G4int i=0;i<nRows;i++){
        for(G4int j=0;j<nCols;j++){
           physDetector=new G4PVPlacement(0,G4ThreeVector(-0.5*m+(i+0.5)*m/nRows,-0.5*m+(j+0.5)*m/nCols,0.49*m),logicDetector,"physDetector",logicWorld,false,j+i*nCols,true);
        }
    }*/
    fScoringVolume=logicSC;

    G4Box *solidDetectorZ = new G4Box("solidDetectorZ",0.5*m,0.5*m,0.01*m);
    logicDetectorZ = new G4LogicalVolume(solidDetectorZ,worldMat,"logicalDetectorZ");
    G4VPhysicalVolume *physDetector1=new G4PVPlacement(0,G4ThreeVector(0.,0.,0.49*m),logicDetectorZ,"physDetector1",logicWorld,false,1,true);
    G4VPhysicalVolume *physDetector2=new G4PVPlacement(0,G4ThreeVector(0.,0.,-0.49*m),logicDetectorZ,"physDetector2",logicWorld,false,2,true);

    G4Box *solidDetectorY = new G4Box("solidDetectorY",0.48*m,0.01*m,0.48*m);
    logicDetectorY = new G4LogicalVolume(solidDetectorY,worldMat,"logicalDetectorY");
    G4VPhysicalVolume *physDetector3=new G4PVPlacement(0,G4ThreeVector(0.,0.49*m,0.),logicDetectorY,"physDetector3",logicWorld,false,3,true);
    G4VPhysicalVolume *physDetector4=new G4PVPlacement(0,G4ThreeVector(0.,-0.49*m,0.),logicDetectorY,"physDetector4",logicWorld,false,4,true);

    G4Box *solidDetectorX = new G4Box("solidDetectorX",0.01*m,0.5*m,0.48*m);
    logicDetectorX = new G4LogicalVolume(solidDetectorX,worldMat,"logicalDetectorX");
    G4VPhysicalVolume *physDetector5=new G4PVPlacement(0,G4ThreeVector(0.49*m,0.,0.),logicDetectorX,"physDetector5",logicWorld,false,5,true);
    G4VPhysicalVolume *physDetector6=new G4PVPlacement(0,G4ThreeVector(-0.49*m,0.,0.),logicDetectorX,"physDetector6",logicWorld,false,6,true);

    return physWorld;
} 
void MyDetectorConstruction::ConstructSDandField(){
    MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");
    //logicDetector->SetSensitiveDetector(sensDet);
    logicDetectorZ->SetSensitiveDetector(sensDet);
    logicDetectorX->SetSensitiveDetector(sensDet);
    logicDetectorY->SetSensitiveDetector(sensDet);

    
}