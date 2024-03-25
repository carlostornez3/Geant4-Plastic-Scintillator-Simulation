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
#include "G4UIcommand.hh"
#include "G4RunManagerFactory.hh"
#include "G4String.hh"
#include "QGSP_BERT.hh"
#include "G4DecayPhysics.hh"
#include "G4VModularPhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4OpticalPhysics.hh"
//#include "G4Random.hh"
#include <ctime>



int main(int argc,char** argv){

    G4long seed = static_cast<G4long>(time(0));

    // Establecer la semilla aleatoria
    G4Random::setTheSeed(seed);
    G4cout<<"The seed is: "<< seed<<G4endl;
    G4UIExecutive *ui=nullptr;
    
    #ifdef G4MULTITHREADED
        G4MTRunManager *runManager=new G4MTRunManager();
    #else
        G4RunManager *runManager=new G4RunManager();
    #endif
    MyDetectorConstruction scintillatorProperties;
    if(G4String(argv[1])=="SC"){
        G4int thickness = G4UIcommand::ConvertToInt(argv[4]);
        scintillatorProperties.ScintillatorProperties(argv[2],argv[3],thickness,argv[5],argv[1]); 
    
        runManager->SetUserInitialization(new MyDetectorConstruction());
        G4cout<<MyDetectorConstruction::scintillatorGeometry<<MyDetectorConstruction::scintillatorType<<MyDetectorConstruction::scintillatorThickness<<MyDetectorConstruction::scintillatorNumberOfSensors<<MyDetectorConstruction::scintillatorArrangement<<G4endl;
        runManager->SetUserInitialization(new MyPhysicsList());
        runManager->SetUserInitialization(new MyActionInitialization());
        G4VModularPhysicsList * physics = new QGSP_BERT();
        //physics->RegisterPhysics(new G4DecayPhysics());
        //physics->RegisterPhysics(new G4EmStandardPhysics());
        physics->RegisterPhysics(new G4OpticalPhysics());
        runManager->SetUserInitialization(physics);
    
        if(argc==6){
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
            G4String fileName = argv[6];
            UImanager->ApplyCommand(command+fileName);
            delete ui;
        }


        delete visManager;
    }else if(G4String(argv[1])=="SCBT" || G4String(argv[1])=="RPCBT"){
        G4int particleEnergy = G4UIcommand::ConvertToInt(argv[4]);
        G4int numberOfParticles = G4UIcommand::ConvertToInt(argv[3]);
        scintillatorProperties.BeamTestConfiguration(argv[1],argv[2],argv[3],argv[4],argv[5]); 
        
        runManager->SetUserInitialization(new MyDetectorConstruction());
        G4cout<<MyDetectorConstruction::scintillatorArrangement<<MyDetectorConstruction::ParticleName<<MyDetectorConstruction::NumberOfParticles<<MyDetectorConstruction::ParticleEnergy<<MyDetectorConstruction::NumberOfEvents<<G4endl;
        runManager->SetUserInitialization(new MyPhysicsList());
        runManager->SetUserInitialization(new MyActionInitialization());
        G4VModularPhysicsList * physics = new QGSP_BERT();
        
        physics->RegisterPhysics(new G4OpticalPhysics());
        runManager->SetUserInitialization(physics);
    
        if(argc==6){
            ui = new G4UIExecutive(argc,argv);
            
        }
        

        G4VisManager *visManager = new G4VisExecutive();
        visManager->Initialize();
        G4UImanager *UImanager = G4UImanager::GetUIpointer();
        if(ui){
        UImanager->ApplyCommand("/control/execute vis.mac");
        UImanager->ApplyCommand("/control/execute gps.mac");
        ui->SessionStart();
        delete ui;
        }else{
            G4String command="/control/execute ";
            G4String fileName = argv[6];
            UImanager->ApplyCommand(command+fileName);

            command = "/gps/particle ";
            G4String particleName = argv[2];
            UImanager->ApplyCommand(command+particleName);

            command = "/gps/ene/mono ";
            G4String energy = argv[4];
            UImanager->ApplyCommand(command+energy+ " GeV");
            
            command = "/gps/number ";
            G4String particleNumber = argv[3];
            UImanager->ApplyCommand(command+particleNumber);

            command = "/run/beamOn ";
            G4String numberOfEvents = argv[5];
            UImanager->ApplyCommand(command+numberOfEvents);
          //  delete ui;
        }
        delete visManager;


    }

    
    
   
    //delete ui;
    
    delete runManager;
    return 0;
}