#include "photonSD.hh"

G4int MyPhotoDetector::noc;
MyPhotoDetector::MyPhotoDetector(G4String name):G4VSensitiveDetector(name)
{   
 npX1=0,npY1=0,npCZ=0,npS0=0,npS1=0,npS2=0,npBC=0,npACORDE=0,npUNAM=0,npFERM=0,npX2=0;
 evtX1=0,evtY1=0,evtCZ=0,evtS0=0,evtS1=0,evtS2=0,evtBC=0,evtACORDE=0,evtUNAM=0,evtFERM=0,evtX2=0;
}
MyPhotoDetector::~MyPhotoDetector(){

}
G4bool MyPhotoDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist){
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    
    if(MyDetectorConstruction::scintillatorArrangement == "SC"){
    G4StepPoint *preStepPoint=aStep->GetPreStepPoint();
    G4StepPoint *postStepPoint=aStep->GetPostStepPoint();
    G4ThreeVector posPhoton=preStepPoint->GetPosition();
    G4double posmodule, posmodule2;
    G4Track *track=aStep->GetTrack();
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
            return true;
        }

            if(copyNumber == 3 || copyNumber == 4){
                NtupleFilling("X1",0,evtX1,npX1,aStep);}
        
            if(copyNumber == 7 || copyNumber == 8){
                NtupleFilling("Y1",1,evtY1,npY1,aStep);

            }

            if(copyNumber == 11 || copyNumber == 12){
                NtupleFilling("CZ",2,evtCZ,npCZ,aStep);
            }

            if(copyNumber == 15 || copyNumber == 16 ){
                NtupleFilling("S0",3,evtS0,npS0,aStep);
            
            }

            if(copyNumber == 19|| copyNumber == 20 ){
                NtupleFilling("S1",4,evtS1,npS1,aStep);
            }

            if(copyNumber == 23 || copyNumber == 24 ){
                NtupleFilling("S2",5,evtS2,npS2,aStep);
                
            }

            if(copyNumber == 27|| copyNumber == 28){
                NtupleFilling("BC",6,evtBC,npBC,aStep);
            }

            if(copyNumber == 31|| copyNumber == 32){
                NtupleFilling("ACORDE",7,evtACORDE,npACORDE,aStep);
            }

            if(copyNumber ==35 || copyNumber == 36){
                NtupleFilling("UNAM",8,evtUNAM,npUNAM,aStep);
            }

            if(copyNumber == 39|| copyNumber == 40){
                NtupleFilling("FERM",9,evtFERM,npFERM,aStep);
            }

            if(copyNumber == 43 || copyNumber == 44){
                NtupleFilling("X2",10,evtX2,npX2,aStep);
            }

        /* NtupleFilling("CZ",2,evtCZ,npCZ,aStep);
            NtupleFilling("S0",3,evtS0,npS0,aStep);
            NtupleFilling("S1",4,evtS1,npS1,aStep);
            NtupleFilling("S2",5,evtS2,npS2,aStep);
            NtupleFilling("BC",6,evtBC,npBC,aStep);
            NtupleFilling("ACORDE",7,evtACORDE,npACORDE,aStep);
            NtupleFilling("UNAM",8,evtUNAM,npUNAM,aStep);
            NtupleFilling("FERM",9,evtFERM,npFERM,aStep);
            NtupleFilling("X2",10,evtX2,npX2,aStep);*/


    }
return true;}

void MyPhotoDetector::NtupleFilling(G4String scintillatorName, G4int scintillatorPosition, G4int& evtNumber, G4int& numberOfPhotons,G4Step *aStep){
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    
    G4Track *track=aStep->GetTrack();
    track->SetTrackStatus(fStopAndKill);
    G4StepPoint *preStepPoint=aStep->GetPreStepPoint();
    G4StepPoint *postStepPoint=aStep->GetPostStepPoint();
    const G4ParticleDefinition* particleDefinition = track->GetDefinition();
    G4String particleName = particleDefinition->GetParticleName();

    
    
    G4ThreeVector momPhoton=preStepPoint->GetMomentum();
    G4double energy =momPhoton.mag();
    G4double wlen= ((1.239841939*eV*um)/momPhoton.mag());
    G4int idEvt =G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();


    man->FillNtupleIColumn(scintillatorPosition*3,0,idEvt);
    man->FillNtupleDColumn(scintillatorPosition*3,1,wlen);
    man->FillNtupleDColumn(scintillatorPosition*3,2,energy);
    

    G4double time = preStepPoint->GetLocalTime();
 //   scintillatorPosition = scintillatorPosition*3; //3 es el numero total de histogramas
    if(idEvt==0){
    man->FillNtupleDColumn(scintillatorPosition*3,3,time);
    }else{
        man->FillNtupleDColumn(scintillatorPosition*3,3,-1);
    }
    man->AddNtupleRow(scintillatorPosition*3);
    man->FillH1(scintillatorPosition*2,time);
    
    if(idEvt==evtNumber){
        numberOfPhotons++;
        
        man->GetH1(scintillatorPosition*2+1)->reset();
        man->FillH1(scintillatorPosition*2+1,numberOfPhotons);
    } else{
        
        evtNumber=idEvt;
        numberOfPhotons=1;
        man->GetH1(scintillatorPosition*2+1)->reset();
        man->FillH1(scintillatorPosition*2+1,numberOfPhotons);
    }


    }
