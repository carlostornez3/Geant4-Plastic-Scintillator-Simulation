#include "construction.hh"
#include <iostream>
#include <tuple>
G4String MyDetectorConstruction::scintillatorType;
G4String MyDetectorConstruction::scintillatorGeometry;
G4String MyDetectorConstruction::scintillatorNumberOfSensors;
G4int MyDetectorConstruction::scintillatorThickness;
G4int MyDetectorConstruction::copyNumberSC;
G4String MyDetectorConstruction::scintillatorArrangement;

MyDetectorConstruction::MyDetectorConstruction(){
   
   if(scintillatorArrangement=="SC"){
    
        if(scintillatorType=="EJ208"){
            DefineMaterialsEJ();
        }else if (scintillatorType=="BC404"){
        DefineMaterialsBC();
    }
    }else if(scintillatorArrangement=="SCBT"){
        DefineAllScintillatorsMaterial();
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

void MyDetectorConstruction::DefineAllScintillatorsMaterial(){
//Scintillation parameters are defined according to a plastic scintillator bc-404. Check https://www.phys.ufl.edu/courses/phy4803L/group_I/muon/bicron_bc400-416.pdf for more details.
   
    std::ifstream BCin("bc404.txt");
    std::ifstream EJin("ej208.txt");
    std::vector<G4double> energyBC;
    std::vector<G4double> globalEnergy;
    std::vector<G4double> fractionBC;
    std::vector<G4double> rindexBC;
    std::vector<G4double> rindexWorld;
    std::vector<G4double> rindexMylar;
    std::vector<G4double> absBC;
    std::vector<G4double> reflectivity;
    
    std::vector<G4double> energyEJ;
    std::vector<G4double> fractionEJ;
    std::vector<G4double> rindexEJ;
    std::vector<G4double> absEJ;

    G4double RindexEJ=1.58,RindexWorld=1.0,RindexMylar=1.655, AbsEJ=400.*cm, Reflectivity=0.9999;
    G4double RindexBC=1.58, AbsBC=140.*cm;
    while(!EJin.eof()){
        
        EJin >> wavelength>>lightOutput;
        G4double Energy=1.239841939*eV/((wavelength/1000));
        lightOutput= lightOutput/100;
        energyEJ.push_back(Energy);
        fractionEJ.push_back(lightOutput);
        globalEnergy.push_back(Energy);
    }
    G4int numberOfEntriesEJ=energyEJ.size();
    
    G4int contador = 0;
    while(contador<numberOfEntriesEJ){
        rindexEJ.push_back(RindexEJ);
        absEJ.push_back(AbsEJ);
        contador++;
    }

    while(!BCin.eof()){
        
        BCin >> wavelength>>lightOutput;
        G4double Energy=1.239841939*eV/((wavelength/1000));
        lightOutput= lightOutput/100;
        energyBC.push_back(Energy);
        globalEnergy.push_back(Energy);
        fractionBC.push_back(lightOutput);
    }
    G4int numberOfEntriesBC=energyBC.size();
    G4int globalNumberOfEntries=globalEnergy.size();

     contador = 0;
    while(contador<numberOfEntriesBC){
        rindexBC.push_back(RindexBC);
        absBC.push_back(AbsBC);
        contador++;
    }
    //G4int globalNumberOfEntries=globalEnergy.size();

    contador = 0;
    while(contador<globalNumberOfEntries){
        rindexWorld.push_back(RindexWorld);
        rindexMylar.push_back(RindexMylar);
        reflectivity.push_back(Reflectivity);
        contador++;
    }
    std::sort(globalEnergy.begin(), globalEnergy.end());
    G4OpticalParameters::Instance()->SetScintFiniteRiseTime(true);
    G4NistManager *nist = G4NistManager::Instance();

    //Geant4 what objects are detectors.-Predefined materials are invoked.
    worldMat = nist->FindOrBuildMaterial("G4_AIR");
    BCMat = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
    EJMat = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
    mylarMat = nist->FindOrBuildMaterial("G4_MYLAR");

    mirrorSurface = new G4OpticalSurface("mirrorSurface");
    mirrorSurface->SetType(dielectric_dielectric);
    mirrorSurface->SetFinish(polishedfrontpainted);
    mirrorSurface->SetModel(unified);

    G4MaterialPropertiesTable *mptBC=new G4MaterialPropertiesTable();
    G4MaterialPropertiesTable *mptEJ=new G4MaterialPropertiesTable();
    G4MaterialPropertiesTable *mptWorld=new G4MaterialPropertiesTable();
    G4MaterialPropertiesTable *mptMylar=new G4MaterialPropertiesTable();
    G4MaterialPropertiesTable *mptMirror = new G4MaterialPropertiesTable();

    mptBC->AddProperty("RINDEX",energyBC, rindexBC,numberOfEntriesBC);
    mptEJ->AddProperty("RINDEX",energyEJ, rindexEJ,numberOfEntriesEJ);
    mptWorld->AddProperty("RINDEX",globalEnergy, rindexWorld,globalNumberOfEntries);
    mptBC->AddProperty("SCINTILLATIONCOMPONENT1",energyBC,fractionBC,numberOfEntriesBC);
    mptEJ->AddProperty("SCINTILLATIONCOMPONENT1",energyEJ,fractionEJ,numberOfEntriesEJ);
    mptBC->AddConstProperty("SCINTILLATIONYIELD", 10./keV);
    mptEJ->AddConstProperty("SCINTILLATIONYIELD", 10./keV);
    mptBC->AddConstProperty("RESOLUTIONSCALE", 1.);
    mptEJ->AddConstProperty("RESOLUTIONSCALE", 1.);
    mptBC->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 1.8*ns);
    mptEJ->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 3.3*ns);
    mptBC->AddConstProperty("SCINTILLATIONRISETIME1", 0.7*ns);
    mptEJ->AddConstProperty("SCINTILLATIONRISETIME1", 1.*ns);
    mptBC->AddProperty("ABSLENGTH",energyBC,absBC,numberOfEntriesBC);
    mptEJ->AddProperty("ABSLENGTH",energyEJ,absEJ,numberOfEntriesEJ);
    mptMirror->AddProperty("REFLECTIVITY", globalEnergy, reflectivity);;
    mptMylar->AddProperty("RINDEX",globalEnergy, rindexMylar,globalNumberOfEntries);
    BCMat->SetMaterialPropertiesTable(mptBC);
    EJMat->SetMaterialPropertiesTable(mptEJ);
    worldMat->SetMaterialPropertiesTable(mptWorld);
    mylarMat->SetMaterialPropertiesTable(mptMylar);
    mirrorSurface->SetMaterialPropertiesTable(mptMirror);

}
G4VPhysicalVolume *MyDetectorConstruction::Construct(){
    
   
    //World volume is created

    G4double xWorld = 1.*m, yWorld= 1.*m, zWorld = 2.5*m;
    thickness=scintillatorThickness*mm;
    solidWorld= new G4Box("solidWorld",xWorld,yWorld,zWorld);
    logicWorld = new G4LogicalVolume(solidWorld,worldMat, "logicWorld");
    physWorld =new G4PVPlacement(0,G4ThreeVector(0.,0.,0.),logicWorld,"physWorld",0,false,0,true);
   
    if(scintillatorArrangement=="SC"){
        if(scintillatorGeometry=="R"){
            rectangularGeometry();
        }else if (scintillatorGeometry=="H"){
            hexagonalGeometry();
    }
   }else if(scintillatorArrangement == "SCBT"){
        G4double beamDistance=80.*cm;
        G4double X1Thickness = 1.5*cm, X1Length = 7*cm, X1Width = 10*cm;
        G4double Y1Thickness = 2.*cm, Y1Length = 2*cm, Y1Width= 2*cm;
        G4double BCThickness=2.6*cm, BCLength = 20*cm, BCWidth = 5*cm;
        G4double CZEJThickness = 1.3*cm, SEJThickness = 1.7*cm, AcordeEJThickness= 1.6*cm, UNAMEJThickness = 5.3*cm;
        G4double FermThickness = 5.3*cm, FermLength = 100*cm, FermWidth = 4*cm;
        G4double SCLength = 100*cm, SCWidth = 5*cm;
        G4double X2Thickness=5*cm, X2Length = 10*cm, X2Width = 2*cm;
        G4double detectorLength = 6*mm;
        G4double length = 100*cm, width = 5*cm, thickness = 2.5*cm, sensorLength = 6.*mm, Zcoordinate = 50*cm;


        solidDetector=new G4Box("solidDetector",detectorLength/2,1.*mm,sensorLength/2);
        logicDetectorX1 = new G4LogicalVolume(solidDetector,worldMat,"logicalDetector");
       /* logicDetectorY1=new G4LogicalVolume(solidDetector,worldMat,"logicalDetector");
        logicDetectorBC=new G4LogicalVolume(solidDetector,worldMat,"logicalDetector");
        logicDetectorCZ=new G4LogicalVolume(solidDetector,worldMat,"logicalDetector");
        logicDetectorFerm=new G4LogicalVolume(solidDetector,worldMat,"logicalDetector");
        logicDetectorEJS0=new G4LogicalVolume(solidDetector,worldMat,"logicalDetector");
        logicDetectorEJS1=new G4LogicalVolume(solidDetector,worldMat,"logicalDetector");
        logicDetectorEJS2=new G4LogicalVolume(solidDetector,worldMat,"logicalDetector");
        logicDetectorAcorde=new G4LogicalVolume(solidDetector,worldMat,"logicalDetector");
        logicDetectorUnamEJ=new G4LogicalVolume(solidDetector,worldMat,"logicalDetector");
        logicDetectorX2 = new G4LogicalVolume(solidDetector,worldMat,"logicalDetector");*/
        copyNumberSC=0;
        rectangularPhysicalVolume(X1Length, X1Width, X1Thickness,detectorLength, 0.*cm, 0.*cm, 80.75*cm,BCMat,physX1, logicDetectorX1,"X1SC");
        rectangularPhysicalVolume(Y1Length, Y1Width, Y1Thickness,detectorLength, 0.*cm, 0.*cm, 92.*cm,BCMat,physX1, logicDetectorX1,"Y1SC");
        rectangularPhysicalVolume(length, width, CZEJThickness,detectorLength, 0.*cm, 0.*cm, 124.15*cm,EJMat,physX1, logicDetectorX1,"CZEJ");

        rectangularPhysicalVolume(length, width, SEJThickness,detectorLength, 0.*cm, 0.*cm, 136.25*cm,EJMat,physX1, logicDetectorX1,"SEJ0");

        rectangularPhysicalVolume(length, width, SEJThickness,detectorLength, 0.*cm, 0.*cm, 148.25*cm,EJMat,physX1, logicDetectorX1,"SEJ1");

        rectangularPhysicalVolume(length, width, SEJThickness,detectorLength, 0.*cm, 0.*cm, 160.35*cm,EJMat,physX1, logicDetectorX1,"SEJ2");

        rectangularPhysicalVolume(BCLength, BCWidth, BCThickness,detectorLength, 0.*cm, 0.*cm, 173.4*cm,BCMat,physX1, logicDetectorX1,"BCSC");

        rectangularPhysicalVolume(length, width, AcordeEJThickness,detectorLength, 0.*cm, 0.*cm, 181.6*cm,EJMat,physX1, logicDetectorX1,"ACORDESC");

        rectangularPhysicalVolume(length, width, UNAMEJThickness,detectorLength, 0.*cm, 0.*cm, 188.85*cm,EJMat,physX1, logicDetectorX1,"UNAMEJ");

        rectangularPhysicalVolume(FermLength, FermWidth, FermThickness,detectorLength, 0.*cm, 0.*cm, 194.35*cm,EJMat,physX1, logicDetectorX1, "FERMSC");

        rectangularPhysicalVolume(X2Length, X2Width, X2Thickness,detectorLength, 0.*cm, 0.*cm, 210.1*cm,BCMat,physX1, logicDetectorX1, "X2SC"); 

        
        

        //rectangularPhysicalVolume(Y1Length, X1Width, X1Thickness,detectorLength, 0.*cm, 0.*cm, 70.*cm,BCMat,physY1,physDetectorX1,physDetectorX2, logicDetector);
        //rectangularPhysicalVolume(Y1Length, X1Width, X1Thickness,detectorLength, 0.*cm, 0.*cm, 70.*cm,BCMat,physY1);
       
        
       /*
       
         G4TwoVector offsetA(0,0), offsetB(0,0);
        G4double scaleA = 1, scaleB = 1;
        
        
        
        G4ThreeVector yTrans1(0,length/2,0);
        G4ThreeVector yTrans2(0,-1*length/2,0);
        yRot->rotateY(0*rad);
        innerBox = new G4Box("innerBox",width/2,length/2,thickness/2);
        externalBox = new G4Box("externalBox",(width/2)+1*mm,(length/2)+1*mm,(thickness/2)+1*mm);
        sensorBox = new G4Box("sensorBox",sensorLength/2,1.*mm,sensorLength/2);

        externalInner= new G4SubtractionSolid("External-Inner", externalBox, innerBox);
        externalSensor1=new G4SubtractionSolid("External-Inner-Sensor1", externalInner, sensorBox, yRot, yTrans1);
        externalSensor2=new G4SubtractionSolid("External-Inner-Sensor2", externalSensor1, sensorBox, yRot, yTrans2);
        logicMylar= new G4LogicalVolume(externalSensor2,mylarMat, "logicMylar");
        G4LogicalSkinSurface *skin = new G4LogicalSkinSurface("skin",logicMylar,mirrorSurface);
        physMylar =new G4PVPlacement(0,G4ThreeVector(0.,0.,Zcoordinate),logicMylar,"physMylar",logicWorld,false,1,true);

        solidDetector=new G4Box("solidDetector",sensorLength/2,1.*mm,sensorLength/2);
        logicDetector1 = new G4LogicalVolume(solidDetector,worldMat,"logicalDetector");
        upperDetector=new G4PVPlacement(0,G4ThreeVector(0.,(length/2)+1*mm,Zcoordinate),logicDetector1,"physDetector1",logicWorld,false,3,true);
        lowerDetector =new G4PVPlacement(0,G4ThreeVector(0.,(-1*length/2)-1*mm,Zcoordinate),logicDetector1,"physDetector2",logicWorld,false,4,true);

        G4Box *solidScintillator = new G4Box("solidScintillator",width/2,length/2,thickness/2);
        logicSC= new G4LogicalVolume(solidScintillator,BCMat, "logicSC");
        physX1 =new G4PVPlacement(0,G4ThreeVector(0.,0.,Zcoordinate),logicSC,"physSC",logicWorld,false,2,true);*/

        
    }   /*
        solidDetector=new G4Box("solidDetector",3.*cm,3.*cm,3.0*cm);
        logicDetector = new G4LogicalVolume(solidDetector,worldMat,"logicalDetector");
        G4VPhysicalVolume *physDetector=new G4PVPlacement(0,G4ThreeVector(0.,0.,-10.*cm),logicDetector,"physDetector",logicWorld,false,1,true);*/
    
    fScoringVolume=logicSC;

    return physWorld;
} 



