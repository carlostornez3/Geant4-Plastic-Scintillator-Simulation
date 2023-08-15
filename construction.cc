#include "construction.hh"
#include <iostream>
G4String MyDetectorConstruction::scintillatorType;
G4String MyDetectorConstruction::scintillatorGeometry;
G4String MyDetectorConstruction::scintillatorNumberOfSensors;
G4int MyDetectorConstruction::scintillatorThickness;
MyDetectorConstruction::MyDetectorConstruction(){
    if(scintillatorType=="EJ208"){
        DefineMaterialsEJ();
    }else if (scintillatorType=="BC404"){
    DefineMaterialsBC();
    }
    
}
MyDetectorConstruction::~MyDetectorConstruction(){}

void MyDetectorConstruction::DefineMaterialsBC(){
      //Scintillation parameters are defined according to a plastic scintillator bc-404. Check https://www.phys.ufl.edu/courses/phy4803L/group_I/muon/bicron_bc400-416.pdf for more details.
   
    std::ifstream fin("bc404.txt");
    std::vector<G4double> energy;
    std::vector<G4double> fraction;
    std::vector<G4double> rindexSC;
    std::vector<G4double> rindexWorld;
    std::vector<G4double> rindexMylar;
    std::vector<G4double> absSC;
    std::vector<G4double> reflectivity;

    G4double RindexSC=1.58,RindexWorld=1.0,RindexMylar=1.655, AbsSC=160.*cm, Reflectivity=0.9999;
    while(!fin.eof()){
        
        fin >> wavelength>>lightOutput;
        G4double Energy=1.239841939*eV/((wavelength/1000));
        lightOutput= lightOutput/100;
        energy.push_back(Energy);
        fraction.push_back(lightOutput);
    }
    G4int numberOfEntries=energy.size();
    
    G4int contador = 0;
    while(contador<numberOfEntries){
        rindexSC.push_back(RindexSC);
        rindexWorld.push_back(RindexWorld);
        rindexMylar.push_back(RindexMylar);
        absSC.push_back(AbsSC);
        reflectivity.push_back(Reflectivity);
        contador++;
    }

    G4OpticalParameters::Instance()->SetScintFiniteRiseTime(true);
    G4NistManager *nist = G4NistManager::Instance();

    //Geant4 what objects are detectors.-Predefined materials are invoked.
    worldMat = nist->FindOrBuildMaterial("G4_AIR");
    SCMat = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
    mylarMat = nist->FindOrBuildMaterial("G4_MYLAR");

    mirrorSurface = new G4OpticalSurface("mirrorSurface");
    mirrorSurface->SetType(dielectric_dielectric);
    mirrorSurface->SetFinish(polishedfrontpainted);
    mirrorSurface->SetModel(unified);

    G4MaterialPropertiesTable *mptSC=new G4MaterialPropertiesTable();
    G4MaterialPropertiesTable *mptWorld=new G4MaterialPropertiesTable();
    G4MaterialPropertiesTable *mptMylar=new G4MaterialPropertiesTable();
    G4MaterialPropertiesTable *mptMirror = new G4MaterialPropertiesTable();

    mptSC->AddProperty("RINDEX",energy, rindexSC,numberOfEntries);
    mptWorld->AddProperty("RINDEX",energy, rindexWorld,numberOfEntries);
    mptSC->AddProperty("SCINTILLATIONCOMPONENT1",energy,fraction,numberOfEntries);
    mptSC->AddConstProperty("SCINTILLATIONYIELD", 10./keV);
    mptSC->AddConstProperty("RESOLUTIONSCALE", 1.);
    mptSC->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 1.8*ns);
    mptSC->AddConstProperty("SCINTILLATIONRISETIME1", 0.7*ns);
    mptSC->AddProperty("ABSLENGTH",energy,absSC,numberOfEntries);
    mptMirror->AddProperty("REFLECTIVITY", energy, reflectivity);;
    mptMylar->AddProperty("RINDEX",energy, rindexMylar,numberOfEntries);
    SCMat->SetMaterialPropertiesTable(mptSC);
    worldMat->SetMaterialPropertiesTable(mptWorld);
    mylarMat->SetMaterialPropertiesTable(mptMylar);
    mirrorSurface->SetMaterialPropertiesTable(mptMirror);
}

