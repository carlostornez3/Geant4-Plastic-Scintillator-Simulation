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
fEdepnoiseX1=0, fEdepnoiseY1=0, fEdepnoiseCZ=0, fEdepnoiseS0=0, fEdepnoiseS1=0, fEdepnoiseS2=0,fEdepnoiseBC=0, fEdepnoiseUNAM=0, fEdepnoiseACOR=0,fEdepnoiseFERM=0, fEdepnoiseX2=0;

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
        G4AnalysisManager *man=G4AnalysisManager::Instance();
        G4int evt =G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
        G4cout<<"Evento: "<< evt<< G4endl;
       
        fillingNtuples("X1",0,fEdepX1,fEdepnoiseX1);
        fillingNtuples("Y1",1,fEdepY1,fEdepnoiseY1);
        fillingNtuples("CZ",2,fEdepCZ,fEdepnoiseCZ);
        fillingNtuples("S0",3,fEdepS0,fEdepnoiseS0);
        fillingNtuples("S1",4,fEdepS1,fEdepnoiseS1);
        fillingNtuples("S2",5,fEdepS2,fEdepnoiseS2);
        fillingNtuples("BC",6,fEdepBC,fEdepnoiseBC);
        fillingNtuples("ACOR",7,fEdepACOR,fEdepACOR);
        fillingNtuples("UNAM",8,fEdepUNAM,fEdepUNAM);
        fillingNtuples("FERM",9,fEdepFERM,fEdepFERM);
        fillingNtuples("X2",10,fEdepX2,fEdepnoiseX2);
    
        
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


   if(name == "noiseX1"){
        fEdepnoiseX1 +=edep;
    }
    if(name == "noiseY1"){
        fEdepnoiseY1 +=edep;
    }
    if(name == "noiseCZ"){
        fEdepnoiseCZ +=edep;
    }
    if(name == "noiseS0"){
        fEdepnoiseS0 +=edep;
    }
    if(name == "noiseS1"){
        fEdepnoiseS1 +=edep;
    }
    if(name == "noiseS2"){
        fEdepnoiseS2 +=edep;
    }
    if(name == "noiseBC"){
        fEdepnoiseBC +=edep;
    }
    if(name == "noiseACOR"){
        fEdepnoiseACOR +=edep;
    }
    if(name == "noiseUNAM"){
        fEdepnoiseUNAM +=edep;
    }
    if(name == "noiseFERM"){
        fEdepnoiseFERM +=edep;
    }
    if(name == "noiseX2"){
        fEdepnoiseX2 +=edep;
    }
}

 void MyEventAction::fillingNtuples(G4String name, G4int scintillatorPosition, G4double fedep, G4double fedepnoise){
    G4AnalysisManager *man=G4AnalysisManager::Instance();
    //scintillatorPosition=scintillatorPosition*3;

    man->FillNtupleDColumn(scintillatorPosition*3+1,0, fedep);
    man->FillNtupleDColumn(scintillatorPosition*3+1,3, fedepnoise);

    G4double meanTF = man->GetH1(scintillatorPosition*2)->mean();
    man->GetH1(scintillatorPosition*2)->reset();
    man->FillNtupleDColumn(scintillatorPosition*3+1,1, meanTF);
    
    G4double meanNF = man->GetH1(scintillatorPosition*2+1)->mean();
    man->GetH1(scintillatorPosition*2+1)->reset();
    man->FillNtupleDColumn(scintillatorPosition*3+1,2, meanNF);
    man->AddNtupleRow(scintillatorPosition*3+1);

    name = "Energy Deposition by "+ name+": ";
    G4cout<<name<<G4BestUnit(fedep,"Energy")<<G4endl;
    G4cout<<name<<fedep<<G4endl;
 }