# Initial software for 2023 analysis

This part of the software was initially used for the analysis of the test beam from 2023. The main root macro for the test beam analysis can is

```c+
OldStructure/makeSimplePlotsFromJanusTree.C
```

How to start it can be found in `runJanusExtraction.sh`, which serves as primary steering script for the data analysis. It also contains several examples on how to compare the output of different runs included in:

```c+
OldStructure/CompareDifferentRuns.C
```

With this code also the single photon extraction can be done, this is steered by `runSinglePhotonExtraction.sh` for which the main root macro is

```c+
OldStructure/makeSinglePhotonSpectraFitsFromJanusTree.C
```

The comparisons for the single photon spectra are steered by `runCompareRunsForSinglePhotons.sh` which have as main root macro:

```c+
OldStructure/CompareDifferentRunsForSinglePhotonSpectra.C.C
```
