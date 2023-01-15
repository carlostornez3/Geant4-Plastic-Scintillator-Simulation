#ifndef EVENT_HH
#define EVENT_HH
#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "G4AnalysisManager.hh"
#include "run.hh"
#include "G4UnitsTable.hh"
class MyEventAction:public G4UserEventAction{
public:
MyEventAction(MyRunAction*);
~MyEventAction();

    virtual void BeginOfEventAction(const G4Event*);
    virtual void EndOfEventAction(const G4Event*);
    //Creation of a method that acumulates the energy deposition.
    void AddEdep(G4double edep){fEdep +=edep;}
private:
G4double fEdep;

};


#endif