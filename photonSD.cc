#include "photonSD.hh"

G4int MyPhotoDetector::noc;
MyPhotoDetector::MyPhotoDetector(G4String name):G4VSensitiveDetector(name)
{   
 npX1=0,npY1=0,npCZ=0,npS0=0,npS1=0,npS2=0,npBC=0,npACORDE=0,npUNAM=0,npFERM=0,npX2=0;
 evtX1=0,evtY1=0,evtCZ=0,evtS0=0,evtS1=0,evtS2=0,evtBC=0,evtACORDE=0,evtUNAM=0,evtFERM=0,evtX2=0;
 evtEJ1=0,evtEJ2=0,evtEJ3=0,evtEJ4=0,evtEJ5=0,evtEJ6=0,evtEJ7=0,evtEJ8=0,evtHex=0,evtTR=0,evtDump=0;
 npEJ1=0,npEJ2=0,npEJ3=0,npEJ4=0,npEJ5=0,npEJ6=0,npEJ7=0,npEJ8=0,npHex=0,npTR=0,npDump=0;
};

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
    track->SetTrackStatus(fStopAndKill);
if (track) {
        const G4ParticleDefinition* particleDefinition = track->GetDefinition();
        if (particleDefinition) {
            G4String particleName = particleDefinition->GetParticleName();
            //G4cout << "Nombre de la partícula: " << particleName << G4endl;
            
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

    if(MyDetectorConstruction::scintillatorArrangement == "SCBT" || MyDetectorConstruction::scintillatorArrangement == "RPCBT"){
        G4VPhysicalVolume* physicalVolume = aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
        G4int copyNumber = physicalVolume->GetCopyNo();
       // G4cout<<"particleDetected"<<G4endl;
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
             //   G4cout<<"particleDetected"<<G4endl;
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

            if(copyNumber == 47 || copyNumber == 48){
                NtupleFilling("EJ1",11,evtEJ1,npEJ1,aStep);
            }

            if(copyNumber == 51 || copyNumber == 52){
                NtupleFilling("EJ2",12,evtEJ2,npEJ2,aStep);
            }

            if(copyNumber == 55 || copyNumber == 56){
                NtupleFilling("EJ3",13,evtEJ3,npEJ3,aStep);
            }

            if(copyNumber == 59 || copyNumber == 60){
                NtupleFilling("EJ4",14,evtEJ4,npEJ4,aStep);
            }

            if(copyNumber == 63 || copyNumber == 64){
                NtupleFilling("EJ5",15,evtEJ5,npEJ5,aStep);
            }

            if(copyNumber == 67 || copyNumber == 68){
                NtupleFilling("EJ6",16,evtEJ6,npEJ6,aStep);
            }

            if(copyNumber == 71 || copyNumber == 72){
                NtupleFilling("EJ7",17,evtEJ7,npEJ7,aStep);
            }

            if(copyNumber == 75 || copyNumber == 76){
                NtupleFilling("EJ8",18,evtEJ8,npEJ8,aStep);
            }

            if(copyNumber == 79 || copyNumber == 80){
                NtupleFilling("TR",19,evtTR,npTR,aStep);
            }

            if(copyNumber == 84 || copyNumber == 85){
                NtupleFilling("HEX",20,evtHex,npHex,aStep);
            }





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

    wlen=wlen/nm;
    energy=energy/eV;
    man->FillNtupleIColumn(scintillatorPosition*3,0,idEvt);
    man->FillNtupleDColumn(scintillatorPosition*3,1,wlen);
    man->FillNtupleDColumn(scintillatorPosition*3,2,energy);
    

    G4double time = preStepPoint->GetLocalTime();
    time = time/ns;
 //   scintillatorPosition = scintillatorPosition*3; //3 es el numero total de histogramas
    man->FillNtupleDColumn(scintillatorPosition*3,3,time);
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