//Predefined method used to tell Geant4 what objects are detectors. 
void MyDetectorConstruction::ConstructSDandField(){
    MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");
    
   //logicDetector->SetSensitiveDetector(sensDet);
    logicDetectorX1->SetSensitiveDetector(sensDet);
    /*logicDetectorY1->SetSensitiveDetector(sensDet);
    logicDetectorBC->SetSensitiveDetector(sensDet);
   logicDetectorCZ->SetSensitiveDetector(sensDet);
    logicDetectorFerm->SetSensitiveDetector(sensDet);
    logicDetectorEJS0->SetSensitiveDetector(sensDet);
    logicDetectorEJS1->SetSensitiveDetector(sensDet);
    logicDetectorEJS2->SetSensitiveDetector(sensDet);
    logicDetectorAcorde->SetSensitiveDetector(sensDet);
    logicDetectorUnamEJ->SetSensitiveDetector(sensDet);
    logicDetectorX2->SetSensitiveDetector(sensDet);*/

    
}
void MyDetectorConstruction::ScintillatorProperties(G4String type,G4String geometry,G4int thickness,G4String numberOfSensors, G4String arrangement){
    scintillatorType=type;
    scintillatorGeometry=geometry;
    scintillatorThickness = thickness;
    scintillatorNumberOfSensors=numberOfSensors;
    scintillatorArrangement=arrangement;

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
void MyDetectorConstruction::rectangularPhysicalVolume(G4double length, G4double width, G4double thickness,G4double sensorLength, G4double Xcoordinate, G4double Ycoordinate, G4double Zcoordinate,G4Material *material, G4VPhysicalVolume *physicalVolume, G4LogicalVolume *logicalDetector, G4String nombre){
        
        G4TwoVector offsetA(0,0), offsetB(0,0);
        G4double scaleA = 1, scaleB = 1;
        
        
        
        G4ThreeVector yTrans1(0,length/2,0);
        G4ThreeVector yTrans2(0,-1*length/2,0);
        yRot->rotateY(0*rad);
        innerBox = new G4Box("innerBox",width/2,length/2,thickness/2);
        externalBox = new G4Box("externalBox",(width/2)+1*mm,(length/2)+1*mm,(thickness/2)+1*mm);
        sensorBox = new G4Box("sensorBox",sensorLength/2,1.*mm,sensorLength/2);

        externalInner= new G4SubtractionSolid("External-Inner", externalBox, innerBox);
        externalSensor1=new G4SubtractionSolid("External-Inner-Sensor1", externalInner, sensorBox, yRot, yTrans1);
        externalSensor2=new G4SubtractionSolid("External-Inner-Sensor2", externalSensor1, sensorBox, yRot, yTrans2);
        logicMylar= new G4LogicalVolume(externalSensor2,mylarMat, "logicMylar");
        G4LogicalSkinSurface *skin = new G4LogicalSkinSurface("skin",logicMylar,mirrorSurface);
        physMylar =new G4PVPlacement(0,G4ThreeVector(0.,0.,Zcoordinate),logicMylar,"physMylar",logicWorld,false,copyNumberSC+1,true);

        

        G4Box *solidScintillator = new G4Box("solidScintillator",width/2,length/2,thickness/2);
        logicSC= new G4LogicalVolume(solidScintillator,material, "logicSC");
        physicalVolume =new G4PVPlacement(0,G4ThreeVector(0.,0.,Zcoordinate),logicSC,"physSC",logicWorld,false,copyNumberSC+2,true);
        
        
        
        upperDetector=new G4PVPlacement(0,G4ThreeVector(0.,(length/2)+1*mm,Zcoordinate),logicalDetector,"physDetector1",logicWorld,false,copyNumberSC+3,true);
        lowerDetector =new G4PVPlacement(0,G4ThreeVector(0.,(-1*length/2)-1*mm,Zcoordinate),logicalDetector,"physDetector2",logicWorld,false,copyNumberSC+4,true);
        G4cout<<nombre<<" "<< " UpperDetector: "<<copyNumberSC+3<<" LowerDetector: "<<copyNumberSC+4<<" PhysicalVolume: "<<copyNumberSC+2<<G4endl;
        copyNumberSC=copyNumberSC+4;
        
}
