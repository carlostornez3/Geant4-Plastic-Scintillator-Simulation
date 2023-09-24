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
        
        
        //Acumulates the energy in the step using the method created in event.hh
        //G4cout<<copyNumber<<G4endl;
        if(copyNumber == 2){
            G4double edep = step->GetTotalEnergyDeposit();
            fEventAction->AddEdepSCBT("X1",edep);
            
        }

        if(copyNumber == 6){
            G4double edep = step->GetTotalEnergyDeposit();
            fEventAction->AddEdepSCBT("Y1",edep);
            
        }

        if(copyNumber == 10){
            G4double edep = step->GetTotalEnergyDeposit();
            fEventAction->AddEdepSCBT("CZ",edep);
            
        }

        if(copyNumber == 14){
            G4double edep = step->GetTotalEnergyDeposit();
            fEventAction->AddEdepSCBT("S0",edep);
            
        }

        if(copyNumber == 18){
            G4double edep = step->GetTotalEnergyDeposit();
            fEventAction->AddEdepSCBT("S1",edep);
            
        }

        if(copyNumber == 22){
            G4double edep = step->GetTotalEnergyDeposit();
            fEventAction->AddEdepSCBT("S2",edep);
            
        }

        if(copyNumber == 26){
            G4double edep = step->GetTotalEnergyDeposit();
            fEventAction->AddEdepSCBT("BC",edep);
            
        }

        if(copyNumber == 30){
            G4double edep = step->GetTotalEnergyDeposit();
            fEventAction->AddEdepSCBT("ACOR",edep);
            
        }

        if(copyNumber == 34){
            G4double edep = step->GetTotalEnergyDeposit();
            fEventAction->AddEdepSCBT("UNAM",edep);
            
        }

        if(copyNumber == 38){
            G4double edep = step->GetTotalEnergyDeposit();
            fEventAction->AddEdepSCBT("FERM",edep);
            
        }

        if(copyNumber == 42){
            G4double edep = step->GetTotalEnergyDeposit();
            fEventAction->AddEdepSCBT("X2",edep);
            
        }
        
    }

}