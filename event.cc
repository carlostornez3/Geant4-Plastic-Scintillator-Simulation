#include "event.hh"
MyEventAction::MyEventAction(MyRunAction*){
    fEdep=0.;

}
MyEventAction::~MyEventAction(){}
void MyEventAction::BeginOfEventAction(const G4Event*){
fEdep=0;
}
void MyEventAction::EndOfEventAction(const G4Event*){
    
    
    G4cout<<"Energy deposition: "<<G4BestUnit(fEdep,"Energy")<<G4endl;
    
    //Passes the energy Deposition  to a histogram 
    G4AnalysisManager *man=G4AnalysisManager::Instance();
    man->FillH1(0,fEdep);
}