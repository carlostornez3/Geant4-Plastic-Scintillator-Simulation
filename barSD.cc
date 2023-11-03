#include "barSD.hh"

MyBarDetector::MyBarDetector(G4String name):G4VSensitiveDetector(name), isFirstHit(true){

}

MyBarDetector::~MyBarDetector(){

}

G4bool MyBarDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist){
    
    

    G4Track *track=aStep->GetTrack();
    const G4ParticleDefinition* particleDefinition = track->GetDefinition();
    G4String particleName = particleDefinition->GetParticleName();
    if(particleName == "opticalphoton"){
        return true;
    }
    
    
    if (aStep->IsFirstStepInVolume()) {
        G4AnalysisManager *man = G4AnalysisManager::Instance();

        G4VPhysicalVolume* physicalVolume = aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
        G4int copyNumber = physicalVolume->GetCopyNo();
        //track->SetTrackStatus(fStopAndKill);
        G4StepPoint *preStepPoint=aStep->GetPreStepPoint();
        G4StepPoint *postStepPoint=aStep->GetPostStepPoint();
        
    // G4cout<<"particula detectada"<<G4endl;
        G4ThreeVector pos = preStepPoint->GetPosition();
        G4int trackID =  aStep->GetTrack()->GetTrackID();
        G4int eventID = G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID();
        G4cout<<"Particula: "<<particleName<<" coordenadas: "<<pos<<" CopyNo: "<<copyNumber<<" TrackID: "<<trackID<<" EventID: " << eventID<<G4endl;
    }
    
    

    return true;

}