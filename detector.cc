#include "detector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name):G4VSensitiveDetector(name)
{

}
MySensitiveDetector::~MySensitiveDetector(){

}
G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist){
    G4Track *track=aStep->GetTrack();
   // track->SetTrackStatus(fStopAndKill);
    G4StepPoint *preStepPoint=aStep->GetPreStepPoint();
    G4StepPoint *postStepPoint=aStep->GetPostStepPoint();
    G4ThreeVector posPhoton=preStepPoint->GetPosition();
    G4ThreeVector momPhoton=preStepPoint->GetMomentum();
    G4double wlen= (1.239841939*eV/momPhoton.mag())*1E+003;
    #ifndef G4MULTITHREADED
    G4cout<<"Photon position"<<posPhoton<<G4endl;
    #endif
    G4AnalysisManager *man = G4AnalysisManager::Instance();

    G4int evt =G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

    man->FillNtupleIColumn(0,evt);
    man->FillNtupleDColumn(1,posPhoton[0]);
    man->FillNtupleDColumn(2,posPhoton[1]);
    man->FillNtupleDColumn(3,posPhoton[2]);
    man->FillNtupleDColumn(4,wlen);
    man->AddNtupleRow(0);

    return true;}