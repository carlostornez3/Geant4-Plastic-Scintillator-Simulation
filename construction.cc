#include "construction.hh"
#include <iostream>
#include <tuple>
G4String MyDetectorConstruction::scintillatorType;
G4String MyDetectorConstruction::scintillatorGeometry;
G4String MyDetectorConstruction::scintillatorNumberOfSensors;
G4int MyDetectorConstruction::scintillatorThickness;
G4int MyDetectorConstruction::copyNumberSC;
G4String MyDetectorConstruction::scintillatorArrangement;
G4String MyDetectorConstruction::NumberOfEvents;
G4String MyDetectorConstruction::ParticleEnergy;
G4String MyDetectorConstruction::NumberOfParticles;
G4String MyDetectorConstruction::ParticleName;


MyDetectorConstruction::MyDetectorConstruction(){
   
   if(scintillatorArrangement=="SC" ){
    
        if(scintillatorType=="EJ208"){
            DefineMaterialsEJ();
        }else if (scintillatorType=="BC404"){
        DefineMaterialsBC();
    }
    }else if(scintillatorArrangement=="SCBT"|| MyDetectorConstruction::scintillatorArrangement == "RPCBT"){
        DefineAllScintillatorsMaterial();
       // DefineMaterialsBC();
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
    G4NistManager *nist = G4NistManager::Instance();

    std::ifstream BCin("bc404.txt");
    std::ifstream EJin("ej208.txt");
    std::ifstream allin("wave.txt");
   
    std::vector<G4double> energyBC;
    std::vector<G4double> fractionBC;
    std::vector<G4double> rindexBC;
    std::vector<G4double> absBC;

    std::vector<G4double> energyEJ;
    std::vector<G4double> fractionEJ;
    std::vector<G4double> rindexEJ;
    std::vector<G4double> absEJ;
    
    
    std::vector<G4double> rindexWorld;
    std::vector<G4double> rindexMylar;
    std::vector<G4double> reflectivity;
    

    std::vector<G4double>  energies;

    G4double RindexBC=1.58, AbsBC=160.*cm;
    G4double RindexEJ=1.58, AbsEJ=400.*cm;
    G4double RindexWorld=1.0,RindexMylar=1.655,Reflectivity=0.9999;

    while(!BCin.eof()){
        
        BCin >> wavelength>>lightOutput;
        G4double Energy=1.239841939*eV/((wavelength/1000));
        lightOutput= lightOutput/100;
        energyBC.push_back(Energy);
        fractionBC.push_back(lightOutput);
        rindexBC.push_back(RindexBC);
        
        absBC.push_back(AbsBC);

    }

    while(!EJin.eof()){
        
        EJin >> wavelength>>lightOutput;
        G4double Energy=1.239841939*eV/((wavelength/1000));
        lightOutput= lightOutput/100;
        energyEJ.push_back(Energy);
        fractionEJ.push_back(lightOutput);
        rindexEJ.push_back(RindexEJ);
        
        absEJ.push_back(AbsEJ);

    }

    while(!allin.eof()){
        allin>> wavelength;
        G4double Energy = 1.239841939*eV/((wavelength/1000));
        rindexWorld.push_back(RindexWorld);
        rindexMylar.push_back(RindexMylar);
        reflectivity.push_back(Reflectivity);
        energies.push_back(Energy);
    }
    G4int globalEntries = energies.size();
    G4int BCentries = energyBC.size();
    G4int EJentries = energyEJ.size();
        worldMat = nist->FindOrBuildMaterial("G4_AIR");
        //EJMat = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
        BCMat = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
        
        mylarMat = nist->FindOrBuildMaterial("G4_MYLAR");
        aluminium =nist-> FindOrBuildMaterial("G4_ALUMINUM_OXIDE");
        copper = nist->FindOrBuildMaterial("G4_Cu");


        mirrorSurface = new G4OpticalSurface("mirrorSurface");
        mirrorSurface->SetType(dielectric_dielectric);
        mirrorSurface->SetFinish(polishedfrontpainted);
        mirrorSurface->SetModel(unified);

    G4String name, symbol;
    G4double atomicNumber, atomicMass,fractionmass,ncomponents;

    G4Element *C =new G4Element(name = "Carbon", symbol = "C", atomicNumber = 6,atomicMass = 12*g/mole);
    G4Element *H =new G4Element(name = "Hydrogen", symbol = "H", atomicNumber = 1,atomicMass = 1.00784*g/mole);
    G4Element *F =new G4Element(name = "Fluor", symbol = "F", atomicNumber = 9,atomicMass = 18.998403*g/mole);

    G4double density = 1.2072 *g/cm3;
    Freon= new G4Material("Freon", density, 3);
    Freon->AddElement(C,2);
    Freon->AddElement(F,4);
    Freon->AddElement(H,2);
    EJMat = new G4Material(name = "EJmat", 1.023*g/cm3, ncomponents=2);
    EJMat->AddElement(C,fractionmass=91.5*perCent);
    EJMat->AddElement(H,fractionmass=8.5*perCent);


    G4MaterialPropertiesTable *mptBC=new G4MaterialPropertiesTable();
    G4MaterialPropertiesTable *mptEJ=new G4MaterialPropertiesTable();
    G4MaterialPropertiesTable *mptWorld=new G4MaterialPropertiesTable();
    G4MaterialPropertiesTable *mptMylar=new G4MaterialPropertiesTable();
    G4MaterialPropertiesTable *mptMirror = new G4MaterialPropertiesTable();

    mptBC->AddProperty("RINDEX",energyBC, rindexBC,BCentries);
    mptBC->AddProperty("SCINTILLATIONCOMPONENT1",energyBC,fractionBC,BCentries);
    mptBC->AddConstProperty("SCINTILLATIONYIELD", 10./keV);
    mptBC->AddConstProperty("RESOLUTIONSCALE", 1.);
    mptBC->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 1.8*ns);
    mptBC->AddConstProperty("SCINTILLATIONRISETIME1", 0.7*ns);
    mptBC->AddProperty("ABSLENGTH",energyBC,absBC,BCentries);
    BCMat->SetMaterialPropertiesTable(mptBC);

    mptEJ->AddProperty("RINDEX",energyEJ, rindexEJ,EJentries);
    mptEJ->AddProperty("SCINTILLATIONCOMPONENT1",energyEJ,fractionEJ,EJentries);
    mptEJ->AddConstProperty("SCINTILLATIONYIELD", 10./keV);
    mptEJ->AddConstProperty("RESOLUTIONSCALE", 1.);
    mptEJ->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 3.3*ns);
    mptEJ->AddConstProperty("SCINTILLATIONRISETIME1", 1.*ns);
    mptEJ->AddProperty("ABSLENGTH",energyEJ,absEJ,EJentries);
    EJMat->SetMaterialPropertiesTable(mptEJ);

    

    
    


    mptWorld->AddProperty("RINDEX",energies, rindexWorld,globalEntries);
    mptMirror->AddProperty("REFLECTIVITY", energies, reflectivity);
    mptMylar->AddProperty("RINDEX",energies, rindexMylar,globalEntries);
    worldMat->SetMaterialPropertiesTable(mptWorld);
    mylarMat->SetMaterialPropertiesTable(mptMylar);
    mirrorSurface->SetMaterialPropertiesTable(mptMirror);

}
G4VPhysicalVolume *MyDetectorConstruction::Construct(){
    
   
    //World volume is created

    G4double xWorld = 1.5*m, yWorld= 1.5*m, zWorld = 8.5*m;
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
   } else if(scintillatorArrangement == "RPCBT" || scintillatorArrangement == "SCBT"){
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
        G4double airDetectorLayerThickness = 0.5*mm;
        G4double EJ1length = 50*cm,EJ2length=80*cm, EJ1width=50*cm, EJ2width=80*cm, EJ1thickness=3.5*cm, EJ2thickness=2.5*cm;
        solidDetector=new G4Box("solidDetector",detectorLength/2,1.*mm,sensorLength/2);
        logicDetector = new G4LogicalVolume(solidDetector,worldMat,"logicalDetector");
        G4double TRthickness = 1.5*cm,TRLength = 7*cm, TRwidth = 10*cm;
        G4double DUMPlength=20*cm, DUMPwidth=20*cm, DUMPthickness=2*cm;
        G4double RPClength = 33*cm, RPCwidth = 31*cm, RPCthickness= 2.2*cm;
       
        copyNumberSC=0;


        
        
        G4Box * sensorBox1 = new G4Box("sensorBox",sensorLength/2,0.75*m,sensorLength/2);

        
    
        G4Box * InnerBox = new G4Box("sensorBox",(X1Width/2)+1*mm,(X1Length/2)+1*mm,X1Thickness/2+1*mm);
        G4Box* ExternalBox=new G4Box("sensorBox",(X1Width/2)+1*mm+airDetectorLayerThickness,(X1Length/2)+1*mm+airDetectorLayerThickness,X1Thickness/2+1*mm+airDetectorLayerThickness);
        G4SubtractionSolid * ExternalInner = new G4SubtractionSolid("External-Inner", ExternalBox, InnerBox);
        G4SubtractionSolid * rectangularShell =new G4SubtractionSolid("External-Inner-Sensor2", ExternalInner, sensorBox1);
        logicDetectorX1 = new G4LogicalVolume(rectangularShell,worldMat,"logicalDetector");
        rectangularPhysicalVolume(X1Length, X1Width, X1Thickness,detectorLength, 0.*cm, 0.*cm, 80.75*cm,mylarMat,BCMat,physSC, logicDetector,logicDetectorX1,"X1SC");

        

        InnerBox = new G4Box("sensorBox",(Y1Width/2)+1*mm,(Y1Length/2)+1*mm,Y1Thickness/2+1*mm);
        ExternalBox=new G4Box("sensorBox",(Y1Width/2)+1*mm+airDetectorLayerThickness,(Y1Length/2)+1*mm+airDetectorLayerThickness,Y1Thickness/2+1*mm+airDetectorLayerThickness);
        ExternalInner = new G4SubtractionSolid("External-Inner", ExternalBox, InnerBox);
        rectangularShell =new G4SubtractionSolid("External-Inner-Sensor2", ExternalInner, sensorBox1);
        logicDetectorY1 = new G4LogicalVolume(rectangularShell,worldMat,"logicalDetector");
        rectangularPhysicalVolume(Y1Length, Y1Width, Y1Thickness,detectorLength, 0.*cm, 0.*cm, 92.*cm,mylarMat,BCMat,physSC, logicDetector,logicDetectorY1,"Y1SC");

        
        InnerBox = new G4Box("sensorBox",(width/2)+1*mm,(length/2)+1*mm,CZEJThickness/2+1*mm);
        ExternalBox=new G4Box("sensorBox",(width/2)+1*mm+airDetectorLayerThickness,(length/2)+1*mm+airDetectorLayerThickness,CZEJThickness/2+1*mm+airDetectorLayerThickness);
        ExternalInner = new G4SubtractionSolid("External-Inner", ExternalBox, InnerBox);
        rectangularShell =new G4SubtractionSolid("External-Inner-Sensor2", ExternalInner, sensorBox1);
       // CreateRectangularShell(rectangularShell,length, width, CZEJThickness,airDetectorLayerThickness);
        logicDetectorCZ = new G4LogicalVolume(rectangularShell,worldMat,"logicalDetector");
        rectangularPhysicalVolume(length, width, CZEJThickness,detectorLength, 0.*cm, 0.*cm, 124.15*cm,mylarMat,EJMat,physSC, logicDetector,logicDetectorCZ,"CZEJ");



        InnerBox = new G4Box("sensorBox",(width/2)+1*mm,(length/2)+1*mm,SEJThickness/2+1*mm);
        ExternalBox=new G4Box("sensorBox",(width/2)+1*mm+airDetectorLayerThickness,(length/2)+1*mm+airDetectorLayerThickness,SEJThickness/2+1*mm+airDetectorLayerThickness);
        ExternalInner = new G4SubtractionSolid("External-Inner", ExternalBox, InnerBox);
        rectangularShell =new G4SubtractionSolid("External-Inner-Sensor2", ExternalInner, sensorBox1);
        logicDetectorEJS0 = new G4LogicalVolume(rectangularShell,worldMat,"logicalDetector");
        rectangularPhysicalVolume(length, width, SEJThickness,detectorLength, 0.*cm, 0.*cm, 136.25*cm,mylarMat,EJMat,physSC, logicDetector,logicDetectorEJS0,"SEJ0");


        InnerBox = new G4Box("sensorBox",(width/2)+1*mm,(length/2)+1*mm,SEJThickness/2+1*mm);
        ExternalBox=new G4Box("sensorBox",(width/2)+1*mm+airDetectorLayerThickness,(length/2)+1*mm+airDetectorLayerThickness,SEJThickness/2+1*mm+airDetectorLayerThickness);
        ExternalInner = new G4SubtractionSolid("External-Inner", ExternalBox, InnerBox);
        rectangularShell =new G4SubtractionSolid("External-Inner-Sensor2", ExternalInner, sensorBox1);
        logicDetectorEJS1 = new G4LogicalVolume(rectangularShell,worldMat,"logicalDetector");
        rectangularPhysicalVolume(length, width, SEJThickness,detectorLength, 0.*cm, 0.*cm, 148.25*cm,mylarMat,EJMat,physSC, logicDetector,logicDetectorEJS1,"SEJ1");
        
        InnerBox = new G4Box("sensorBox",(width/2)+1*mm,(length/2)+1*mm,SEJThickness/2+1*mm);
        ExternalBox=new G4Box("sensorBox",(width/2)+1*mm+airDetectorLayerThickness,(length/2)+1*mm+airDetectorLayerThickness,SEJThickness/2+1*mm+airDetectorLayerThickness);
        ExternalInner = new G4SubtractionSolid("External-Inner", ExternalBox, InnerBox);
        rectangularShell =new G4SubtractionSolid("External-Inner-Sensor2", ExternalInner, sensorBox1);
        logicDetectorEJS2 = new G4LogicalVolume(rectangularShell,worldMat,"logicalDetector");
        rectangularPhysicalVolume(length, width, SEJThickness,detectorLength, 0.*cm, 0.*cm, 160.35*cm,mylarMat,EJMat,physSC, logicDetector,logicDetectorEJS2,"SEJ2");


        InnerBox = new G4Box("sensorBox",(BCWidth/2)+1*mm,(BCLength/2)+1*mm,BCThickness/2+1*mm);
        ExternalBox=new G4Box("sensorBox",(BCWidth/2)+1*mm+airDetectorLayerThickness,(BCLength/2)+1*mm+airDetectorLayerThickness,BCThickness/2+1*mm+airDetectorLayerThickness);
        ExternalInner = new G4SubtractionSolid("External-Inner", ExternalBox, InnerBox);
        rectangularShell =new G4SubtractionSolid("External-Inner-Sensor2", ExternalInner, sensorBox1);
        logicDetectorBC = new G4LogicalVolume(rectangularShell,worldMat,"logicalDetector");
        rectangularPhysicalVolume(BCLength, BCWidth, BCThickness,detectorLength, 0.*cm, 0.*cm, 173.4*cm,mylarMat,BCMat,physSC, logicDetector,logicDetectorBC,"BCSC");


        InnerBox = new G4Box("sensorBox",(width/2)+1*mm,(length/2)+1*mm,AcordeEJThickness/2+1*mm);
        ExternalBox=new G4Box("sensorBox",(width/2)+1*mm+airDetectorLayerThickness,(length/2)+1*mm+airDetectorLayerThickness,AcordeEJThickness/2+1*mm+airDetectorLayerThickness);
        ExternalInner = new G4SubtractionSolid("External-Inner", ExternalBox, InnerBox);
        rectangularShell =new G4SubtractionSolid("External-Inner-Sensor2", ExternalInner, sensorBox1);
        logicDetectorAcorde = new G4LogicalVolume(rectangularShell,worldMat,"logicalDetector");
        rectangularPhysicalVolume(length, width, AcordeEJThickness,detectorLength, 0.*cm, 0.*cm, 181.6*cm,mylarMat,EJMat,physSC, logicDetector,logicDetectorAcorde,"ACORDESC");


        InnerBox = new G4Box("sensorBox",(width/2)+1*mm,(length/2)+1*mm,UNAMEJThickness/2+1*mm);
        ExternalBox=new G4Box("sensorBox",(width/2)+1*mm+airDetectorLayerThickness,(length/2)+1*mm+airDetectorLayerThickness,UNAMEJThickness/2+1*mm+airDetectorLayerThickness);
        ExternalInner = new G4SubtractionSolid("External-Inner", ExternalBox, InnerBox);
        rectangularShell =new G4SubtractionSolid("External-Inner-Sensor2", ExternalInner, sensorBox1);
        logicDetectorUnamEJ = new G4LogicalVolume(rectangularShell,worldMat,"logicalDetector");
        rectangularPhysicalVolume(length, width, UNAMEJThickness,detectorLength, 0.*cm, 0.*cm, 188.70*cm,mylarMat,EJMat,physSC, logicDetector,logicDetectorUnamEJ,"UNAMEJ");


        InnerBox = new G4Box("sensorBox",(FermWidth/2)+1*mm,(FermLength/2)+1*mm,FermThickness/2+1*mm);
        ExternalBox=new G4Box("sensorBox",(FermWidth/2)+1*mm+airDetectorLayerThickness,(FermLength/2)+1*mm+airDetectorLayerThickness,FermThickness/2+1*mm+airDetectorLayerThickness);
        ExternalInner = new G4SubtractionSolid("External-Inner", ExternalBox, InnerBox);
        rectangularShell =new G4SubtractionSolid("External-Inner-Sensor2", ExternalInner, sensorBox1);
        logicDetectorFerm = new G4LogicalVolume(rectangularShell,worldMat,"logicalDetector");
        rectangularPhysicalVolume(FermLength, FermWidth, FermThickness,detectorLength, 0.*cm, 0.*cm, 194.35*cm,mylarMat,EJMat,physSC, logicDetector,logicDetectorFerm, "FERMSC");


        InnerBox = new G4Box("sensorBox",(X2Width/2)+1*mm,(X2Length/2)+1*mm,X2Thickness/2+1*mm);
        ExternalBox=new G4Box("sensorBox",(X2Width/2)+1*mm+airDetectorLayerThickness,(X2Length/2)+1*mm+airDetectorLayerThickness,X2Thickness/2+1*mm+airDetectorLayerThickness);
        ExternalInner = new G4SubtractionSolid("External-Inner", ExternalBox, InnerBox);
        rectangularShell =new G4SubtractionSolid("External-Inner-Sensor2", ExternalInner, sensorBox1);
        logicDetectorX2 = new G4LogicalVolume(rectangularShell,worldMat,"logicalDetector");
        rectangularPhysicalVolume(X2Length, X2Width, X2Thickness,detectorLength, 0.*cm, 0.*cm, 209.9*cm,mylarMat,BCMat,physSC, logicDetector, logicDetectorX2,"X2SC");

        ////////////////////////////////////////////////////////////////////////////////////////

        InnerBox = new G4Box("sensorBox",(EJ1width/2)+1*mm,(EJ1length/2)+1*mm,EJ1thickness/2+1*mm);
        ExternalBox=new G4Box("sensorBox",(EJ1width/2)+1*mm+airDetectorLayerThickness,(EJ1length/2)+1*mm+airDetectorLayerThickness,EJ1thickness/2+1*mm+airDetectorLayerThickness);
        ExternalInner = new G4SubtractionSolid("External-Inner", ExternalBox, InnerBox);
        rectangularShell =new G4SubtractionSolid("External-Inner-Sensor2", ExternalInner, sensorBox1);
        logicDetectorEJ1 = new G4LogicalVolume(rectangularShell,worldMat,"logicalDetector");
        rectangularPhysicalVolume(EJ1length, EJ1width, EJ1thickness,detectorLength, 0.*cm, 0.*cm, 248.65*cm,mylarMat,EJMat,physSC, logicDetector, logicDetectorEJ1,"EJ1");

        InnerBox = new G4Box("sensorBox",(EJ1width/2)+1*mm,(EJ1length/2)+1*mm,EJ1thickness/2+1*mm);
        ExternalBox=new G4Box("sensorBox",(EJ1width/2)+1*mm+airDetectorLayerThickness,(EJ1length/2)+1*mm+airDetectorLayerThickness,EJ1thickness/2+1*mm+airDetectorLayerThickness);
        ExternalInner = new G4SubtractionSolid("External-Inner", ExternalBox, InnerBox);
        rectangularShell =new G4SubtractionSolid("External-Inner-Sensor2", ExternalInner, sensorBox1);
        logicDetectorEJ2 = new G4LogicalVolume(rectangularShell,worldMat,"logicalDetector");
        rectangularPhysicalVolume(EJ1length, EJ1width, EJ1thickness,detectorLength, 0.*cm, 0.*cm, 254.15*cm,mylarMat,EJMat,physSC, logicDetector, logicDetectorEJ2,"EJ2");

        InnerBox = new G4Box("sensorBox",(EJ1width/2)+1*mm,(EJ1length/2)+1*mm,EJ1thickness/2+1*mm);
        ExternalBox=new G4Box("sensorBox",(EJ1width/2)+1*mm+airDetectorLayerThickness,(EJ1length/2)+1*mm+airDetectorLayerThickness,EJ1thickness/2+1*mm+airDetectorLayerThickness);
        ExternalInner = new G4SubtractionSolid("External-Inner", ExternalBox, InnerBox);
        rectangularShell =new G4SubtractionSolid("External-Inner-Sensor2", ExternalInner, sensorBox1);
        logicDetectorEJ3 = new G4LogicalVolume(rectangularShell,worldMat,"logicalDetector");
        rectangularPhysicalVolume(EJ1length, EJ1width, EJ1thickness,detectorLength, 0.*cm, 0.*cm, 352.65*cm,mylarMat,EJMat,physSC, logicDetector, logicDetectorEJ3,"EJ3");


        InnerBox = new G4Box("sensorBox",(EJ1width/2)+1*mm,(EJ1length/2)+1*mm,EJ1thickness/2+1*mm);
        ExternalBox=new G4Box("sensorBox",(EJ1width/2)+1*mm+airDetectorLayerThickness,(EJ1length/2)+1*mm+airDetectorLayerThickness,EJ1thickness/2+1*mm+airDetectorLayerThickness);
        ExternalInner = new G4SubtractionSolid("External-Inner", ExternalBox, InnerBox);
        rectangularShell =new G4SubtractionSolid("External-Inner-Sensor2", ExternalInner, sensorBox1);
        logicDetectorEJ4 = new G4LogicalVolume(rectangularShell,worldMat,"logicalDetector");
        rectangularPhysicalVolume(EJ1length, EJ1width, EJ1thickness,detectorLength, 0.*cm, 0.*cm, 358.15*cm,mylarMat,EJMat,physSC, logicDetector, logicDetectorEJ4,"EJ4");


        ////////



        InnerBox = new G4Box("sensorBox",(EJ2width/2)+1*mm,(EJ2length/2)+1*mm,EJ2thickness/2+1*mm);
        ExternalBox=new G4Box("sensorBox",(EJ2width/2)+1*mm+airDetectorLayerThickness,(EJ2length/2)+1*mm+airDetectorLayerThickness,EJ2thickness/2+1*mm+airDetectorLayerThickness);
        ExternalInner = new G4SubtractionSolid("External-Inner", ExternalBox, InnerBox);
        rectangularShell =new G4SubtractionSolid("External-Inner-Sensor2", ExternalInner, sensorBox1);
        logicDetectorEJ5 = new G4LogicalVolume(rectangularShell,worldMat,"logicalDetector");
        rectangularPhysicalVolume(EJ2length, EJ2width, EJ2thickness,detectorLength, 0.*cm, 0.*cm, 488.45*cm,mylarMat,EJMat,physSC, logicDetector, logicDetectorEJ5,"EJ5");

        InnerBox = new G4Box("sensorBox",(EJ2width/2)+1*mm,(EJ2length/2)+1*mm,EJ2thickness/2+1*mm);
        ExternalBox=new G4Box("sensorBox",(EJ2width/2)+1*mm+airDetectorLayerThickness,(EJ2length/2)+1*mm+airDetectorLayerThickness,EJ2thickness/2+1*mm+airDetectorLayerThickness);
        ExternalInner = new G4SubtractionSolid("External-Inner", ExternalBox, InnerBox);
        rectangularShell =new G4SubtractionSolid("External-Inner-Sensor2", ExternalInner, sensorBox1);
        logicDetectorEJ6 = new G4LogicalVolume(rectangularShell,worldMat,"logicalDetector");
        rectangularPhysicalVolume(EJ2length, EJ2width, EJ2thickness,detectorLength, 0.*cm, 0.*cm, 498.45*cm,mylarMat,EJMat,physSC, logicDetector, logicDetectorEJ6,"EJ6");

        InnerBox = new G4Box("sensorBox",(EJ2width/2)+1*mm,(EJ2length/2)+1*mm,EJ2thickness/2+1*mm);
        ExternalBox=new G4Box("sensorBox",(EJ2width/2)+1*mm+airDetectorLayerThickness,(EJ2length/2)+1*mm+airDetectorLayerThickness,EJ2thickness/2+1*mm+airDetectorLayerThickness);
        ExternalInner = new G4SubtractionSolid("External-Inner", ExternalBox, InnerBox);
        rectangularShell =new G4SubtractionSolid("External-Inner-Sensor2", ExternalInner, sensorBox1);
        logicDetectorEJ7 = new G4LogicalVolume(rectangularShell,worldMat,"logicalDetector");
        rectangularPhysicalVolume(EJ2length, EJ2width, EJ2thickness,detectorLength, 0.*cm, 0.*cm, 508.45*cm,mylarMat,EJMat,physSC, logicDetector, logicDetectorEJ7,"EJ7");


        InnerBox = new G4Box("sensorBox",(EJ2width/2)+1*mm,(EJ2length/2)+1*mm,EJ2thickness/2+1*mm);
        ExternalBox=new G4Box("sensorBox",(EJ2width/2)+1*mm+airDetectorLayerThickness,(EJ2length/2)+1*mm+airDetectorLayerThickness,EJ2thickness/2+1*mm+airDetectorLayerThickness);
        ExternalInner = new G4SubtractionSolid("External-Inner", ExternalBox, InnerBox);
        rectangularShell =new G4SubtractionSolid("External-Inner-Sensor2", ExternalInner, sensorBox1);
        logicDetectorEJ8 = new G4LogicalVolume(rectangularShell,worldMat,"logicalDetector");
        rectangularPhysicalVolume(EJ2length, EJ2width, EJ2thickness,detectorLength, 0.*cm, 0.*cm, 518.45*cm,mylarMat,EJMat,physSC, logicDetector, logicDetectorEJ8,"EJ8");





        InnerBox = new G4Box("sensorBox",(TRwidth/2)+1*mm,(TRLength/2)+1*mm,TRthickness/2+1*mm);
        ExternalBox=new G4Box("sensorBox",(TRwidth/2)+1*mm+airDetectorLayerThickness,(TRLength/2)+1*mm+airDetectorLayerThickness,TRthickness/2+1*mm+airDetectorLayerThickness);
        ExternalInner = new G4SubtractionSolid("External-Inner", ExternalBox, InnerBox);
        rectangularShell =new G4SubtractionSolid("External-Inner-Sensor2", ExternalInner, sensorBox1);
        logicDetectorTR = new G4LogicalVolume(rectangularShell,worldMat,"logicalDetector");
        rectangularPhysicalVolume(TRLength, TRwidth, TRthickness,detectorLength, 0.*cm, 0.*cm, 789.45*cm,mylarMat,BCMat,physSC, logicDetector, logicDetectorTR,"TR");

        

        



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

        std::vector<G4TwoVector> polygonExtlayer(nsect);
        G4double rmaxExtlayer = (26*mm+airDetectorLayerThickness/(std::cos(pi/6)));
        
        for (G4int i = 0; i < nsect; ++i)
        {
        G4double phi = i*ang;
        G4double cosphi = std::cos(phi);
        G4double sinphi = std::sin(phi);
        polygonExtlayer[i].set(rmaxExtlayer*cosphi, rmaxExtlayer*sinphi);
        }
        
        
        sensorBox = new G4Box("sensorBox",3.*mm,0.75*m,3.*mm);


        
        G4double zcoordinate = 401.15*cm;
        //G4double zcoordinate = 40.15*cm;
        thickness = 2.1*cm;
        
        xtru = new G4ExtrudedSolid("xtru", polygon, thickness/2, offsetA, scaleA, offsetB, scaleB);
        G4ExtrudedSolid* xtrulayer = new G4ExtrudedSolid("xtrulayer", polygonExtlayer, (thickness/2)+1*mm+airDetectorLayerThickness, offsetA, scaleA, offsetB, scaleB);


        G4LogicalVolume* logicHEX= new G4LogicalVolume(xtru,BCMat, "logicHex");
        G4VPhysicalVolume* physHEX =new G4PVPlacement(0,G4ThreeVector(0.,0.,zcoordinate),logicHEX,"physSC",logicWorld,false,copyNumberSC+2,true); ////////////////
        
        xtruExternal= new G4ExtrudedSolid("xtruExternal", polygonExt, (thickness/2)+1*mm, offsetA, scaleA, offsetB, scaleB);
    
        externalInner= new G4SubtractionSolid("External-Inner", xtruExternal, xtru);
        externalSensor=new G4SubtractionSolid("external-sensor", externalInner, sensorBox);
        logicMylar= new G4LogicalVolume(externalSensor,mylarMat, "logicMylar");
        G4LogicalSkinSurface *skin = new G4LogicalSkinSurface("skin",logicMylar,mirrorSurface);
        physMylar =new G4PVPlacement(0,G4ThreeVector(0.,0.,zcoordinate),logicMylar,"physMylar",logicWorld,false,copyNumberSC+3,true); //////////////////////

        solidDetector=new G4Box("solidDetector",3.*mm,1.*mm,3.0*mm);
        logicPhotoSensorUpHex= new G4LogicalVolume(solidDetector,worldMat,"logicalDetector");
        G4VPhysicalVolume *physDetector=new G4PVPlacement(0,G4ThreeVector(0.,2.6*cm,zcoordinate),logicPhotoSensorUpHex,"physDetector",logicWorld,false,copyNumberSC+4,true);////////////
        physDetector=new G4PVPlacement(0,G4ThreeVector(0.,-2.6*cm,zcoordinate),logicPhotoSensorUpHex,"physDetector",logicWorld,false,copyNumberSC+5,true);////////////////

        G4SubtractionSolid* externalLayer=new G4SubtractionSolid("external-sensor", xtrulayer, xtruExternal);
        G4SubtractionSolid *airLayerSolid=new G4SubtractionSolid("external-sensor", externalLayer, sensorBox);
        logicDetectorHex =new G4LogicalVolume(airLayerSolid,worldMat,"logicalHex");
        G4VPhysicalVolume *physAirHex=new G4PVPlacement(0,G4ThreeVector(0.,0.,zcoordinate),logicDetectorHex,"physDetector",logicWorld,false,copyNumberSC+1000,true);/////////////


        G4cout<<"Hex: "<< "LowerDetector: "<<copyNumberSC+4<<" UpperDetector: "<<copyNumberSC+5<<"PhysicalVolume: "<<copyNumberSC+2<<"airLayer: "<<copyNumberSC+1000<<G4endl;


         copyNumberSC=87;


        if(scintillatorArrangement == "RPCBT"){
        CreateRPC(RPClength, RPCwidth,RPCthickness,0., 0.,379.*cm,Freon ,copper, aluminium, "RPC3");
        CreateRPC(RPClength, RPCwidth,RPCthickness,0., 0.,381.2*cm,Freon ,copper, aluminium, "RPC1");
        
        }

    }  
    
    fScoringVolume=logicSC;

    return physWorld;
} 



