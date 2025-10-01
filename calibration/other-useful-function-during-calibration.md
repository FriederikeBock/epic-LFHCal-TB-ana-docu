# Other useful function during calibration

## Skimming local muon triggers only

```sh
./DataPrep -f -d 1 -M -i rawPedAndMuon_$RUNNR.root -o raw_muononly_$RUNNR.root 
```

## Skimming local noise triggers only

```sh
./DataPrep -f -d 1 -N -i rawPedAndMuonNoise_$RUNNR.root -o raw_pedonly_$RUNNR.root 
```

## Restricting the number of events to be analyzed

For some functions of `./DataPrep` an option to limit the running only over a fraction of the events is implemented use `-L $NEVTSANA` if need be.

&#x20;
