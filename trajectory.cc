#include "trajectory.hh"

MyTrackingAction::MyTrackingAction(){}

MyTrackingAction::~MyTrackingAction(){}

void MyTrackingAction::PreUserTrackingAction(const G4Track* track){

    
    const G4ParticleDefinition* particle = track->GetDefinition();
        if (particle->GetParticleName() == "opticalphoton" || track->GetParentID()==0) {
            G4TrackingManager* trackingManager = G4EventManager::GetEventManager()->GetTrackingManager();
           trackingManager->SetStoreTrajectory(0);
          //  G4cout<<"photon"<<G4endl;
        }else{
            G4TrackingManager* trackingManager = G4EventManager::GetEventManager()->GetTrackingManager();
           trackingManager->SetStoreTrajectory(1);
            //G4cout<<"No photon"<<G4endl;
            //fpTrackingManager->SetStoreTrajectory(1);
        
    
        
        
        

}
}

