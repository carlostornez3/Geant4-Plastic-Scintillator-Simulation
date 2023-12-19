#include "stepping.hh"
#include "G4VPhysicalVolume.hh"
MySteppingAction::MySteppingAction(MyEventAction *eventAction){
    fEventAction=eventAction;
}

MySteppingAction::~MySteppingAction(){

}
void MySteppingAction::UserSteppingAction(const G4Step *step){
    if(MyDetectorConstruction::scintillatorArrangement == "SC"){
        G4LogicalVolume *volume=step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
        const MyDetectorConstruction *detectorConstruction = static_cast<const MyDetectorConstruction*>(G4RunManager::GetRunManager()->GetUserDetectorConstruction());
        G4LogicalVolume *fScoringVolume= detectorConstruction->GetScoringVolume();
        if (volume != fScoringVolume)
        { 
            return;
        }
        
        //Acumulates the energy in the step using the method created in event.hh
        G4double edep = step->GetTotalEnergyDeposit();
        fEventAction->AddEdep(edep);
    
    
    }
    if(MyDetectorConstruction::scintillatorArrangement == "SCBT"|| MyDetectorConstruction::scintillatorArrangement == "RPCBT"){
        G4LogicalVolume *volume=step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
        G4VPhysicalVolume* physicalVolume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
        G4int copyNumber = physicalVolume->GetCopyNo();
        
        G4ParticleDefinition* particleDefinition = step->GetTrack()->GetDefinition();

    // Obtener el nombre de la partícula
        G4String particleName = particleDefinition->GetParticleName();
        G4double edep = step->GetTotalEnergyDeposit();
   
        
        if(copyNumber == 2){
            
            if(particleName == "mu-" || particleName == "pi+"){
                fEventAction->AddEdepSCBT("X1",edep);
            }else if(particleName != "opticalphoton") {
                fEventAction->AddEdepSCBT("noiseX1",edep);
                //G4cout<<particleName<< " "<<copyNumber<<G4endl;
                }
            
        }

        if(copyNumber == 6){
           if(particleName == "mu-" || particleName == "pi+"){
                fEventAction->AddEdepSCBT("Y1",edep);
            }else if(particleName != "opticalphoton") {
                fEventAction->AddEdepSCBT("noiseY1",edep);
                //G4cout<<particleName<< " "<<copyNumber<<G4endl;
                }
            
        }

        if(copyNumber == 10){
            if(particleName == "mu-" || particleName == "pi+"){
                fEventAction->AddEdepSCBT("CZ",edep);
            }else if(particleName != "opticalphoton") {
                fEventAction->AddEdepSCBT("noiseCZ",edep);
                //G4cout<<particleName<< " "<<copyNumber<<G4endl;
                }
            
        }

        if(copyNumber == 14){
            if(particleName == "mu-" || particleName == "pi+"){
                fEventAction->AddEdepSCBT("S0",edep);
            }else if(particleName != "opticalphoton") {
                fEventAction->AddEdepSCBT("noiseS0",edep);
                //G4cout<<particleName<< " "<<copyNumber<<G4endl;
                }
            
        }

        if(copyNumber == 18){
            if(particleName == "mu-" || particleName == "pi+"){
                fEventAction->AddEdepSCBT("S1",edep);
            }else if(particleName != "opticalphoton") {
                fEventAction->AddEdepSCBT("noiseS1",edep);
                //G4cout<<particleName<< " "<<copyNumber<<G4endl;
                }
            
        }

        if(copyNumber == 22){
            if(particleName == "mu-" || particleName == "pi+"){
                fEventAction->AddEdepSCBT("S2",edep);
            }else if(particleName != "opticalphoton") {
                fEventAction->AddEdepSCBT("noiseS2",edep);
                //G4cout<<particleName<< " "<<copyNumber<<G4endl;
                }
            
        }

        if(copyNumber == 26){
            if(particleName == "mu-" || particleName == "pi+"){
                fEventAction->AddEdepSCBT("BC",edep);
            }else if(particleName != "opticalphoton") {
                fEventAction->AddEdepSCBT("noiseBC",edep);
                //G4cout<<particleName<< " "<<copyNumber<<G4endl;
                }
            
        }

        if(copyNumber == 30){
            if(particleName == "mu-" || particleName == "pi+"){
                fEventAction->AddEdepSCBT("ACOR",edep);
            }else if(particleName != "opticalphoton") {
                fEventAction->AddEdepSCBT("noiseACOR",edep);
                //G4cout<<particleName<< " "<<copyNumber<<G4endl;
                }
            
        }

        if(copyNumber == 34){
            if(particleName == "mu-" || particleName == "pi+"){
                fEventAction->AddEdepSCBT("UNAM",edep);
            }else if(particleName != "opticalphoton") {
                fEventAction->AddEdepSCBT("noiseUNAM",edep);
                //G4cout<<particleName<< " "<<copyNumber<<G4endl;
                }
            
        }

        if(copyNumber == 38){
           if(particleName == "mu-" || particleName == "pi+"){
                fEventAction->AddEdepSCBT("FERM",edep);
            }else if(particleName != "opticalphoton") {
                fEventAction->AddEdepSCBT("noiseFERM",edep);
                //G4cout<<particleName<< " "<<copyNumber<<G4endl;
                }
            
        }

        if(copyNumber == 42){
            if(particleName == "mu-" || particleName == "pi+"){
                fEventAction->AddEdepSCBT("X2",edep);
            }else if(particleName != "opticalphoton") {
                fEventAction->AddEdepSCBT("noiseX2",edep);
                //G4cout<<particleName<< " "<<copyNumber<<G4endl;
                }
            
        }


        if(copyNumber == 46){
            if(particleName == "mu-" || particleName == "pi+"){
                fEventAction->AddEdepSCBT("EJ1",edep);
            }else if(particleName != "opticalphoton") {
                fEventAction->AddEdepSCBT("noiseEJ1",edep);
                //G4cout<<particleName<< " "<<copyNumber<<G4endl;
                }
            
        }

        if(copyNumber == 50){
            if(particleName == "mu-" || particleName == "pi+"){
                fEventAction->AddEdepSCBT("EJ2",edep);
            }else if(particleName != "opticalphoton") {
                fEventAction->AddEdepSCBT("noiseEJ2",edep);
                //G4cout<<particleName<< " "<<copyNumber<<G4endl;
                }
            
        }

        if(copyNumber == 54){
            if(particleName == "mu-" || particleName == "pi+"){
                fEventAction->AddEdepSCBT("EJ3",edep);
            }else if(particleName != "opticalphoton") {
                fEventAction->AddEdepSCBT("noiseEJ3",edep);
                //G4cout<<particleName<< " "<<copyNumber<<G4endl;
                }
            
        }


        if(copyNumber == 58){
            if(particleName == "mu-" || particleName == "pi+"){
                fEventAction->AddEdepSCBT("EJ4",edep);
            }else if(particleName != "opticalphoton") {
                fEventAction->AddEdepSCBT("noiseEJ4",edep);
                //G4cout<<particleName<< " "<<copyNumber<<G4endl;
                }
            
        }


        if(copyNumber == 62){
            if(particleName == "mu-" || particleName == "pi+"){
                fEventAction->AddEdepSCBT("EJ5",edep);
            }else if(particleName != "opticalphoton") {
                fEventAction->AddEdepSCBT("noiseEJ5",edep);
                //G4cout<<particleName<< " "<<copyNumber<<G4endl;
                }
            
        }


        if(copyNumber == 66){
            if(particleName == "mu-" || particleName == "pi+"){
                fEventAction->AddEdepSCBT("EJ6",edep);
            }else if(particleName != "opticalphoton") {
                fEventAction->AddEdepSCBT("noiseEJ6",edep);
                //G4cout<<particleName<< " "<<copyNumber<<G4endl;
                }
            
        }


        if(copyNumber == 70){
            if(particleName == "mu-" || particleName == "pi+"){
                fEventAction->AddEdepSCBT("EJ7",edep);
            }else if(particleName != "opticalphoton") {
                fEventAction->AddEdepSCBT("noiseEJ7",edep);
                //G4cout<<particleName<< " "<<copyNumber<<G4endl;
                }
            
        }

        if(copyNumber == 74){
            if(particleName == "mu-" || particleName == "pi+"){
                fEventAction->AddEdepSCBT("EJ8",edep);
            }else if(particleName != "opticalphoton") {
                fEventAction->AddEdepSCBT("noiseEJ8",edep);
                //G4cout<<particleName<< " "<<copyNumber<<G4endl;
                }
            
        }


        if(copyNumber == 78){
            if(particleName == "mu-" || particleName == "pi+"){
                fEventAction->AddEdepSCBT("TR",edep);
            }else if(particleName != "opticalphoton") {
                fEventAction->AddEdepSCBT("noiseTR",edep);
                //G4cout<<particleName<< " "<<copyNumber<<G4endl;
                }
            
        }


        if(copyNumber == 82){
            if(particleName == "mu-" || particleName == "pi+"){
                fEventAction->AddEdepSCBT("HEX",edep);
            }else if(particleName != "opticalphoton") {
                fEventAction->AddEdepSCBT("noiseHEX",edep);
                //G4cout<<particleName<< " "<<copyNumber<<G4endl;
                }
            
        }

        


        
        
    }

}