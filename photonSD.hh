#ifndef PHOTONSD_HH
#define PHOTONSD_HH

#include "G4VSensitiveDetector.hh"
#include "G4AnalysisManager.hh"
//#include "g4root.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "event.hh"
#include "construction.hh"
#include "G4UnitsTable.hh"

class MyPhotoDetector: public G4VSensitiveDetector{
    public:
    MyPhotoDetector(G4String);
    ~MyPhotoDetector();
    void NtupleFilling(G4String scintillatorName, G4int scintillatorPosition, G4int& evtNumber,G4int& numberOfPhotons,G4Step *aStep);
    
    
    private:
    virtual G4bool ProcessHits(G4Step *,G4TouchableHistory *);
    static G4int noc;
    G4int numberOfPhotons=0,evt=0;
    G4int npX1,npY1,npCZ,npS0,npS1,npS2,npBC,npACORDE,npUNAM,npFERM,npX2;
    G4int evtX1,evtY1,evtCZ,evtS0,evtS1,evtS2,evtBC,evtACORDE,evtUNAM,evtFERM,evtX2;
    G4int evtEJ1,evtEJ2,evtEJ3,evtEJ4,evtEJ5,evtEJ6,evtEJ7,evtEJ8,evtHex,evtTR,evtDump;
    G4int npEJ1,npEJ2,npEJ3,npEJ4,npEJ5,npEJ6,npEJ7,npEJ8,npHex,npTR,npDump;
};


#endif