#include <iostream>
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4MTRunManager.hh"
#include "G4UIExecutive.hh"
#include "construction.hh"
#include "physics.hh"
#include "action.hh"
#include "G4RunManagerFactory.hh"

int main(int argc,char** argv){
    G4UIExecutive *ui=nullptr;
    
    #ifdef G4MULTITHREADED
        G4MTRunManager *runManager=new G4MTRunManager();
    #else
        G4RunManager *runManager=new G4RunManager();
    #endif
    
    
    //G4RunManager *runManager=new G4RunManager();
    //G4ScoringManager::GetScoringManager();
   
    runManager->SetUserInitialization(new MyDetectorConstruction());
    runManager->SetUserInitialization(new MyPhysicsList());
    runManager->SetUserInitialization(new MyActionInitialization());
    //runManager->Initialize();
   
    if(argc==1){
        ui = new G4UIExecutive(argc,argv);
        
    }
    

    G4VisManager *visManager = new G4VisExecutive();
    visManager->Initialize();
    G4UImanager *UImanager = G4UImanager::GetUIpointer();
    if(ui){
    UImanager->ApplyCommand("/control/execute vis.mac");
    ui->SessionStart();
    }else{
        G4String command="/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command+fileName);
        delete ui;
    }

    //delete ui;
    delete visManager;
    delete runManager;
    return 0;
}