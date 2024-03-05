#include "action.hh"

MyActionInitialization::MyActionInitialization(){

}
MyActionInitialization::~MyActionInitialization(){

}
void MyActionInitialization::BuildForMaster() const {
    MyRunAction *runAction= new MyRunAction();
    SetUserAction(runAction);
    
}
void MyActionInitialization::Build() const 
{
    //User-defined action classes declarated acording to geant4 sintaxis
    MyPrimaryGenerator *generator = new MyPrimaryGenerator();
    SetUserAction(generator);
    MyRunAction *runAction= new MyRunAction();
    SetUserAction(runAction);
    MyEventAction *eventAction= new MyEventAction(runAction);
    SetUserAction(eventAction);

    MyTrackingAction *trackingAction = new MyTrackingAction();
    SetUserAction(trackingAction);

    MySteppingAction *steppingAction= new MySteppingAction(eventAction);
    SetUserAction(steppingAction);
    
    
}