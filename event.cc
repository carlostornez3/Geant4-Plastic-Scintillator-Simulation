#include "event.hh"
MyEventAction::MyEventAction(MyRunAction*){
    fEdep=0;
    fnumber=0;

}
MyEventAction::~MyEventAction(){}
void MyEventAction::BeginOfEventAction(const G4Event*){
fEdep=0;
fnumber=0;
}
void MyEventAction::EndOfEventAction(const G4Event*){
    G4int evt =G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();


    G4cout<<"Evento: "<< evt<< G4endl;
    G4cout<<"Energy deposition: "<<G4BestUnit(fEdep,"Energy")<<G4endl;


    //Passes the energy Deposition  to a histogram 
    G4AnalysisManager *man=G4AnalysisManager::Instance();
    man->FillH1(0,fEdep);
    meanTF= man->GetH1(15)->mean();
    G4cout<<"Average TOF:"<<meanTF<<G4endl;
    G4cout<<"Average TOF:"<<G4BestUnit(meanTF,"Time")<<G4endl;
    man->FillH1(16,meanTF);
    man->GetH1(15)->reset();
    //G4cout<<"mean TOF:"<<G4BestUnit(man->GetH1(15)->mean(),"Time")<<G4endl;
    //G4cout<<"mean TOF:"<<man->GetH1(15)->mean()<<G4endl;

    
    //G4MUTEXLOCK(&mutex );
    meanNF= man->GetH1(17)->mean();
    //total = meanNF-n;
    /*total2=total2+total;
    man->GetH1(19)->reset();
    man->FillH1(19,total2);*/
    //n=meanNF;
    man->FillH1(18,meanNF);
    
    
    G4cout<<"Number of Photons: "<<meanNF<<G4endl;
    //G4MUTEXUNLOCK(&mutex );


}