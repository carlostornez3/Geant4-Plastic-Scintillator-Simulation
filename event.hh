#ifndef EVENT_HH
#define EVENT_HH
#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "G4AnalysisManager.hh"
#include "run.hh"
#include "G4UnitsTable.hh"
#include "G4RunManager.hh"
#include "G4Threading.hh"
#include "G4AutoLock.hh"
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
private:
G4double fEdep,meanTF,meanNF,hola;
G4double fnumber;
G4int total=0,n=0,total2=0;


};


#endif