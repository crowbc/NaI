# NaI
Notes on NaI simulation:

Sodium iodide detector simulation for Geant4 v 11.1(beta)

Current build will generate energy spectrum from depositions in scoring volume.

Current build will simulate scintillation photons, but number of hits in sensitive volume has not yet been validated.

# Simulation Output
Simulation output stored in NaIoutput<RunNumber>_t<threadNumber>.root (output file name is hard coded.)

Thread outputs can be merged by typing:

hadd nameOfMergedFile.root NaIoutput<RunNumber>_t{0..n}.root, where n one less than the number of threads used to run the batch (max thread index)

for merging all threads into a single Root file for a particular run number

hadd nameOfMergedFile.root NaIoutput*_t{0..n}.root

for merging all threads of all runs into a single Root file

# Running the simulation
To run simulations in batch mode, type the following command:

./NaI macroName.mac

To run with the visualizer, type:

./NaI
 (note - the default source of a geantino redefined as a Co-60 decay ion will be used, but no events will be generated)

