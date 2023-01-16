#include "detector.hh"
#include "G4UnitsTable.hh"
MySensitiveDetector::MySensitiveDetector(G4String name):G4VSensitiveDetector(name)
{

}
MySensitiveDetector::~MySensitiveDetector(){

}
G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist){
    
    //Definition of what will fill the histograms
    G4Track *track=aStep->GetTrack();
    G4StepPoint *preStepPoint=aStep->GetPreStepPoint();
    G4StepPoint *postStepPoint=aStep->GetPostStepPoint();
    G4ThreeVector posPhoton=preStepPoint->GetPosition();
    G4ThreeVector momPhoton=preStepPoint->GetMomentum();
    G4double energy =momPhoton.mag();
    G4double wlen= ((1.239841939*eV*um)/momPhoton.mag());
    //Only if Multithreaded mode is not being used
    #ifndef G4MULTITHREADED
    G4cout<<"Photon position"<<posPhoton<<G4endl;
    #endif


    G4AnalysisManager *man = G4AnalysisManager::Instance();
    G4double n=0.33*um;
    G4int evt =G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
    G4cout<<"Wavelength: "<<G4BestUnit(wlen,"Length")<<G4endl;
    G4cout<<"Energy: "<<G4BestUnit(energy,"Energy")<<G4endl;
    

    man->FillH1(1,wlen);
    man->FillH1(2,evt);
    man->FillH1(3,energy);
   man->FillH2(0,energy, wlen);
return true;}