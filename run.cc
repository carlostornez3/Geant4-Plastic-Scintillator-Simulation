#include "run.hh"
#include "construction.hh"
#include "G4UIcommand.hh"


 //Creation of histograms
 //#include "G4RootAnalysisManager.hh"
 G4int MyRunAction::noc;
G4int MyRunAction::noc2;

MyRunAction::MyRunAction(){
   G4AnalysisManager *man =G4AnalysisManager::Instance();

   if(MyDetectorConstruction::scintillatorArrangement=="SC"){
  
        man->CreateH1("fEdep","Energy Deposition by Muons",60,0.,12*MeV,"MeV");
        man->SetH1XAxisTitle(0,"Energy Deposition (MeV)");
        man->SetH1YAxisTitle(0,"Number of Muons");

        man->CreateH1("fWlength","Photon Wavelength",60,360*nm,525*nm,"nm");
        man->SetH1XAxisTitle(1,"Wavelength (nm)");
        man->SetH1YAxisTitle(1,"Number of Photons");
        
        man->CreateH1("fEvent","Amount of Photons produced per event",30,0,1000,"none");
        man->SetH1XAxisTitle(2,"Event");
        man->SetH1YAxisTitle(2,"Number of Photons");

        
        man->CreateH1("fEnergy","Photon Energy",80,2.*eV,4.*eV,"eV");
        man->SetH1XAxisTitle(3,"Energy (eV)");
        man->SetH1YAxisTitle(3,"Number of Photons");

        man->CreateH1("fEvent2","Amount of Photons produced per event",10,0,10,"none");
        man->SetH1XAxisTitle(4,"Event");
        man->SetH1YAxisTitle(4,"Number of Photons");

        man->CreateH1("fTime0","Time of flight Event 0",150,0.*ns,120.*ns,"ns");
        man->SetH1XAxisTitle(5,"Time of flight (ns)");
        man->SetH1YAxisTitle(5,"Number of Photons");

        man->CreateH1("fTime1","Time of flight Event 1",150,0.*ns,120.*ns,"ns");
        man->SetH1XAxisTitle(6,"Time of flight (ns)");
        man->SetH1YAxisTitle(6,"Number of Photons");
        
        man->CreateH1("fTime2","Time of flight Event 2",150,0.*ns,120.*ns,"ns");
        man->SetH1XAxisTitle(7,"Time of flight (ns)");
        man->SetH1YAxisTitle(7,"Number of Photons");

        man->CreateH1("fTime3","Time of flight Event 3",150,0.*ns,120.*ns,"ns");
        man->SetH1XAxisTitle(8,"Time of flight (ns)");
        man->SetH1YAxisTitle(8,"Number of Photons");

        man->CreateH1("fTime4","Time of flight Event 4",150,0.*ns,120.*ns,"ns");
        man->SetH1XAxisTitle(9,"Time of flight (ns)");
        man->SetH1YAxisTitle(9,"Number of Photons");

        man->CreateH1("fTime5","Time of flight Event 5",150,0.*ns,120.*ns,"ns");
        man->SetH1XAxisTitle(10,"Time of flight (ns)");
        man->SetH1YAxisTitle(10,"Number of Photons");

        man->CreateH1("fTime6","Time of flight Event 6",150,0.*ns,120.*ns,"ns");
        man->SetH1XAxisTitle(11,"Time of flight (ns)");
        man->SetH1YAxisTitle(11,"Number of Photons");

        man->CreateH1("fTime7","Time of flight Event 7",150,0.*ns,120.*ns,"ns");
        man->SetH1XAxisTitle(12,"Time of flight (ns)");
        man->SetH1YAxisTitle(12,"Number of Photons");

        man->CreateH1("fTime8","Time of flight Event 8",150,0.*ns,120.*ns,"ns");
        man->SetH1XAxisTitle(13,"Time of flight (ns)");
        man->SetH1YAxisTitle(13,"Number of Photons");

        man->CreateH1("fTime9","Time of flight Event 9",150,0.*ns,120.*ns,"ns");
        man->SetH1XAxisTitle(14,"Time of flight (ns)");
        man->SetH1YAxisTitle(14,"Number of Photons");
            
        man->CreateH1("fTime10","Time of flight ",150,0.*ns,100000*ns,"ns");
        man->SetH1XAxisTitle(15,"Time of flight (ns)");
        man->SetH1YAxisTitle(15,"Number of Photons");
        man->SetH1Activation(15, false);
            G4int lowLimit, highLimit,center;
            if(MyDetectorConstruction::scintillatorGeometry=="R"){
                if(MyDetectorConstruction::scintillatorType=="BC404"){
                    if(MyDetectorConstruction::scintillatorThickness==10){
                        center=9*ns;
                    }
                    else if(MyDetectorConstruction::scintillatorThickness==20){
                        center=10*ns;
                    }
                    else if(MyDetectorConstruction::scintillatorThickness==30){
                        center=10*ns;
                    }
                    else if(MyDetectorConstruction::scintillatorThickness==40){
                        center=10*ns;
                    }else{
                        center=0;
                    }
                }if(MyDetectorConstruction::scintillatorType=="EJ208"){
                    if(MyDetectorConstruction::scintillatorThickness==10){
                        center=19*ns;
                    }
                    else if(MyDetectorConstruction::scintillatorThickness==20){
                        center=20*ns;
                    }
                    else if(MyDetectorConstruction::scintillatorThickness==30){
                        center=21*ns;
                    }
                    else if(MyDetectorConstruction::scintillatorThickness==40){
                        center=22*ns;
                    }else{
                        center=0;
                    }
                }
                if(center!=0){
                lowLimit=center-3*ns;
                highLimit=center+3*ns;
                } else{
                lowLimit=0*ns;
                highLimit=100*ns;
                }
            }else{
                lowLimit=0*ns;
                highLimit=20*ns;
            }
            
        man->CreateH1("MTOF","Mean Time of flight",60,lowLimit,highLimit,"ns");
        man->SetH1XAxisTitle(16,"Time of flight (ns)");
        //man->SetH1YAxisTitle(16,"Number of Photons");

        man->CreateH1("fEvent4","Amount of Photons produced",1000,0,100000,"none");
        man->SetH1YAxisTitle(17,"Event");
        man->SetH1XAxisTitle(17,"Number of Photons");
        man->SetH1Activation(17, false);

        man->CreateH1("fEvent3","Amount of Photons produced",150,0,15000,"none");
        man->SetH1YAxisTitle(18,"Events");
        man->SetH1XAxisTitle(18,"Number of Photons");

         man->CreateH1("fEvent5","Amount of Photons produced",1000,0,100000,"none");
        man->SetH1YAxisTitle(19,"Event");
        man->SetH1XAxisTitle(19,"Number of Photons");
        ////man->SetH1Activation(19, false);


        man->CreateH2("fEnergy vs fWlength","Photon Energy vs Photon Wavelength",80,2.4*eV,3.5*eV,60,300*nm,520*nm,"eV","nm");
        //man->SetH2XAxisTitle(0,"Photon Energy (eV)");
        //man->SetH2YAxisTitle(0,"Photon Wavelength (nm)");
        //man->SetH2ZAxisTitle(0,"Number of Photons");
   } else if(MyDetectorConstruction::scintillatorArrangement=="SCBT"){
       /* noc=0;
        noc2=0;
        G4int fevents=100;
      

        histogramCreation("X1","BC",12.,fevents,0*ns,12*ns);  
        histogramCreation("Y1","BC",12.,fevents,0*ns,12*ns);
        histogramCreation("CZ","EJ208",12.,fevents,0*ns,12*ns);
        histogramCreation("S0","EJ208",12.,fevents,0*ns,12*ns);
        histogramCreation("S1","EJ208",12.,fevents,0*ns,12*ns);
        histogramCreation("S2","EJ208",12.,fevents,0*ns,12*ns);
        histogramCreation("BC","BC",12.,fevents,0*ns,12*ns);
        histogramCreation("ACORDE","EJ208",12.,fevents,0*ns,12*ns);
        histogramCreation("UNAM","EJ208",12.,fevents,0*ns,12*ns);
        histogramCreation("FERM","EJ208",12.,fevents,0*ns,12*ns);
        histogramCreation("X2","BC",12.,fevents,0*ns,12*ns);*/

        NtupleCreation("X1","0",0);
        NtupleCreation("X1","1",1);
        NtupleCreation("X1","2",2);

        NtupleCreation("Y1","0",3);
        NtupleCreation("Y1","1",4);
        NtupleCreation("Y1","2",5);

        NtupleCreation("CZ","0",6);
        NtupleCreation("CZ","1",7);
        NtupleCreation("CZ","2",8);

        NtupleCreation("S0","0",9);
        NtupleCreation("S0","1",10);
        NtupleCreation("S0","2",11);

        NtupleCreation("S1","0",12);
        NtupleCreation("S1","1",13);
        NtupleCreation("S1","2",14);

        NtupleCreation("S2","0",15);
        NtupleCreation("S2","1",16);
        NtupleCreation("S2","2",17);

        NtupleCreation("BC","0",18);
        NtupleCreation("BC","1",19);
        NtupleCreation("BC","2",20);

        NtupleCreation("ACORDE","0",21);
        NtupleCreation("ACORDE","1",22);
        NtupleCreation("ACORDE","2",23);

        NtupleCreation("UNAM","0",24);
        NtupleCreation("UNAM","1",25);
        NtupleCreation("UNAM","2",26);

        NtupleCreation("FERM","0",27);
        NtupleCreation("FERM","1",28);
        NtupleCreation("FERM","2",29);

        NtupleCreation("X2","0",30);
        NtupleCreation("X2","1",31);
        NtupleCreation("X2","2",32);



   }

}
MyRunAction::~MyRunAction(){

}
void MyRunAction::BeginOfRunAction(const G4Run * run){
    G4AnalysisManager *man =G4AnalysisManager::Instance();

    G4int runID = run->GetRunID();
    std::stringstream strRunID;
    strRunID<<runID;
   // G4String thickness = G4UIcommand::ConvertToString(MyDetectorConstruction::scintillatorThickness); strRunID.str()
    G4String file =MyDetectorConstruction::scintillatorGeometry+"_"+ MyDetectorConstruction::scintillatorType +"_" + G4UIcommand::ConvertToString(MyDetectorConstruction::scintillatorThickness) + "mm"+"_"+MyDetectorConstruction::scintillatorNumberOfSensors+"Sensors"  + ".root";
  
    man->OpenFile(file);


}
void MyRunAction::EndOfRunAction(const G4Run *){
    G4AnalysisManager *man =G4AnalysisManager::Instance();
    man->Write();
    man->CloseFile();
}