void MyDetectorConstruction::DefineMaterialsEJ(){
    
    //Scintillation parameters are defined according to a plastic scintillator bc-404. Check https://www.phys.ufl.edu/courses/phy4803L/group_I/muon/bicron_bc400-416.pdf for more details.
   
    std::ifstream fin("ej208.txt");
    std::vector<G4double> energy;
    std::vector<G4double> fraction;
    std::vector<G4double> rindexSC;
    std::vector<G4double> rindexWorld;
    std::vector<G4double> rindexMylar;
    std::vector<G4double> absSC;
    std::vector<G4double> reflectivity;

    G4double RindexSC=1.58,RindexWorld=1.0,RindexMylar=1.655, AbsSC=400.*cm, Reflectivity=0.9999;
    while(!fin.eof()){
        
        fin >> wavelength>>lightOutput;
        G4double Energy=1.239841939*eV/((wavelength/1000));
        lightOutput= lightOutput/100;
        energy.push_back(Energy);
        fraction.push_back(lightOutput);
    }
    G4int numberOfEntries=energy.size();
    
    G4int contador = 0;
    while(contador<numberOfEntries){
        rindexSC.push_back(RindexSC);
        rindexWorld.push_back(RindexWorld);
        rindexMylar.push_back(RindexMylar);
        absSC.push_back(AbsSC);
        reflectivity.push_back(Reflectivity);
        contador++;
    }

    G4OpticalParameters::Instance()->SetScintFiniteRiseTime(true);
    G4NistManager *nist = G4NistManager::Instance();

    //Geant4 what objects are detectors.-Predefined materials are invoked.
    worldMat = nist->FindOrBuildMaterial("G4_AIR");
    SCMat = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
    mylarMat = nist->FindOrBuildMaterial("G4_MYLAR");

    mirrorSurface = new G4OpticalSurface("mirrorSurface");
    mirrorSurface->SetType(dielectric_dielectric);
    mirrorSurface->SetFinish(polishedfrontpainted);
    mirrorSurface->SetModel(unified);

    G4MaterialPropertiesTable *mptSC=new G4MaterialPropertiesTable();
    G4MaterialPropertiesTable *mptWorld=new G4MaterialPropertiesTable();
    G4MaterialPropertiesTable *mptMylar=new G4MaterialPropertiesTable();
    G4MaterialPropertiesTable *mptMirror = new G4MaterialPropertiesTable();

    mptSC->AddProperty("RINDEX",energy, rindexSC,numberOfEntries);
    mptWorld->AddProperty("RINDEX",energy, rindexWorld,numberOfEntries);
    mptSC->AddProperty("SCINTILLATIONCOMPONENT1",energy,fraction,numberOfEntries);
    mptSC->AddConstProperty("SCINTILLATIONYIELD", 10./keV);
    mptSC->AddConstProperty("RESOLUTIONSCALE", 1.);
    mptSC->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 3.3*ns);
    mptSC->AddConstProperty("SCINTILLATIONRISETIME1", 1.*ns);
    mptSC->AddProperty("ABSLENGTH",energy,absSC,numberOfEntries);
    mptMirror->AddProperty("REFLECTIVITY", energy, reflectivity);;
    mptMylar->AddProperty("RINDEX",energy, rindexMylar,numberOfEntries);
    SCMat->SetMaterialPropertiesTable(mptSC);
    worldMat->SetMaterialPropertiesTable(mptWorld);
    mylarMat->SetMaterialPropertiesTable(mptMylar);
    mirrorSurface->SetMaterialPropertiesTable(mptMirror);
}

G4VPhysicalVolume *MyDetectorConstruction::Construct(){
    
   
    //World volume is created

    G4double xWorld = 1.*m, yWorld= 1.*m, zWorld = 1.*m;
    thickness=scintillatorThickness*mm;
    solidWorld= new G4Box("solidWorld",xWorld,yWorld,zWorld);
    logicWorld = new G4LogicalVolume(solidWorld,worldMat, "logicWorld");
    physWorld =new G4PVPlacement(0,G4ThreeVector(0.,0.,0.),logicWorld,"physWorld",0,false,0,true);
   
    
    if(scintillatorGeometry=="R"){
        rectangularGeometry();
    }else if (scintillatorGeometry=="H"){
        hexagonalGeometry();
    }
    
    
    fScoringVolume=logicSC;

    return physWorld;
} 



