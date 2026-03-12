# Other useful functions during calibration

## Skimming local muon triggers only

```sh
./DataPrep -f -d 1 -M -i rawPedAndMuon_$RUNNR.root -o raw_muononly_$RUNNR.root 
```

## Skimming local noise triggers only

```sh
./DataPrep -f -d 1 -N -i rawPedAndMuonNoise_$RUNNR.root -o raw_pedonly_$RUNNR.root 
```

## Overwriting an existing setup tree

<mark style="background-color:red;">**This operation should only be done if a never version of the setup object needs to be written which contains the same information!**</mark> <mark style="background-color:red;"></mark><mark style="background-color:red;">This is an</mark> <mark style="background-color:red;"></mark><mark style="background-color:red;">**EXPERT OPERATION**</mark><mark style="background-color:red;">, please check with Friederike or Oskar whether this is the appropriate use case for your particular application.</mark>&#x20;

The following command would copy the calib & data tree and replace the setup tree according to the newly provided mapping file

```bash
// Example for rewriting raw file with new setup tree for 2025 TB 
./DataPrep -R ../configs/TB2025/mapping_HGCROC_PSTB2025_default_wSegments.txt -i 202511_PST09/HGCROCData/rawHGCROC_207.root -o 202511_PST09/HGCROCData/rawHGCROC_207_setupReplaced.root
```

## Restricting the number of events to be analyzed

For some functions of `./DataPrep` an option to limit the running only over a fraction of the events is implemented use `-L $NEVTSANA` if need be.

## Simple HGCROC waveform display

The HGCROC waveforms in our standard output per layer if at all are only displayed as a function of the sample number they have been taken with. However, for instance to further develop it can be very useful to have the waveforms as a function of time in addition.&#x20;

In order to that either you need calibrated output including the TOA phase corrections. You can run it on a single calibrated file as follows:

```bash
./DataPrep -d 1 -E 2 -f -w -i $CALIBRATEDFILE.root -o $OUTPUTFILENAME.root -O $PLOTDIRECTORY -r $RUNLIST 
```

The most of the options you should have seen before in other steps and they work in the same way. The key option triggering the waveform plotting is `-w`  which doesn't need any further argument. In this particular case no tree-output file will be generated and the histo output file will be named: `$OUTPUTFILENAME_hists.root`.&#x20;

Once more most of the histograming is handle by our [TileSpectra-class](https://github.com/eic/epic-lfhcal-tbana/blob/main/NewStructure/TileSpectra.h) generating all plots for all tiles for two different cases (a) all events/tiles & (b) "triggered" tiles, which in this case means for that specific tile and event a `TOA > 0` has to have been registered. The primary routine for this can be found in:

`bool Analyses::VisualizeWaveform(void)` in [Analyses.cc](https://github.com/eic/epic-lfhcal-tbana/blob/main/NewStructure/Analyses.cc).