void MyRunAction::histogramCreation(G4String scintillatorName,G4String scintillatorType, G4double thickness, G4int numberOfEvents, G4double mtofLL, G4double mtofUL){
        G4AnalysisManager *man =G4AnalysisManager::Instance();
        treeName = "fEdep_"+ scintillatorName;
        
        histogramName = "Energy Deposition by Primary Particle_" + scintillatorName;
        man->CreateH1(treeName,histogramName,60,0.,12*MeV,"MeV");
        //man->SetH1XAxisTitle(noc,"Energy Deposition (MeV)");
        //man->SetH1YAxisTitle(noc,"Number of Muons");

        treeName = "fWlength_"+ scintillatorName;
        noc = noc+1;
        histogramName = "Photon Wavelength_" + scintillatorName;
        man->CreateH1(treeName,histogramName,60,360*nm,525*nm,"nm");
        //man->SetH1XAxisTitle(noc+1,"Wavelength (nm)");
        //man->SetH1YAxisTitle(noc+1,"Number of Photons");
        

        noc = noc+2;
        treeName = "fEvent_"+ scintillatorName;
        histogramName = "Amount of Photons produced per event_" + scintillatorName;
        man->CreateH1(treeName,histogramName,30,0,numberOfEvents,"none");
        //man->SetH1XAxisTitle(noc+2,"Event");
        //man->SetH1YAxisTitle(noc+2,"Number of Photons");

        noc = noc+3;
        treeName = "fEnergy_"+ scintillatorName;
        histogramName = "Photon Energy_" + scintillatorName;
        man->CreateH1(treeName,histogramName,80,2.*eV,4.*eV,"eV");
        //man->SetH1XAxisTitle(noc+3,"Energy (eV)");
        //man->SetH1YAxisTitle(noc+3,"Number of Photons");

        noc = noc+4;
        treeName = "fEvent2_"+ scintillatorName;
        histogramName = "Amount of Photons produced per event_" + scintillatorName;
        man->CreateH1(treeName,histogramName,10,0,10,"none");
        //man->SetH1XAxisTitle(noc+4,"Event");
        //man->SetH1YAxisTitle(noc+4,"Number of Photons");



        noc = noc+5;
        treeName = "ftime1_"+ scintillatorName;
        histogramName = "Time of flight random Event 1_" + scintillatorName;
        man->CreateH1(treeName,histogramName,150,0.*ns,120.*ns,"ns");
        //man->SetH1XAxisTitle(noc+5,"Time of flight (ns)");
        //man->SetH1YAxisTitle(noc+5,"Number of Photons");
    

        noc = noc+6;
        man->CreateH1("fTime10","Time of flight ",150,0.*ns,100000*ns,"ns");
        //man->SetH1XAxisTitle(noc+6,"Time of flight (ns)");
        ////man->SetH1YAxisTitle(noc+6,"Number of Photons");
        ////man->SetH1Activation(noc+6, false);



        noc = noc+7;
        treeName = "MTOF_"+ scintillatorName;
        histogramName = "Mean Time of Flight_" + scintillatorName;
        man->CreateH1(treeName,histogramName,120,mtofLL,mtofUL,"ns");
        ////man->SetH1XAxisTitle(noc+7,"Time of flight (ns)");
        ////man->SetH1YAxisTitle(noc+7,"Number of Photons");


        
        treeName = "fEvent4_"+ scintillatorName;
        histogramName = "_" + scintillatorName;
        man->CreateH1(treeName,histogramName,1000,0,10000000,"none");
        ////man->SetH1YAxisTitle(noc+8,"Event");
        ////man->SetH1XAxisTitle(noc+8,"Number of Photons");
        ////man->SetH1Activation(noc+8, false);
        
       
        treeName = "fPhoton_"+ scintillatorName;
        histogramName = "Amount of Photons produced_" + scintillatorName;
        man->CreateH1(treeName,histogramName,500,0,50000,"none");
        ////man->SetH1YAxisTitle(noc+9,"Events");
        ////man->SetH1XAxisTitle(noc+9,"Number of Photons");

        
        treeName = "EnergyNoise_"+ scintillatorName;
        histogramName = "Energy Deposition by Secondary Particles" + scintillatorName;
        man->CreateH1(treeName,histogramName,60,0.,12*MeV,"MeV");
        //man->SetH1XAxisTitle(noc+10,"Energy Deposition (MeV)");
        //man->SetH1YAxisTitle(noc+10,"Number of Muons");

        


        treeName = "fEnergy vs fWlength_"+ scintillatorName;
        histogramName = "Photon Energy vs Photon Wavelength_" + scintillatorName;
        man->CreateH2(treeName,histogramName,80,2.4*eV,3.5*eV,60,300*nm,520*nm,"eV","nm");
        ////man->SetH2XAxisTitle(noc2,"Photon Energy (eV)");
        ////man->SetH2YAxisTitle(noc2,"Photon Wavelength (nm)");
        ////man->SetH2ZAxisTitle(noc2,"Number of Photons");

        treeName = "XY_Position" + scintillatorName;
        histogramName = "XY Position of Impact by Secondary Particles";
        man->CreateH2(treeName,histogramName,100,-5.*cm,5*cm,1000,-75*cm,75*cm,"cm","cm");
        //noc2+2
       
       
       
        noc=noc+10;
        noc2++;
}