//Predefined method used to tell Geant4 what objects are detectors. 
void MyDetectorConstruction::ConstructSDandField(){
    MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");
    
    logicDetector->SetSensitiveDetector(sensDet);
   

    
}
void MyDetectorConstruction::ScintillatorProperties(G4String type,G4String geometry,G4int thickness,G4String numberOfSensors){
    scintillatorType=type;
    scintillatorGeometry=geometry;
    scintillatorThickness = thickness;
    scintillatorNumberOfSensors=numberOfSensors;

}
void MyDetectorConstruction::rectangularGeometry(){


    if(scintillatorNumberOfSensors=="1"){
        G4TwoVector offsetA(0,0), offsetB(0,0);
        G4double scaleA = 1, scaleB = 1;
        
        
        
        G4ThreeVector zTrans(0,0,thickness/2);
        yRot->rotateY(0*rad);
        innerBox = new G4Box("innerBox",2.5*cm,50.*cm,thickness/2);
        externalBox = new G4Box("externalBox",2.6*cm,50.1*cm,(thickness/2)+1*mm);
        sensorBox = new G4Box("sensorBox",3.*mm,3.*mm,1*mm);

        externalInner= new G4SubtractionSolid("External-Inner", externalBox, innerBox);
        externalSensor=new G4SubtractionSolid("external-sensor", externalInner, sensorBox, yRot, zTrans);
        logicMylar= new G4LogicalVolume(externalSensor,mylarMat, "logicMylar");
        G4LogicalSkinSurface *skin = new G4LogicalSkinSurface("skin",logicMylar,mirrorSurface);
        physMylar =new G4PVPlacement(0,G4ThreeVector(0.,0.,10.*cm),logicMylar,"physMylar",logicWorld,false,1,true);

        solidDetector=new G4Box("solidDetector",3.*mm,3.*mm,1.0*mm);
        logicDetector = new G4LogicalVolume(solidDetector,worldMat,"logicalDetector");
        G4VPhysicalVolume *physDetector=new G4PVPlacement(0,G4ThreeVector(0.,0.,101*mm+thickness/2),logicDetector,"physDetector",logicWorld,false,3,true);
    

        G4Box *solidScintillator = new G4Box("solidScintillator",2.5*cm,50.*cm,thickness/2);
        logicSC= new G4LogicalVolume(solidScintillator,SCMat, "logicSC");
        physSC =new G4PVPlacement(0,G4ThreeVector(0.,0.,10.*cm),logicSC,"physSC",logicWorld,false,2,true);
    }

    if(scintillatorNumberOfSensors=="2"){
        G4TwoVector offsetA(0,0), offsetB(0,0);
        G4double scaleA = 1, scaleB = 1;
        
        
        
        G4ThreeVector yTrans1(0,50.*cm,0);
        G4ThreeVector yTrans2(0,-50.*cm,0);
        yRot->rotateY(0*rad);
        innerBox = new G4Box("innerBox",2.5*cm,50.*cm,thickness/2);
        externalBox = new G4Box("externalBox",2.6*cm,50.1*cm,(thickness/2)+1*mm);
        sensorBox = new G4Box("sensorBox",3.*mm,1.*mm,3*mm);

        externalInner= new G4SubtractionSolid("External-Inner", externalBox, innerBox);
        externalSensor1=new G4SubtractionSolid("External-Inner-Sensor1", externalInner, sensorBox, yRot, yTrans1);
        externalSensor2=new G4SubtractionSolid("External-Inner-Sensor2", externalSensor1, sensorBox, yRot, yTrans2);
        logicMylar= new G4LogicalVolume(externalSensor2,mylarMat, "logicMylar");
        G4LogicalSkinSurface *skin = new G4LogicalSkinSurface("skin",logicMylar,mirrorSurface);
        physMylar =new G4PVPlacement(0,G4ThreeVector(0.,0.,10.*cm),logicMylar,"physMylar",logicWorld,false,1,true);

        solidDetector=new G4Box("solidDetector",3.*mm,1.*mm,3.0*mm);
        logicDetector = new G4LogicalVolume(solidDetector,worldMat,"logicalDetector");
        physDetector1=new G4PVPlacement(0,G4ThreeVector(0.,50*cm+1*mm,10*cm),logicDetector,"physDetector1",logicWorld,false,3,true);
        physDetector2=new G4PVPlacement(0,G4ThreeVector(0.,-50*cm-1*mm,10*cm),logicDetector,"physDetector2",logicWorld,false,4,true);

        G4Box *solidScintillator = new G4Box("solidScintillator",2.5*cm,50.*cm,thickness/2);
        logicSC= new G4LogicalVolume(solidScintillator,SCMat, "logicSC");
        physSC =new G4PVPlacement(0,G4ThreeVector(0.,0.,10.*cm),logicSC,"physSC",logicWorld,false,2,true);
    }

}

