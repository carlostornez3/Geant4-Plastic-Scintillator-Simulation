#include "stepping.hh"
MySteppingAction::MySteppingAction(MyEventAction *eventAction){
    fEventAction=eventAction;
}

MySteppingAction::~MySteppingAction(){

}
void MySteppingAction::UserSteppingAction(const G4Step *step){
    G4double edep = step->GetTotalEnergyDeposit();
    fEventAction->AddEdep(edep);
}