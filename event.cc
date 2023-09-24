#include "event.hh"
MyEventAction::MyEventAction(MyRunAction*){
    fEdep=0;
    fnumber=0;

}
MyEventAction::~MyEventAction(){}
void MyEventAction::BeginOfEventAction(const G4Event*){
fEdep=0;
fnumber=0;
fEdepX1=0, fEdepY1=0, fEdepCZ=0, fEdepS0=0, fEdepS1=0, fEdepS2=0,fEdepBC=0, fEdepUNAM=0, fEdepACOR=0,fEdepFERM=0, fEdepX2=0;

}
void MyEventAction::EndOfEventAction(const G4Event*){

    if(MyDetectorConstruction::scintillatorArrangement=="SC"){
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
    }else if(MyDetectorConstruction::scintillatorArrangement=="SCBT"){
        G4int evt =G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
        G4cout<<"Evento: "<< evt<< G4endl;
        G4cout<<"Energy deposition X1: "<<G4BestUnit(fEdepX1,"Energy")<<G4endl;
        G4cout<<"Energy deposition Y1: "<<G4BestUnit(fEdepY1,"Energy")<<G4endl;
        G4cout<<"Energy deposition CZ: "<<G4BestUnit(fEdepCZ,"Energy")<<G4endl;
        G4cout<<"Energy deposition S0: "<<G4BestUnit(fEdepS0,"Energy")<<G4endl;
        G4cout<<"Energy deposition S1: "<<G4BestUnit(fEdepS1,"Energy")<<G4endl;
        G4cout<<"Energy deposition S2: "<<G4BestUnit(fEdepS2,"Energy")<<G4endl;
        G4cout<<"Energy deposition BC: "<<G4BestUnit(fEdepBC,"Energy")<<G4endl;
        G4cout<<"Energy deposition ACORDE: "<<G4BestUnit(fEdepACOR,"Energy")<<G4endl;
        G4cout<<"Energy deposition UNAM: "<<G4BestUnit(fEdepUNAM,"Energy")<<G4endl;
        G4cout<<"Energy deposition FERM: "<<G4BestUnit(fEdepFERM,"Energy")<<G4endl;
        G4cout<<"Energy deposition X2: "<<G4BestUnit(fEdepX2,"Energy")<<G4endl;

        
    }
    //G4MUTEXUNLOCK(&mutex );
    


}

void MyEventAction::AddEdepSCBT(G4String name, G4double edep){

    if(name == "X1"){
        fEdepX1 +=edep;
    }
    if(name == "Y1"){
        fEdepY1 +=edep;
    }
    if(name == "CZ"){
        fEdepCZ +=edep;
    }
    if(name == "S0"){
        fEdepS0 +=edep;
    }
    if(name == "S1"){
        fEdepS1 +=edep;
    }
    if(name == "S2"){
        fEdepS2 +=edep;
    }
    if(name == "BC"){
        fEdepBC +=edep;
    }
    if(name == "ACOR"){
        fEdepACOR +=edep;
    }
    if(name == "UNAM"){
        fEdepUNAM +=edep;
    }
    if(name == "FERM"){
        fEdepFERM +=edep;
    }
    if(name == "X2"){
        fEdepX2 +=edep;
    }
}