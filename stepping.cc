#include "stepping.hh"
#include "G4VPhysicalVolume.hh"
MySteppingAction::MySteppingAction(MyEventAction *eventAction){
    fEventAction=eventAction;
}

MySteppingAction::~MySteppingAction(){

}
void MySteppingAction::UserSteppingAction(const G4Step *step){
    G4LogicalVolume *volume=step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
    G4VPhysicalVolume* physicalVolume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
    G4int copyNumber = physicalVolume->GetCopyNo();
    const MyDetectorConstruction *detectorConstruction = static_cast<const MyDetectorConstruction*>(G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    G4LogicalVolume *fScoringVolume= detectorConstruction->GetScoringVolume();
    /*if (volume != fScoringVolume)
    { 
        return;
    }*/
    
    if(copyNumber == 2 || copyNumber == 6){
    //Acumulates the energy in the step using the method created in event.hh
    G4double edep = step->GetTotalEnergyDeposit();
    fEventAction->AddEdep(edep);}
}