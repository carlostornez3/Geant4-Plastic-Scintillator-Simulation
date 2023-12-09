#ifndef RUN_HH
#define RUN_HH

#include "G4UserRunAction.hh"
//#include "G4GenericAnalysisManager.hh"
#include "G4Run.hh"
#include "G4SystemOfUnits.hh"
//#include "g4root.hh"
#include "G4AnalysisManager.hh"
//using G4AnalysisManager = G4GenericAnalysisManager;

class MyRunAction:public G4UserRunAction{
public:
    MyRunAction();
    ~MyRunAction();
    void histogramCreation(G4String scintillatorName,G4String scintillatorType, G4double thickness, G4int numberOfEvents, G4double mtofLL, G4double mtofUL);
    void NtupleCreation(G4String scintillatorName,G4String category,G4int tupleNumber);
    G4String treeName, histogramName;
    virtual void BeginOfRunAction(const G4Run *);
    virtual void EndOfRunAction(const G4Run *);
    static G4int noc; //number of calls of void funcion histogramCreation. This variable is used as a counter
    static G4int noc2;
};
#endif