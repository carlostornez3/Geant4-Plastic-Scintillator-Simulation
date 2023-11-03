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
    if(MyDetectorConstruction::scintillatorArrangement == "SCBT"){
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
            }else {
                fEventAction->AddEdepSCBT("noiseX1",edep);
                }
            
        }

        if(copyNumber == 6){
           if(particleName == "mu-" || particleName == "pi+"){
                fEventAction->AddEdepSCBT("Y1",edep);
            }else {
                fEventAction->AddEdepSCBT("noiseY1",edep);
                }
            
        }

        if(copyNumber == 10){
            if(particleName == "mu-" || particleName == "pi+"){
                fEventAction->AddEdepSCBT("CZ",edep);
            }else {
                fEventAction->AddEdepSCBT("noiseCZ",edep);
                }
            
        }

        if(copyNumber == 14){
            if(particleName == "mu-" || particleName == "pi+"){
                fEventAction->AddEdepSCBT("S0",edep);
            }else {
                fEventAction->AddEdepSCBT("noiseS0",edep);
                }
            
        }

        if(copyNumber == 18){
            if(particleName == "mu-" || particleName == "pi+"){
                fEventAction->AddEdepSCBT("S1",edep);
            }else {
                fEventAction->AddEdepSCBT("noiseS1",edep);
                }
            
        }

        if(copyNumber == 22){
            if(particleName == "mu-" || particleName == "pi+"){
                fEventAction->AddEdepSCBT("S2",edep);
            }else {
                fEventAction->AddEdepSCBT("noiseS2",edep);
                }
            
        }

        if(copyNumber == 26){
            if(particleName == "mu-" || particleName == "pi+"){
                fEventAction->AddEdepSCBT("BC",edep);
            }else {
                fEventAction->AddEdepSCBT("noiseBC",edep);
                }
            
        }

        if(copyNumber == 30){
            if(particleName == "mu-" || particleName == "pi+"){
                fEventAction->AddEdepSCBT("ACOR",edep);
            }else {
                fEventAction->AddEdepSCBT("noiseACOR",edep);
                }
            
        }

        if(copyNumber == 34){
            if(particleName == "mu-" || particleName == "pi+"){
                fEventAction->AddEdepSCBT("UNAM",edep);
            }else {
                fEventAction->AddEdepSCBT("noiseUNAM",edep);
                }
            
        }

        if(copyNumber == 38){
           if(particleName == "mu-" || particleName == "pi+"){
                fEventAction->AddEdepSCBT("FERM",edep);
            }else {
                fEventAction->AddEdepSCBT("noiseFERM",edep);
                }
            
        }

        if(copyNumber == 42){
            if(particleName == "mu-" || particleName == "pi+"){
                fEventAction->AddEdepSCBT("X2",edep);
            }else {
                fEventAction->AddEdepSCBT("noiseX2",edep);
                }
            
        }
        
    }

}