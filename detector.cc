#include "detector.hh"
#include "G4UnitsTable.hh"
#include <cmath>

G4int MySensitiveDetector::noc;
MySensitiveDetector::MySensitiveDetector(G4String name):G4VSensitiveDetector(name)
{   
 npX1=0,npY1=0,npCZ=0,npS0=0,npS1=0,npS2=0,npBC=0,npACORDE=0,npUNAM=0,npFERM=0,npX2=0;
 evtX1=0,evtY1=0,evtCZ=0,evtS0=0,evtS1=0,evtS2=0,evtBC=0,evtACORDE=0,evtUNAM=0,evtFERM=0,evtX2=0;
}
MySensitiveDetector::~MySensitiveDetector(){

}
G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist){
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    //Definition of what will fill the histograms
    G4Track *track=aStep->GetTrack();
   // track->SetTrackStatus(fStopAndKill);
    const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();
    G4int copyNo = touchable -> GetCopyNumber();
    if(MyDetectorConstruction::scintillatorArrangement == "SC"){
    G4StepPoint *preStepPoint=aStep->GetPreStepPoint();
    G4StepPoint *postStepPoint=aStep->GetPostStepPoint();
    G4ThreeVector posPhoton=preStepPoint->GetPosition();
    G4double posmodule, posmodule2;
if (track) {
        const G4ParticleDefinition* particleDefinition = track->GetDefinition();
        if (particleDefinition) {
            G4String particleName = particleDefinition->GetParticleName();
            //G4cout << "Nombre de la partícula: " << particleName << G4endl;
            if(particleName == "proton"){
            posmodule = posPhoton.x()*posPhoton.x()+posPhoton.y()*posPhoton.y();
            posmodule2=std::sqrt(posmodule2);
             G4cout<<posPhoton<<" "<<posmodule2<<G4endl;
            }
        }
    }
    
    G4ThreeVector momPhoton=preStepPoint->GetMomentum();
    G4double energy =momPhoton.mag();
    G4double wlen= ((1.239841939*eV*um)/momPhoton.mag());
    
    
    G4double time = preStepPoint->GetLocalTime();
     //Only if Multithreaded mode is not being used

   #ifndef G4MULTITHREADED
    G4cout<<"TOF:  "<<G4BestUnit(time,"Time")<<G4endl;
    G4cout<<"TOF:  "<<time<<G4endl;

    #endif

    
    G4int idEvt =G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
    if(idEvt==evt){
        numberOfPhotons++;
        man->GetH1(17)->reset();
        man->FillH1(17,numberOfPhotons);
    } else{
        evt=idEvt;
        numberOfPhotons=1;
        man->GetH1(17)->reset();
        man->FillH1(17,numberOfPhotons);
    }
    
    
    
    
    
    man->FillH1(1,wlen);
    man->FillH1(2,idEvt);
    man->FillH1(3,energy);
    if(idEvt<10){
    man->FillH1(4,idEvt);
    }
    
    if(idEvt<10){
    man->FillH1(idEvt+5,time);
    }
    man->FillH1(15,time);

    
   man->FillH2(0,energy, wlen);
    }

    if(MyDetectorConstruction::scintillatorArrangement == "SCBT"){
        G4VPhysicalVolume* physicalVolume = aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
        G4int copyNumber = physicalVolume->GetCopyNo();
        G4Track *track=aStep->GetTrack();
    track->SetTrackStatus(fStopAndKill);
    G4StepPoint *preStepPoint=aStep->GetPreStepPoint();
    G4StepPoint *postStepPoint=aStep->GetPostStepPoint();
    const G4ParticleDefinition* particleDefinition = track->GetDefinition();
    G4String particleName = particleDefinition->GetParticleName();

    G4ThreeVector pos = preStepPoint->GetPosition();
    if(particleName != "opticalphoton"){
        G4cout<<"Particula: "<<particleName<<" coordenadas: "<<pos<<G4endl;
    }

        if(copyNumber == 3 || copyNumber == 4){
            histogramFilling("X1",0,evtX1,npX1,aStep);}
       //if(copyNumber == 2 || copyNumber == 6){G4cout<<copyNumber<<G4endl;}
        if(copyNumber == 7 || copyNumber == 8){
            histogramFilling("Y1",1,evtY1,npY1,aStep);

        }

        if(copyNumber == 11 || copyNumber == 12){
            histogramFilling("CZ",2,evtCZ,npCZ,aStep);
        }

        if(copyNumber == 15 || copyNumber == 16 ){
            histogramFilling("S0",3,evtS0,npS0,aStep);
         
        }

        if(copyNumber == 19|| copyNumber == 20 ){
            histogramFilling("S1",4,evtS1,npS1,aStep);
        }

        if(copyNumber == 23 || copyNumber == 24 ){
            histogramFilling("S2",5,evtS2,npS2,aStep);
            
        }

        if(copyNumber == 27|| copyNumber == 28){
            histogramFilling("BC",6,evtBC,npBC,aStep);
        }

        if(copyNumber == 31|| copyNumber == 32){
            histogramFilling("ACORDE",7,evtACORDE,npACORDE,aStep);
        }

        if(copyNumber ==35 || copyNumber == 36){
            histogramFilling("UNAM",8,evtUNAM,npUNAM,aStep);
        }

        if(copyNumber == 39|| copyNumber == 40){
            histogramFilling("FERM",9,evtFERM,npFERM,aStep);
        }

        if(copyNumber == 43 || copyNumber == 44){
            histogramFilling("X2",10,evtX2,npX2,aStep);
        }

       /* histogramFilling("CZ",2,evtCZ,npCZ,aStep);
        histogramFilling("S0",3,evtS0,npS0,aStep);
        histogramFilling("S1",4,evtS1,npS1,aStep);
        histogramFilling("S2",5,evtS2,npS2,aStep);
        histogramFilling("BC",6,evtBC,npBC,aStep);
        histogramFilling("ACORDE",7,evtACORDE,npACORDE,aStep);
        histogramFilling("UNAM",8,evtUNAM,npUNAM,aStep);
        histogramFilling("FERM",9,evtFERM,npFERM,aStep);
        histogramFilling("X2",10,evtX2,npX2,aStep);*/


    }
return true;}

