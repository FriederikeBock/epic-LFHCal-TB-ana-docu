# General Setup

The TB simulations will be full embedded into the ePIC simulation framework, this means in order to run them you need a setup with eic-shell. Here are a few links to resources, tutorials and starting points for the eic computing environment:

* [Getting started ePIC software](https://www.epic-eic.org/sc/getstarted.html)
* [HEP tutorials page](https://hsf-training.org/training-center/)
* [ePIC/EIC tutorials](https://www.epic-eic.org/sc/tutorials.html)
* [ePIC software FAQ](https://www.epic-eic.org/sc/faq.html)

ePIC is simulating the geometry and hit information using [dd4hep](https://dd4hep.web.cern.ch/dd4hep/reference/) as main wrapper for full fledged GEANT4 simulations. The corresponding geometry is implemented in our [epic-dd4hep ](https://github.com/eic/epic)repository. The electronics emulation, reconstruction and initial analysis are afterwards handled via [eicrecon](https://github.com/eic/EICrecon). These packages and their dependencies are all provided within the eic-shell environment ([how-to-install](https://eic.github.io/tutorial-setting-up-environment)). They are tagged on a regular basis and provide the basis for our simulations.&#x20;

Our current plan for the simulations of the various test beams is to first implement the full geometry which is exposed to the beam (actual detector + trigger setup + additional components if applicable) using epic-dd4hep and then afterwards process it with eicrecon to the level of reconstructed hits. These hits should then be stored in the same format as we are using to process our TB data, or at least something can be easily converted to such a format.&#x20;

## Compiling TB geometry

Our current test beam geometry isn't yet included in the main branch of the epic-dd4hep repository, as it isn't fully functional yet. However, a good starting point has been provided in a [draft PR](https://github.com/eic/epic/tree/pr/lfhcal_8m_module_only). This however means we can't just blindly run the central compiled epic software but need to compile our own repository.&#x20;

```bash
## clone epic-dd4-hep directory 
## -> recommendation: don't put it into the same folder as the eic shell lives
git clone git@github.com:eic/epic.git epic-dd4hep
cd epic-dd4hep
git fetch origin
git switch pr/lfhcal_8m_module_only
```

Basic steps after you installed eic-shell:

```bash
## go to your directory with the epic-singularity installations
## make sure your eic-shell is up to date, this might take a minute if you haven't updated recently
./eic-shell --upgrade
## enter EIC shell
./eic-shell
## this set the environment variables correctly for all packages
source /opt/detector/epic-main/bin/thisepic.sh
## now we need to go to our freshly checked out repo
cd $WHERE_EVER_YOUR_EPIC_DIR_IS/epic-dd4hep
## build commands
cmake -B build -S . -DCMAKE_INSTALL_PREFIX=install
cmake --build build -- install -j8
## reset environment variables to pick up this version of the epic
source install/bin/thisepic.sh
```

Now you should have working epic geom version with the basics of the TB geometry included. Once you implement more things you have to always recompile!
