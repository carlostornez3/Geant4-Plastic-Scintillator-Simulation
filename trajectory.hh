#ifndef TRAJECTORY_HH
#define TRAJECTORY_HH

#include "G4UserTrackingAction.hh"
#include "G4Track.hh"
#include "G4ParticleDefinition.hh"
#include "G4OpticalPhoton.hh"
#include "G4Trajectory.hh"
#include "event.hh"
#include "G4TrackingManager.hh"
class MyTrackingAction : public G4UserTrackingAction {
public:
    MyTrackingAction();
    virtual ~MyTrackingAction();
    virtual void PreUserTrackingAction(const G4Track* track);
  //  virtual void PostUserTrackingAction(const G4Track* track);
    

    G4TrackingManager* fpTrackingManager;
    
};


#endif