void MySensitiveDetector::histogramFilling(G4String scintillatorName, G4int scintillatorPosition, G4int& evtNumber, G4int& numberOfPhotons,G4Step *aStep){
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    
    G4Track *track=aStep->GetTrack();
    track->SetTrackStatus(fStopAndKill);
    G4StepPoint *preStepPoint=aStep->GetPreStepPoint();
    G4StepPoint *postStepPoint=aStep->GetPostStepPoint();
    const G4ParticleDefinition* particleDefinition = track->GetDefinition();
    G4String particleName = particleDefinition->GetParticleName();

    G4ThreeVector pos = preStepPoint->GetPosition();
    if(particleName != "opticalphoton"){
        G4cout<<"Particula: "<<particleName<<" coordenadas: "<<pos<<G4endl;
    }
    G4ThreeVector momPhoton=preStepPoint->GetMomentum();
    G4double energy =momPhoton.mag();
    G4double wlen= ((1.239841939*eV*um)/momPhoton.mag());
    
    man->FillH2(scintillatorPosition,energy, wlen);
    G4double time = preStepPoint->GetLocalTime();
    scintillatorPosition = scintillatorPosition*10;
    
    

    G4int idEvt =G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
    if(idEvt==evtNumber){
        numberOfPhotons++;
        
        man->GetH1(scintillatorPosition+8)->reset();
        man->FillH1(scintillatorPosition+8,numberOfPhotons);
    } else{
        
        evtNumber=idEvt;
        numberOfPhotons=1;
        man->GetH1(scintillatorPosition+8)->reset();
        man->FillH1(scintillatorPosition+8,numberOfPhotons);
    }
    
    
    
    
    
    man->FillH1(scintillatorPosition+1,wlen);
   // man->FillH1(1,wlen);
    man->FillH1(scintillatorPosition+2,idEvt);
    
    man->FillH1(scintillatorPosition+3,energy);
    if(idEvt<10){
    man->FillH1(scintillatorPosition+4,idEvt);
    }
    
    if(idEvt==0){
    man->FillH1(scintillatorPosition+5,time);
    }
    man->FillH1(scintillatorPosition+6,time);

    
   
    

}