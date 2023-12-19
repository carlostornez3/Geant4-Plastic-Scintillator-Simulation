#include "barSD.hh"

MyBarDetector::MyBarDetector(G4String name):G4VSensitiveDetector(name){

}

MyBarDetector::~MyBarDetector(){

}

G4bool MyBarDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist){
    
    

    G4Track *track=aStep->GetTrack();
    const G4ParticleDefinition* particleDefinition = track->GetDefinition();
    G4String particleName = particleDefinition->GetParticleName();
    if(particleName == "opticalphoton"){
        //G4cout<<particleName<<" bardetector"<<G4endl;
    }

    if(particleName == "opticalphoton" || particleName == MyDetectorConstruction::ParticleName){
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
    
    if(copyNumber == 1000){ //x1
        man->FillNtupleDColumn(2,0,pos.x()/mm);
        man->FillNtupleDColumn(2,1,pos.y()/mm);
        man->FillNtupleDColumn(2,2,pos.z()/mm);  
        
        man->AddNtupleRow(2); 
        }

    if(copyNumber == 1004){ //Y1
        man->FillNtupleDColumn(5,0,pos.x()/mm);
        man->FillNtupleDColumn(5,1,pos.y()/mm);
        man->FillNtupleDColumn(5,2,pos.z()/mm);
        man->AddNtupleRow(5);
            
        }

    if(copyNumber == 1008){  //CZ
        man->FillNtupleDColumn(8,0,pos.x()/mm);
        man->FillNtupleDColumn(8,1,pos.y()/mm);
        man->FillNtupleDColumn(8,2,pos.z()/mm); 
        man->AddNtupleRow(8);
            
        }

    if(copyNumber == 1012){ // S0
        man->FillNtupleDColumn(11,0,pos.x()/mm);
        man->FillNtupleDColumn(11,1,pos.y()/mm);
        man->FillNtupleDColumn(11,2,pos.z()/mm);
        man->AddNtupleRow(11);
            
        }

    if(copyNumber == 1016){ //S1
        man->FillNtupleDColumn(14,0,pos.x()/mm);
        man->FillNtupleDColumn(14,1,pos.y()/mm);
        man->FillNtupleDColumn(14,2,pos.z()/mm);
        man->AddNtupleRow(14);
            
        }

    if(copyNumber == 1020){ //S2
        man->FillNtupleDColumn(17,0,pos.x()/mm);
        man->FillNtupleDColumn(17,1,pos.y()/mm);
        man->FillNtupleDColumn(17,2,pos.z()/mm);
        man->AddNtupleRow(17);
            
        }

    if(copyNumber == 1024){ //BC
        man->FillNtupleDColumn(20,0,pos.x()/mm);
        man->FillNtupleDColumn(20,1,pos.y()/mm);
        man->FillNtupleDColumn(20,2,pos.z()/mm);
        man->AddNtupleRow(20);
            
        }

    if(copyNumber == 1028){ //ACOR
        man->FillNtupleDColumn(23,0,pos.x()/mm);
        man->FillNtupleDColumn(23,1,pos.y()/mm);
        man->FillNtupleDColumn(23,2,pos.z()/mm);
        man->AddNtupleRow(23);
            
        }

    if(copyNumber == 1032){ //UNAM
        man->FillNtupleDColumn(26,0,pos.x()/mm);
        man->FillNtupleDColumn(26,1,pos.y()/mm);
        man->FillNtupleDColumn(26,2,pos.z()/mm);           
        man->AddNtupleRow(26);
            
        }

    if(copyNumber == 1036){ //FERM
        man->FillNtupleDColumn(29,0,pos.x()/mm);
        man->FillNtupleDColumn(29,1,pos.y()/mm);
        man->FillNtupleDColumn(29,2,pos.z()/mm);
        man->AddNtupleRow(29);
        }

    if(copyNumber == 1040){ //X2
        man->FillNtupleDColumn(32,0,pos.x()/mm);
        man->FillNtupleDColumn(32,1,pos.y()/mm);
        man->FillNtupleDColumn(32,2,pos.z()/mm);
        man->AddNtupleRow(32); 
        }

        if(copyNumber == 1044){ //EJ1
        man->FillNtupleDColumn(35,0,pos.x()/mm);
        man->FillNtupleDColumn(35,1,pos.y()/mm);
        man->FillNtupleDColumn(35,2,pos.z()/mm);
        man->AddNtupleRow(35); 
        }


        if(copyNumber == 1048){ //EJ2
        man->FillNtupleDColumn(38,0,pos.x()/mm);
        man->FillNtupleDColumn(38,1,pos.y()/mm);
        man->FillNtupleDColumn(38,2,pos.z()/mm);
        man->AddNtupleRow(38); 
        }


        if(copyNumber == 1052){ //EJ3
        man->FillNtupleDColumn(41,0,pos.x()/mm);
        man->FillNtupleDColumn(41,1,pos.y()/mm);
        man->FillNtupleDColumn(41,2,pos.z()/mm);
        man->AddNtupleRow(41); 
        }


        if(copyNumber == 1056){ //EJ4
        man->FillNtupleDColumn(44,0,pos.x()/mm);
        man->FillNtupleDColumn(44,1,pos.y()/mm);
        man->FillNtupleDColumn(44,2,pos.z()/mm);
        man->AddNtupleRow(44); 
        }


        if(copyNumber == 1060){ //EJ5
        man->FillNtupleDColumn(47,0,pos.x()/mm);
        man->FillNtupleDColumn(47,1,pos.y()/mm);
        man->FillNtupleDColumn(47,2,pos.z()/mm);
        man->AddNtupleRow(47); 
        }


        if(copyNumber == 1064){ //EJ6
        man->FillNtupleDColumn(50,0,pos.x()/mm);
        man->FillNtupleDColumn(50,1,pos.y()/mm);
        man->FillNtupleDColumn(50,2,pos.z()/mm);
        man->AddNtupleRow(50); 
        }


        if(copyNumber == 1068){ //EJ7
        man->FillNtupleDColumn(53,0,pos.x()/mm);
        man->FillNtupleDColumn(53,1,pos.y()/mm);
        man->FillNtupleDColumn(53,2,pos.z()/mm);
        man->AddNtupleRow(53); 
        }


        if(copyNumber == 1072){ //EJ8
        man->FillNtupleDColumn(56,0,pos.x()/mm);
        man->FillNtupleDColumn(56,1,pos.y()/mm);
        man->FillNtupleDColumn(56,2,pos.z()/mm);
        man->AddNtupleRow(56); 
        }

        if(copyNumber == 1076){ //TR
        man->FillNtupleDColumn(59,0,pos.x()/mm);
        man->FillNtupleDColumn(59,1,pos.y()/mm);
        man->FillNtupleDColumn(59,2,pos.z()/mm);
        man->AddNtupleRow(59); 
        }


        if(copyNumber == 1086){ //HEX
        man->FillNtupleDColumn(62,0,pos.x()/mm);
        man->FillNtupleDColumn(62,1,pos.y()/mm);
        man->FillNtupleDColumn(62,2,pos.z()/mm);
        man->AddNtupleRow(62); 
        }




        
    
    

    return true;

}