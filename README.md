# Geant4-Plastic-Scintillator-Simulation


This project simulates a Plastic Scintillator and computes the total energy deposition by muons. It also creates a root file with information about 
the photons generated via scintillation and the energy deposition.

The program uses the method GetTotalEnergyDeposit() to calculate the energy deposition by muons. 

To run the program:
cd Geant4-Plastic-Scintillator-Simulation
mkdir build
cd build
cmake ..
make 

The program allows to choose between two geometries and two scintillator types: Hexagonal(H) or Rectangular(R) and BC404 or EJ208. It also allows you to choose the thickness (it must be specified in mm)
To execute:
./sim <Geometry> <type> <thickness>
Example:
./sim R BC4O4 20 run.mac

The last parameter is optional and it will execute the batch mode. 

If you are using multithreaded mode, modify the "run.mac" file, there, you can change the number of threads your computer can use and also the number of 
events geant4 will simulate(1 muon per event).Beware that visualization is only available if you are not using multithreaded.