void MyRunAction::NtupleCreation(G4String scintillatorName,G4String category,G4int tupleNumber){
        G4AnalysisManager *man =G4AnalysisManager::Instance();
       
        
        G4String NtupleName = scintillatorName + "_" + category;
        man->CreateNtuple(NtupleName,NtupleName);

        if(category == "0"){

            man->CreateNtupleIColumn("fEvent"); //foton
            man->CreateNtupleDColumn("Wlength"); //foton
            man->CreateNtupleDColumn("PhotonEnergy"); //foton
            
        }
        else if(category == "1"){
            man->CreateNtupleDColumn("Energy Deposition by Primary Particle");   //final del evento
            man->CreateNtupleDColumn("MTOF"); //final del evento
            man->CreateNtupleDColumn("fPhoton"); //final del evento
            man->CreateNtupleDColumn("Energy Deposition Noise"); //final del evento
        }
        else if(category == "2"){
            man->CreateNtupleDColumn("fXNoise"); // ruido
            man->CreateNtupleDColumn("fYNoise"); //ruido
            man->CreateNtupleDColumn("fZNoise"); //ruido


        }
        
        man->FinishNtuple(tupleNumber);

        G4String name = scintillatorName + "TOFEvt0";
        man->CreateH1(name, "Time of Flight Event0",150,0.*ns,120.*ns,"ns"); //foton
        name = scintillatorName + "_tof";
        man->CreateH1(name,"Time of flight ",150,0.*ns,1000000000*ns,"ns");
        name = scintillatorName +"_fParticles";
        man->CreateH1(name,"particles",1000,0,10000000000,"none");
        
        
       
        

        
        

        


        

        
       
       
       
        
}

