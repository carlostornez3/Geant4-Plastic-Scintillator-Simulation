#ifndef BARSD_HH
#define BARSD_HH

#include "G4VSensitiveDetector.hh"
#include "G4AnalysisManager.hh"
//#include "g4root.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "event.hh"
#include "construction.hh"
#include "G4UnitsTable.hh"
#include <unordered_map>
#include <set>
#include "G4EventManager.hh"
#include "G4Event.hh"
#include "G4Track.hh"

class MyBarDetector : public G4VSensitiveDetector{

    public:
    MyBarDetector(G4String);
    ~MyBarDetector();
    
  //  virtual void  EndOfEvent (G4HCofThisEvent *);
    private:
    virtual G4bool ProcessHits(G4Step *,G4TouchableHistory *);
    G4bool isFirstHit;
   


};
#endif