---
icon: hand-wave
cover: .gitbook/assets/IMG_0309.jpeg
coverY: 0
---

# Getting started

Welcome! This page is meant as an intro to the LFHCal TB analysis software , which can be found here: [https://github.com/eic/epic-lfhcal-tbana](https://github.com/eic/epic-lfhcal-tbana)

{% hint style="info" %}
**DISCLAIMER: Any plots shown in this tutorial should not be shown at conferences without prior approval by the ePIC LFHCal DSC. They are purely meant as illustrations what the software can do in its current state.**
{% endhint %}

In order to get started make sure you download the software:&#x20;

```sh
git clone git@github.com:eic/epic-lfhcal-tbana.git $WHATEVERYOURDIRNAMESHOULDBE
# enter corresponding directory
cd $WHATEVERYOURDIRENAMESHOULDBE
git submodule update --init --recursive
# please check enter the NewStructure/h2g_decode which version of the code is check out
git status
## Out put should be: 
On branch v0.13
Your branch is up to date with 'origin/v0.13'.
# check in addition which was the last commit
git log
# output should be at the top:
commit 20bc388794e0157c6efb66fe93745627ad90d546 
# If this isn't the case please do the following:
git checkout v0.13
git pull --rebase
```

have a working developer version of root and can actually compile the software. The repository contains 2 major version of the analysis code:

* OldStructure (used prior to the Aug. 2024 TB)
* NewStructure (used since Aug. 2024)

A basis intro can description is also given in the README in the main directory of the software. We only left the older part of the software as inspiration for some future parts of the code. Any further development should be done in "NewStructure". So in order to see whether everything works in principle. Open a shell in the main checkout of the git-repo, make sure you have access to root and do

```sh
cd NewStructure
cmake .
make
```

This should compile all necessary executables for the calibrations and initial data analysis. You can test the compilation as follows&#x20;

```sh
./Convert -h
```

This should give you all the options the program Convert can handle. If that worked , you'll need some data! If not something went wrong with your compilation. Please make sure you also always are on the latest version of main software packages and the submodules packages by:

```sh
git pull --rebase
git pull --recurse-submodules
```

In case you make any major changes to the basis classes remember to do&#x20;

```sh
make clean
make 
```

Otherwise you might be building against an outdated class by accident. In case you pulled changes from the git repository, always make yourself familiar with the new options first using:

```sh
./Convert -h
Usage:
./Convert [-option (arguments)]
Options:
-a       printing calib object to file (using name of output root or calib root file ending in txt)
-c xxx   Convert ASCII input file xxx into root format output
-d [0-n] switch on debug info with debug level 0 to n
-f       Force to write output if already exist
-i uuu   Input file in root format
-m www   Name of mapping file  2024 PS TB [../configs/mappingFile_202409_CAEN.txt] 
-o vvv   Output file name (mandatory)
-O kkk   Output directory name for plots (mandatory)
-r rrr   Name of run list file  2024 PS TB [../configs/DataTakingDB_202409_CAEN.csv] 
-y yyyy  setting year externally to narrow parameters
-h       this help

Examples:
./Convert -c (-f) input.txt -o output.root (Convert ASCII to root) (-f to overwrite existing output)


./DataPrep -h
Usage:
./DataPrep [-option (arguments)]
Options:
-a       printing calib object to file (using name of output root or calib root file ending in txt)
-A aaa   stripping only calib and setup object to external file
-b       calculate bad channel map internally
-B lll   apply external bad channel map during transfer of calibs
-C yyy   Apply calibrations stored in yyy root file to the input uncalibrated file
-d [0-n] switch on debug info with debug level 0 to n
-e       extended plotting = 1
-E       extended plotting = 2
-f       Force to write output if already exist
-F fff   set explicit plot extension explicitly, default is pdf 
-i uuu   Input file in root format
-k kkk   enabling overwriting of calib file using external calib txt file
-L LLL   enable testing with only limited number of events
-m www   Name of mapping file  2024 PS TB [../configs/mappingFile_202409_CAEN.txt] 
-M       save mip triggered cells only
-n       extract noise after first mip fits and reevaluate pedestals
-N       save noise triggered cells only
-o vvv   Output file name (mandatory)
-O kkk   Output directory name for plots (mandatory)
-p       Extract pedestal from input file and store it in output file
-P zzz   Correct pedestals stored in zzz root file and applied to input file
-r rrr   Name of run list file  2024 PS TB [../configs/DataTakingDB_202409_CAEN.csv] 
-s       extract scaling constant from input data
-S       extract scaling constant from input data in 2nd iteration based on pretriggered data
-t       use local trigger eval from existing input, don't redo in calibrate
-T ttt   evaluate local triggers before calibrating, use external calib file ttt
-y yyyy  setting year externally to narrow parameters
-h       this help

Examples:
./DataPrep -p (-f) -o OutputWithExtractedPedestal.root -i input.root (-f to overwrite existing output)
./DataPrep -s (-f) -o OutputWithMIPscaling.root -i input.root (-f to overwrite existing output)
./DataPrep -S (-f) -o OutputWithMIPscaling.root -i input.root (-f to overwrite existing output)
./DataPrep -s (-f) -o OutputWithMIPscaling.root -P PedestalInput.root -i RawInput.root (-f to overwrite existing output)
./DataPrep -C Calibration.root (-f) -o CalibratedOutput.root -i Input.root (-f to overwrite existing output)


./DataAna -h
Usage:
./DataAna [-option (arguments)]
Options:
-a       printing calib object to file (using name of output root or calib root file ending in txt)
-d [0-n] switch on debug info with debug level 0 to n
-f       Force to write output if already exist
-i uuu   Input file in root format
-o vvv   Output file name 
-O kkk   Output Histos saved in
-P zzz   Plots directory path
-Q       Run basic QA routine
-r rrr   Name of run list file  2024 PS TB [../configs/DataTakingDB_202409_CAEN.csv] 
-y yyyy  setting year externally to narrow parameters
Examples:
./DataAna -Q (-f) -P plotDir/ -O OutputHist.root -i input.root (-f to overwrite existing output)

```

All provided shell scripts are designed such that they work with the executable compiled in the NewStructure-folder. If you prefer to have them separate that is possible too. Just be aware that you'll need to write your own shell scripts in that case.

```sh
#optional compilation in "build"-directory
cmake -B build .
cd build
make
# executables can in this case be executed from the NewStructure-directory i.e. like
build/Convert -h 

```

An overview of the data sets we collected in August 2024 can be found here [https://wiki.bnl.gov/EPIC/index.php?title=LFHCal\_Fall\_2024\_Test\_Beam](https://wiki.bnl.gov/EPIC/index.php?title=LFHCal_Fall_2024_Test_Beam)

If you don't know where raw files for the data are contact Friederike Bock (fbock@cern.ch) and she'll let you know how to get access.&#x20;

As you might be analyzing quite a lot of runs and doing things in parallel for instance on the same data set but with different settings it might be worth separating the directory in which you have the checked out version of the software and where you are compiling/running & storing things.&#x20;

To do so we prepared a small script which can create soft-links to your original software directory (allowing you to have the same software version w/o multiple copies). This script is called `$prepareAnalysisDirectory.sh` and can be executed as follows on any unix system:

```sh
bash $PATHTOSCRIPT/prepareAnalysisDirectory.sh $USERNAME [new/old]
```

Execute it in the directory where you would like to work after having added your user name and path to the software repo. The software compilation would still need to happen in the original checked out directory.&#x20;
