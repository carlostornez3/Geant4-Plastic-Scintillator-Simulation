#ifndef EVENT_HH
#define EVENT_HH
#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "G4AnalysisManager.hh"
//#include "g4root.hh"
#include "run.hh"
#include "G4UnitsTable.hh"
#include "G4RunManager.hh"
#include "G4Threading.hh"
#include "G4AutoLock.hh"
#include "construction.hh"
class MyEventAction:public G4UserEventAction{
public:
MyEventAction(MyRunAction*);
~MyEventAction();
G4Mutex mutex; 
    virtual void BeginOfEventAction(const G4Event*);
    virtual void EndOfEventAction(const G4Event*);
    //Creation of a method that acumulates the energy deposition.
    void AddEdep(G4double edep){fEdep +=edep;}
    void AddNumber(){fnumber++;}
    void AddEdepSCBT(G4String name, G4double edep);
    void fillingHistograms(G4String name, G4int scintillatorPosition, G4double fedep, G4double fedepnoise);
private:
G4double fEdep,meanTF,meanNF,hola;
G4double fnumber;
G4int total=0,n=0,total2=0;

G4double fEdepX1,fEdepY1,fEdepCZ,fEdepS0,fEdepS1,fEdepS2,fEdepBC,fEdepACOR,fEdepUNAM,fEdepFERM, fEdepX2;
G4double fEdepnoiseX1,fEdepnoiseY1,fEdepnoiseCZ,fEdepnoiseS0,fEdepnoiseS1,fEdepnoiseS2,fEdepnoiseBC,fEdepnoiseACOR,fEdepnoiseUNAM,fEdepnoiseFERM, fEdepnoiseX2;
};


#endif