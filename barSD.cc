#include "barSD.hh"

MyBarDetector::MyBarDetector(G4String name):G4VSensitiveDetector(name){

}

MyBarDetector::~MyBarDetector(){

}

G4bool MyBarDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist){
    
    

    G4Track *track=aStep->GetTrack();
    const G4ParticleDefinition* particleDefinition = track->GetDefinition();
    G4String particleName = particleDefinition->GetParticleName();
   
    if(particleName == "opticalphoton" || track->GetParentID()==0){
        return true;
    }
    
    G4AnalysisManager *man = G4AnalysisManager::Instance();

    G4VPhysicalVolume* physicalVolume = aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
    G4int copyNumber = physicalVolume->GetCopyNo();
    G4StepPoint *preStepPoint=aStep->GetPreStepPoint();
    G4StepPoint *postStepPoint=aStep->GetPostStepPoint();
    G4double time = preStepPoint->GetLocalTime();
    time = time/ns;   

    G4ThreeVector pos = preStepPoint->GetPosition();
    G4int trackID =  aStep->GetTrack()->GetTrackID();
    

    G4int idEvt =G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
    if(copyNumber == 1000){ //x1
        man->FillNtupleDColumn(2,0,pos.x()/mm);
        man->FillNtupleDColumn(2,1,pos.y()/mm);
        man->FillNtupleDColumn(2,2,pos.z()/mm);  
        man->FillNtupleIColumn(2,3,idEvt); 
        man->FillNtupleIColumn(2,4,trackID);
        man->FillNtupleDColumn(2,5,time);    
        man->AddNtupleRow(2); 
        }

    if(copyNumber == 1004){ //Y1
        man->FillNtupleDColumn(5,0,pos.x()/mm);
        man->FillNtupleDColumn(5,1,pos.y()/mm);
        man->FillNtupleDColumn(5,2,pos.z()/mm);
        man->FillNtupleIColumn(5,3,idEvt); 
        man->FillNtupleIColumn(5,4,trackID);
        man->FillNtupleDColumn(5,5,time); 
        man->AddNtupleRow(5);
            
        }

    if(copyNumber == 1008){  //CZ
        man->FillNtupleDColumn(8,0,pos.x()/mm);
        man->FillNtupleDColumn(8,1,pos.y()/mm);
        man->FillNtupleDColumn(8,2,pos.z()/mm);
        man->FillNtupleIColumn(8,3,idEvt); 
        man->FillNtupleIColumn(8,4,trackID);
        man->FillNtupleDColumn(8,5,time);  
        man->AddNtupleRow(8);
            
        }

    if(copyNumber == 1012){ // S0
        man->FillNtupleDColumn(11,0,pos.x()/mm);
        man->FillNtupleDColumn(11,1,pos.y()/mm);
        man->FillNtupleDColumn(11,2,pos.z()/mm);
        man->FillNtupleIColumn(11,3,idEvt); 
        man->FillNtupleIColumn(11,4,trackID);
        man->FillNtupleDColumn(11,5,time); 
        man->AddNtupleRow(11);
            
        }

    if(copyNumber == 1016){ //S1
        man->FillNtupleDColumn(14,0,pos.x()/mm);
        man->FillNtupleDColumn(14,1,pos.y()/mm);
        man->FillNtupleDColumn(14,2,pos.z()/mm);
        man->FillNtupleIColumn(14,3,idEvt); 
        man->FillNtupleIColumn(14,4,trackID);
        man->FillNtupleDColumn(14,5,time); 
        man->AddNtupleRow(14);
            
        }

    if(copyNumber == 1020){ //S2
        man->FillNtupleDColumn(17,0,pos.x()/mm);
        man->FillNtupleDColumn(17,1,pos.y()/mm);
        man->FillNtupleDColumn(17,2,pos.z()/mm);
        man->FillNtupleIColumn(17,3,idEvt); 
        man->FillNtupleIColumn(17,4,trackID);
        man->FillNtupleDColumn(17,5,time); 
        man->AddNtupleRow(17);
            
        }

    if(copyNumber == 1024){ //BC
        man->FillNtupleDColumn(20,0,pos.x()/mm);
        man->FillNtupleDColumn(20,1,pos.y()/mm);
        man->FillNtupleDColumn(20,2,pos.z()/mm);
        man->FillNtupleIColumn(20,3,idEvt); 
        man->FillNtupleIColumn(20,4,trackID);
        man->FillNtupleDColumn(20,5,time); 
        man->AddNtupleRow(20);
            
        }

    if(copyNumber == 1028){ //ACOR
        man->FillNtupleDColumn(23,0,pos.x()/mm);
        man->FillNtupleDColumn(23,1,pos.y()/mm);
        man->FillNtupleDColumn(23,2,pos.z()/mm);
        man->FillNtupleIColumn(23,3,idEvt); 
        man->FillNtupleIColumn(23,4,trackID);
        man->FillNtupleDColumn(23,5,time); 
        man->AddNtupleRow(23);
            
        }

    if(copyNumber == 1032){ //UNAM
        man->FillNtupleDColumn(26,0,pos.x()/mm);
        man->FillNtupleDColumn(26,1,pos.y()/mm);
        man->FillNtupleDColumn(26,2,pos.z()/mm); 
        man->FillNtupleIColumn(26,3,idEvt); 
        man->FillNtupleIColumn(26,4,trackID);
        man->FillNtupleDColumn(26,5,time);           
        man->AddNtupleRow(26);
            
        }

    if(copyNumber == 1036){ //FERM
        man->FillNtupleDColumn(29,0,pos.x()/mm);
        man->FillNtupleDColumn(29,1,pos.y()/mm);
        man->FillNtupleDColumn(29,2,pos.z()/mm);
        man->FillNtupleIColumn(29,3,idEvt); 
        man->FillNtupleIColumn(29,4,trackID);
        man->FillNtupleDColumn(29,5,time); 
        man->AddNtupleRow(29);
        }

    if(copyNumber == 1040){ //X2
        man->FillNtupleDColumn(32,0,pos.x()/mm);
        man->FillNtupleDColumn(32,1,pos.y()/mm);
        man->FillNtupleDColumn(32,2,pos.z()/mm);
        man->FillNtupleIColumn(32,3,idEvt); 
        man->FillNtupleIColumn(32,4,trackID);
        man->FillNtupleDColumn(32,5,time); 
        man->AddNtupleRow(32); 
        }

        if(copyNumber == 1044){ //EJ1
        man->FillNtupleDColumn(35,0,pos.x()/mm);
        man->FillNtupleDColumn(35,1,pos.y()/mm);
        man->FillNtupleDColumn(35,2,pos.z()/mm);
        man->FillNtupleIColumn(35,3,idEvt); 
        man->FillNtupleIColumn(35,4,trackID);
        man->FillNtupleDColumn(35,5,time); 
        man->AddNtupleRow(35); 
        }


        if(copyNumber == 1048){ //EJ2
        man->FillNtupleDColumn(38,0,pos.x()/mm);
        man->FillNtupleDColumn(38,1,pos.y()/mm);
        man->FillNtupleDColumn(38,2,pos.z()/mm);
        man->FillNtupleIColumn(38,3,idEvt); 
        man->FillNtupleIColumn(38,4,trackID);
        man->FillNtupleDColumn(38,5,time); 
        man->AddNtupleRow(38); 
        }


        if(copyNumber == 1052){ //EJ3
        man->FillNtupleDColumn(41,0,pos.x()/mm);
        man->FillNtupleDColumn(41,1,pos.y()/mm);
        man->FillNtupleDColumn(41,2,pos.z()/mm);
        man->FillNtupleIColumn(41,3,idEvt); 
        man->FillNtupleIColumn(41,4,trackID);
        man->FillNtupleDColumn(41,5,time); 
        man->AddNtupleRow(41); 
        }


        if(copyNumber == 1056){ //EJ4
        man->FillNtupleDColumn(44,0,pos.x()/mm);
        man->FillNtupleDColumn(44,1,pos.y()/mm);
        man->FillNtupleDColumn(44,2,pos.z()/mm);
        man->FillNtupleIColumn(44,3,idEvt); 
        man->FillNtupleIColumn(44,4,trackID);
        man->FillNtupleDColumn(44,5,time); 
        man->AddNtupleRow(44); 
        }


        if(copyNumber == 1060){ //EJ5
        man->FillNtupleDColumn(47,0,pos.x()/mm);
        man->FillNtupleDColumn(47,1,pos.y()/mm);
        man->FillNtupleDColumn(47,2,pos.z()/mm);
        man->FillNtupleIColumn(47,3,idEvt); 
        man->FillNtupleIColumn(47,4,trackID);
        man->FillNtupleDColumn(47,5,time); 
        man->AddNtupleRow(47); 
        }


        if(copyNumber == 1064){ //EJ6
        man->FillNtupleDColumn(50,0,pos.x()/mm);
        man->FillNtupleDColumn(50,1,pos.y()/mm);
        man->FillNtupleDColumn(50,2,pos.z()/mm);
        man->FillNtupleIColumn(50,3,idEvt); 
        man->FillNtupleIColumn(50,4,trackID);
        man->FillNtupleDColumn(50,5,time); 
        man->AddNtupleRow(50); 
        }


        if(copyNumber == 1068){ //EJ7
        man->FillNtupleDColumn(53,0,pos.x()/mm);
        man->FillNtupleDColumn(53,1,pos.y()/mm);
        man->FillNtupleDColumn(53,2,pos.z()/mm);
        man->FillNtupleIColumn(53,3,idEvt); 
        man->FillNtupleIColumn(53,4,trackID);
        man->FillNtupleDColumn(53,5,time); 
        man->AddNtupleRow(53); 
        }


        if(copyNumber == 1072){ //EJ8
        man->FillNtupleDColumn(56,0,pos.x()/mm);
        man->FillNtupleDColumn(56,1,pos.y()/mm);
        man->FillNtupleDColumn(56,2,pos.z()/mm);
        man->FillNtupleIColumn(56,3,idEvt); 
        man->FillNtupleIColumn(56,4,trackID);
        man->FillNtupleDColumn(56,5,time); 
        man->AddNtupleRow(56); 
        }

        if(copyNumber == 1076){ //TR
        man->FillNtupleDColumn(59,0,pos.x()/mm);
        man->FillNtupleDColumn(59,1,pos.y()/mm);
        man->FillNtupleDColumn(59,2,pos.z()/mm);
        man->FillNtupleIColumn(59,3,idEvt); 
        man->FillNtupleIColumn(59,4,trackID);
        man->FillNtupleDColumn(59,5,time); 
        man->AddNtupleRow(59); 
        }


        if(copyNumber == 1080){ //HEX
        man->FillNtupleDColumn(62,0,pos.x()/mm);
        man->FillNtupleDColumn(62,1,pos.y()/mm);
        man->FillNtupleDColumn(62,2,pos.z()/mm);
        man->FillNtupleIColumn(62,3,idEvt); 
        man->FillNtupleIColumn(62,4,trackID);
        man->FillNtupleDColumn(62,5,time); 
        man->AddNtupleRow(62); 
        }




        
    
    

    return true;

}