//Predefined method used to tell Geant4 what objects are detectors. 
void MyDetectorConstruction::ConstructSDandField(){
   // MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");
  
    if(scintillatorArrangement == "SCBT"|| MyDetectorConstruction::scintillatorArrangement == "RPCBT"){
    MyBarDetector *mybardetector = new MyBarDetector("mybardetector");
    MyPhotoDetector *myphotodetector = new MyPhotoDetector("myphotodetector");
   
   
   logicDetector->SetSensitiveDetector(myphotodetector);
   logicPhotoSensorUpHex->SetSensitiveDetector(myphotodetector);
    
     logicDetectorX1->SetSensitiveDetector(mybardetector);
    logicDetectorY1->SetSensitiveDetector(mybardetector);
    logicDetectorBC->SetSensitiveDetector(mybardetector);
    logicDetectorCZ->SetSensitiveDetector(mybardetector);
    logicDetectorFerm->SetSensitiveDetector(mybardetector);
    logicDetectorEJS0->SetSensitiveDetector(mybardetector);
    logicDetectorEJS1->SetSensitiveDetector(mybardetector);
    logicDetectorEJS2->SetSensitiveDetector(mybardetector);
    logicDetectorAcorde->SetSensitiveDetector(mybardetector);
    logicDetectorUnamEJ->SetSensitiveDetector(mybardetector);
    logicDetectorX2->SetSensitiveDetector(mybardetector);
    logicDetectorEJ1->SetSensitiveDetector(mybardetector);
    logicDetectorEJ2->SetSensitiveDetector(mybardetector);
    logicDetectorEJ3->SetSensitiveDetector(mybardetector);
    logicDetectorEJ4->SetSensitiveDetector(mybardetector);
    logicDetectorEJ5->SetSensitiveDetector(mybardetector);
    logicDetectorEJ6->SetSensitiveDetector(mybardetector);
    logicDetectorEJ7->SetSensitiveDetector(mybardetector);
    logicDetectorEJ8->SetSensitiveDetector(mybardetector);
    logicDetectorTR->SetSensitiveDetector(mybardetector);
    
    logicDetectorHex->SetSensitiveDetector(mybardetector);
     }
    else if(scintillatorArrangement == "SC"){
        
        
        MyPhotoDetector *myphotodetector = new MyPhotoDetector("myphotodetector");
        logicDetector->SetSensitiveDetector(myphotodetector);

    }

    
}
void MyDetectorConstruction::ScintillatorProperties(G4String type,G4String geometry,G4int thickness, G4String numberOfSensors, G4String arrangement){
    scintillatorType=type;
    scintillatorGeometry=geometry;
    scintillatorThickness = thickness;
    scintillatorNumberOfSensors=numberOfSensors;
    scintillatorArrangement=arrangement;

}
void MyDetectorConstruction::BeamTestConfiguration(G4String arrangement, G4String particleName, G4String numberOfParticles, G4String particleEnergy, G4String numberOfEvents){
    scintillatorArrangement=arrangement;
    ParticleName = particleName;
    NumberOfParticles = numberOfParticles;
    ParticleEnergy = particleEnergy;
    NumberOfEvents = numberOfEvents;
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
void MyDetectorConstruction::rectangularPhysicalVolume(G4double length, G4double width, G4double thickness,G4double sensorLength, G4double Xcoordinate, G4double Ycoordinate, G4double Zcoordinate,G4Material* MylarM ,G4Material *material, G4VPhysicalVolume *physicalVolume, G4LogicalVolume *logicalDetector, G4LogicalVolume *airLayer, G4String nombre){
        
        
        G4ThreeVector yTrans1(0,length/2,0);
        G4ThreeVector yTrans2(0,-1*length/2,0);
        yRot->rotateY(0*rad);
        innerBox = new G4Box("innerBox",width/2,length/2,thickness/2);
        externalBox = new G4Box("externalBox",(width/2)+1*mm,(length/2)+1*mm,(thickness/2)+1*mm);
        sensorBox = new G4Box("sensorBox",sensorLength/2,1.*mm,sensorLength/2);

        externalInner= new G4SubtractionSolid("External-Inner", externalBox, innerBox);
        externalSensor1=new G4SubtractionSolid("External-Inner-Sensor1", externalInner, sensorBox, yRot, yTrans1);
        externalSensor2=new G4SubtractionSolid("External-Inner-Sensor2", externalSensor1, sensorBox, yRot, yTrans2);
        logicMylar= new G4LogicalVolume(externalSensor2,MylarM, "logicMylar");
        G4LogicalSkinSurface *skin = new G4LogicalSkinSurface("skin",logicMylar,mirrorSurface);
        physMylar =new G4PVPlacement(0,G4ThreeVector(0.,0.,Zcoordinate),logicMylar,"physMylar",logicWorld,false,copyNumberSC+1,true);

        

        G4Box *solidScintillator = new G4Box("solidScintillator",width/2,length/2,thickness/2);
        logicSC= new G4LogicalVolume(solidScintillator,material, "logicSC");
        physicalVolume =new G4PVPlacement(0,G4ThreeVector(0.,0.,Zcoordinate),logicSC,"physSC",logicWorld,false,copyNumberSC+2,true);
        
        
        
        upperDetector=new G4PVPlacement(0,G4ThreeVector(0.,(length/2)+1*mm,Zcoordinate),logicalDetector,"physDetector1",logicWorld,false,copyNumberSC+3,true);
        lowerDetector =new G4PVPlacement(0,G4ThreeVector(0.,(-1*length/2)-1*mm,Zcoordinate),logicalDetector,"physDetector2",logicWorld,false,copyNumberSC+4,true);

        physDetector=new G4PVPlacement(0,G4ThreeVector(0.,0.,Zcoordinate),airLayer,"airlayerDetector",logicWorld,false,copyNumberSC+1000,true);
        G4cout<<nombre<<" "<< "UpperDetector: "<<copyNumberSC+3<<" LowerDetector :"<<copyNumberSC+4<<" PhysicalVolume: "<<copyNumberSC+2<<" AirLayerDetector: "<<copyNumberSC+1000<<G4endl;
        copyNumberSC=copyNumberSC+4;
        
}

void MyDetectorConstruction::CreateRPC(G4double length, G4double width, G4double thickness,G4double Xcoordinate, G4double Ycoordinate, G4double Zcoordinate,G4Material* gasMaterial ,G4Material *innerLayerMaterial, G4Material *externalLayerMaterial,  G4String nombre){
    
        G4Box *gasBox = new G4Box("gasBox",width/2-4*mm,length/2-4*mm,thickness/2-4*mm);
        G4Box *externalSolid = new G4Box("externalSolid",width/2,length/2,thickness/2);
        G4Box *innerSolid = new G4Box("innerSolid",width/2-2*mm,length/2-2*mm,thickness/2-2*mm);

        G4SubtractionSolid * innerBox = new G4SubtractionSolid("innerSolid", innerSolid, gasBox);
        G4SubtractionSolid * externalBox = new G4SubtractionSolid("externalSolid", externalSolid, innerSolid);
        G4LogicalVolume * innerLogic = new G4LogicalVolume(innerBox,innerLayerMaterial, "logicalInner");
        G4LogicalVolume * externalLogic = new G4LogicalVolume(externalBox,externalLayerMaterial, "logicalExternal");
        G4LogicalVolume * logicalGas = new G4LogicalVolume(gasBox,externalLayerMaterial, "logicalgas");
        G4VPhysicalVolume * physicalGas=new G4PVPlacement(0,G4ThreeVector(Xcoordinate,Ycoordinate,Zcoordinate),logicalGas,nombre,logicWorld,false,copyNumberSC+1,true);
        G4VPhysicalVolume * physicalinner=new G4PVPlacement(0,G4ThreeVector(Xcoordinate,Ycoordinate,Zcoordinate),innerLogic,nombre +" physInner",logicWorld,false,copyNumberSC+2,true);
        G4VPhysicalVolume * physicalExternal=new G4PVPlacement(0,G4ThreeVector(Xcoordinate,Ycoordinate,Zcoordinate),externalLogic,nombre +"physExternal",logicWorld,false,copyNumberSC+3,true);
        G4cout<<nombre<<" "<< "gasVolume: "<<copyNumberSC+1<<" copper : "<<copyNumberSC+2<<" Aluminium: "<<copyNumberSC+3<<G4endl;
        
        copyNumberSC=copyNumberSC+3;

}