void MyDetectorConstruction::hexagonalGeometry(){
    //Hexagonal geometry is defined using G4ExtrudedSolid Class
    const G4int nsect = 6;
    std::vector<G4TwoVector> polygon(nsect);
    G4double ang = twopi/nsect;
    G4double rmax = 2.88675*cm;
    for (G4int i = 0; i < nsect; ++i)
    {
    G4double phi = i*ang;
    G4double cosphi = std::cos(phi);
    G4double sinphi = std::sin(phi);
    polygon[i].set(rmax*cosphi, rmax*sinphi);
    }
    G4TwoVector offsetA(0,0), offsetB(0,0);
    G4double scaleA = 1, scaleB = 1;

    //Mylar Volume (External volume)
    std::vector<G4TwoVector> polygonExt(nsect);
    G4double rmaxExt = (26/(std::cos(pi/6)))*mm;
    
    for (G4int i = 0; i < nsect; ++i)
    {
    G4double phi = i*ang;
    G4double cosphi = std::cos(phi);
    G4double sinphi = std::sin(phi);
    polygonExt[i].set(rmaxExt*cosphi, rmaxExt*sinphi);
    }
    
    G4ThreeVector yTrans(0,2.5*cm,0.);
    yRot->rotateY(0*rad);
    //World volume is created
    sensorBox = new G4Box("sensorBox",3.*mm,2.*mm,3.*mm);
    
    
    
    
    xtru = new G4ExtrudedSolid("xtru", polygon, thickness/2, offsetA, scaleA, offsetB, scaleB);
    xtruInner = new G4ExtrudedSolid("xtruInner", polygon, thickness/2, offsetA, scaleA, offsetB, scaleB);

    logicSC= new G4LogicalVolume(xtru,SCMat, "logicSC");
    physSC =new G4PVPlacement(0,G4ThreeVector(0.,0.,10.*cm),logicSC,"physSC",logicWorld,false,0,true);
    xtruExternal= new G4ExtrudedSolid("xtruExternal", polygonExt, (thickness/2)+1*mm, offsetA, scaleA, offsetB, scaleB);
   
    externalInner= new G4SubtractionSolid("External-Inner", xtruExternal, xtruInner);
    externalSensor=new G4SubtractionSolid("external-sensor", externalInner, sensorBox, yRot, yTrans);
    logicMylar= new G4LogicalVolume(externalSensor,mylarMat, "logicMylar");
    G4LogicalSkinSurface *skin = new G4LogicalSkinSurface("skin",logicMylar,mirrorSurface);
    physMylar =new G4PVPlacement(0,G4ThreeVector(0.,0.,10*cm),logicMylar,"physMylar",logicWorld,false,1,true);

    solidDetector=new G4Box("solidDetector",3.*mm,1.*mm,3.0*mm);
    logicDetector = new G4LogicalVolume(solidDetector,worldMat,"logicalDetector");
    G4VPhysicalVolume *physDetector=new G4PVPlacement(0,G4ThreeVector(0.,2.6*cm,10.*cm),logicDetector,"physDetector",logicWorld,false,3,true);
}
