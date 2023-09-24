#include "detector.hh"
#include "G4UnitsTable.hh"
#include <cmath>
MySensitiveDetector::MySensitiveDetector(G4String name):G4VSensitiveDetector(name)
{   
 
}
MySensitiveDetector::~MySensitiveDetector(){

}
G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist){
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    //Definition of what will fill the histograms
    G4Track *track=aStep->GetTrack();
    track->SetTrackStatus(fStopAndKill);
    if(MyDetectorConstruction::scintillatorArrangement == "SC"){
    G4StepPoint *preStepPoint=aStep->GetPreStepPoint();
    G4StepPoint *postStepPoint=aStep->GetPostStepPoint();
    G4ThreeVector posPhoton=preStepPoint->GetPosition();
    G4double posmodule, posmodule2;
if (track) {
        const G4ParticleDefinition* particleDefinition = track->GetDefinition();
        if (particleDefinition) {
            G4String particleName = particleDefinition->GetParticleName();
            //G4cout << "Nombre de la partícula: " << particleName << G4endl;
            if(particleName == "proton"){
            posmodule = posPhoton.x()*posPhoton.x()+posPhoton.y()*posPhoton.y();
            posmodule2=std::sqrt(posmodule2);
             G4cout<<posPhoton<<" "<<posmodule2<<G4endl;
            }
        }
    }
    
    G4ThreeVector momPhoton=preStepPoint->GetMomentum();
    G4double energy =momPhoton.mag();
    G4double wlen= ((1.239841939*eV*um)/momPhoton.mag());
    
    
    G4double time = preStepPoint->GetLocalTime();
     //Only if Multithreaded mode is not being used

   #ifndef G4MULTITHREADED
    G4cout<<"TOF:  "<<G4BestUnit(time,"Time")<<G4endl;
    G4cout<<"TOF:  "<<time<<G4endl;

    #endif

    
    G4int idEvt =G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
    if(idEvt==evt){
        numberOfPhotons++;
        man->GetH1(17)->reset();
        man->FillH1(17,numberOfPhotons);
    } else{
        evt=idEvt;
        numberOfPhotons=1;
        man->GetH1(17)->reset();
        man->FillH1(17,numberOfPhotons);
    }
    
    
    
    
    
    man->FillH1(1,wlen);
    man->FillH1(2,idEvt);
    man->FillH1(3,energy);
    if(idEvt<10){
    man->FillH1(4,idEvt);
    }
    
    if(idEvt<10){
    man->FillH1(idEvt+5,time);
    }
    man->FillH1(15,time);

    
   man->FillH2(0,energy, wlen);
    }

    if(MyDetectorConstruction::scintillatorArrangement == "SCBT"){
    G4StepPoint *preStepPoint=aStep->GetPreStepPoint();
    G4StepPoint *postStepPoint=aStep->GetPostStepPoint();
    const G4ParticleDefinition* particleDefinition = track->GetDefinition();
    G4String particleName = particleDefinition->GetParticleName();
    G4cout << "Nombre de la partícula: " << particleName << G4endl;
            
            

    G4ThreeVector momPhoton=preStepPoint->GetMomentum();
    G4double energy =momPhoton.mag();
    G4double wlen= ((1.239841939*eV*um)/momPhoton.mag());
    
    
    G4double time = preStepPoint->GetLocalTime();
     //Only if Multithreaded mode is not being used

   #ifndef G4MULTITHREADED
    G4cout<<"TOF:  "<<G4BestUnit(time,"Time")<<G4endl;
    G4cout<<"TOF:  "<<time<<G4endl;

    #endif

    
    G4int idEvt =G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
    if(idEvt==evt){
        numberOfPhotons++;
        man->GetH1(17)->reset();
        man->FillH1(17,numberOfPhotons);
    } else{
        evt=idEvt;
        numberOfPhotons=1;
        man->GetH1(17)->reset();
        man->FillH1(17,numberOfPhotons);
    }
    
    
    
    
    
    man->FillH1(1,wlen);
    man->FillH1(2,idEvt);
    man->FillH1(3,energy);
    if(idEvt<10){
    man->FillH1(4,idEvt);
    }
    
    if(idEvt<10){
    man->FillH1(idEvt+5,time);
    }
    man->FillH1(15,time);

    
   man->FillH2(0,energy, wlen);
    }

return true;}