#include "detector.hh"

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
    G4double wlen= (1.239841939*eV/momPhoton.mag())*1E+003;
    G4double energy=(1.239841939/(wlen*1E-003));
    //Only if Multithreaded mode is not being used
    #ifndef G4MULTITHREADED
    G4cout<<"Photon position"<<posPhoton<<G4endl;
    #endif


    G4AnalysisManager *man = G4AnalysisManager::Instance();

    G4int evt =G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
    
    man->FillH1(1,wlen);
    man->FillH1(2,evt);
    man->FillH1(3,energy);
    man->FillH2(0,energy, wlen);
return true;}