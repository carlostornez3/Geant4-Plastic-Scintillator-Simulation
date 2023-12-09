#include "barSD.hh"

MyBarDetector::MyBarDetector(G4String name):G4VSensitiveDetector(name), isFirstHit(true){

}

MyBarDetector::~MyBarDetector(){

}

G4bool MyBarDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist){
    
    

    G4Track *track=aStep->GetTrack();
    const G4ParticleDefinition* particleDefinition = track->GetDefinition();
    G4String particleName = particleDefinition->GetParticleName();
    if(particleName == "opticalphoton"){
        return true;
    }
    
    
    if (!aStep->IsFirstStepInVolume()) {
        return true;
    }
    G4AnalysisManager *man = G4AnalysisManager::Instance();

    G4VPhysicalVolume* physicalVolume = aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
    G4int copyNumber = physicalVolume->GetCopyNo();
    G4StepPoint *preStepPoint=aStep->GetPreStepPoint();
    G4StepPoint *postStepPoint=aStep->GetPostStepPoint();
        

    G4ThreeVector pos = preStepPoint->GetPosition();
   // G4int trackID =  aStep->GetTrack()->GetTrackID();
    //G4int eventID = G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID();
    //G4cout<<"Particula: "<<particleName<<" coordenadas: "<<pos<<" CopyNo: "<<copyNumber<<" TrackID: "<<trackID<<" EventID: " << eventID<<G4endl;

    //man->FillNtupleDColumn();
    G4double adlt=1*mm; //thickness of the air detector layer
    pos[2]=pos[2]-adlt;
    if(copyNumber == 2){ //x1
        man->FillNtupleDColumn(2,0,pos[0]);
        man->FillNtupleDColumn(2,1,pos[1]);
        man->FillNtupleDColumn(2,2,pos[2]);  
            
        }

    if(copyNumber == 6){ //Y1
        man->FillNtupleDColumn(5,0,pos[0]);
        man->FillNtupleDColumn(5,1,pos[1]);
        man->FillNtupleDColumn(5,2,pos[2]);
            
        }

    if(copyNumber == 10){  //CZ
        man->FillNtupleDColumn(8,0,pos[0]);
        man->FillNtupleDColumn(8,1,pos[1]);
        man->FillNtupleDColumn(8,2,pos[2]); 
            
        }

    if(copyNumber == 14){ // S0
        man->FillNtupleDColumn(11,0,pos[0]);
        man->FillNtupleDColumn(11,1,pos[1]);
        man->FillNtupleDColumn(11,2,pos[2]);
            
        }

    if(copyNumber == 18){ //S1
        man->FillNtupleDColumn(14,0,pos[0]);
        man->FillNtupleDColumn(14,1,pos[1]);
        man->FillNtupleDColumn(14,2,pos[2]);
            
        }

    if(copyNumber == 22){ //S2
        man->FillNtupleDColumn(17,0,pos[0]);
        man->FillNtupleDColumn(17,1,pos[1]);
        man->FillNtupleDColumn(17,2,pos[2]);
            
        }

    if(copyNumber == 26){ //BC
        man->FillNtupleDColumn(20,0,pos[0]);
        man->FillNtupleDColumn(20,1,pos[1]);
        man->FillNtupleDColumn(20,2,pos[2]);
            
        }

    if(copyNumber == 30){ //ACOR
        man->FillNtupleDColumn(23,0,pos[0]);
        man->FillNtupleDColumn(23,1,pos[1]);
        man->FillNtupleDColumn(23,2,pos[2]);
            
        }

    if(copyNumber == 34){ //UNAM
        man->FillNtupleDColumn(26,0,pos[0]);
        man->FillNtupleDColumn(26,1,pos[1]);
        man->FillNtupleDColumn(26,2,pos[2]);           
            
        }

    if(copyNumber == 38){ //FERM
        man->FillNtupleDColumn(29,0,pos[0]);
        man->FillNtupleDColumn(29,1,pos[1]);
        man->FillNtupleDColumn(29,2,pos[2]);
        }

    if(copyNumber == 42){ //X2
        man->FillNtupleDColumn(32,0,pos[0]);
        man->FillNtupleDColumn(32,1,pos[1]);
        man->FillNtupleDColumn(32,2,pos[2]); 
        }
    
    

    return true;

}