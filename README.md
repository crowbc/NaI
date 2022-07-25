# NaI

Notes on NaI simulation

Sodium iodide detector simulation for Geant4 v 11.1(beta)

Current build will generate energy spectrum from depositions in scoring volume
Current build will simulate scintillation photons, but will not score number of hits in sensitive volume
Simulation output stored in NaIoutput<RunNumber>_t<threadNumber>.root

Thread outputs can be merged by typing:
for merging all threads into a single Root file for one run number:
hadd nameOfMergedFile.root NaIoutput<RunNumber>_t*.root
for merging all threads of all runs into a single Root file:
hadd nameOfMergedFile.root NaIoutput*_t*.root

To run simulations in batch mode, type the following command:
./NaI macroName.mac

To run with the visualizer, type:
./NaI
 (note - the default source of a geantino redefined as a Co-60 decay ion will be used, but no events will be generated)

