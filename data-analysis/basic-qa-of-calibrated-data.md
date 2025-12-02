# Basic QA of calibrated data

## CAEN data

### Running over one single run&#x20;

The main-program to run a basic QA over the calbrated data is `./DataAna.` So far only one option is implemented `-Q`, which triggers a basic QA run over the data and can be run as follows.

```sh
./DataAna -d 1 -Q -i calibrated_Run_$RUNNR.root -O QAHists_Run_$RUNNR.root -a -f -r $RUNLIST -P $PLOTSDIR
```

It currently produces the following plots and can distinguish 3 different trigger classes (All, Muon triggered, Not Muon Triggered).

<div><figure><img src="../.gitbook/assets/EnergyVsCellID.png" alt=""><figcaption></figcaption></figure> <figure><img src="../.gitbook/assets/HG.png" alt=""><figcaption></figcaption></figure> <figure><img src="../.gitbook/assets/HGCorr.png" alt=""><figcaption></figcaption></figure> <figure><img src="../.gitbook/assets/LG.png" alt=""><figcaption></figcaption></figure> <figure><img src="../.gitbook/assets/LGCorr.png" alt=""><figcaption></figcaption></figure></div>

<div><figure><img src="../.gitbook/assets/EnergyTotalVsNCells.png" alt=""><figcaption></figcaption></figure> <figure><img src="../.gitbook/assets/EnergyTotalVsNCells_MuonTrigg.png" alt=""><figcaption></figcaption></figure> <figure><img src="../.gitbook/assets/EnergyTotalVsNCells_WoMuonTrigg.png" alt=""><figcaption></figcaption></figure></div>

<div><figure><img src="../.gitbook/assets/EnergyTot.png" alt=""><figcaption></figcaption></figure> <figure><img src="../.gitbook/assets/EnergyTotSplit.png" alt=""><figcaption></figcaption></figure> <figure><img src="../.gitbook/assets/NCells.png" alt=""><figcaption></figcaption></figure> <figure><img src="../.gitbook/assets/NCellsSplit.png" alt=""><figcaption></figcaption></figure></div>

<div><figure><img src="/broken/files/EKsBbs7UEUgxZ7nIQJzd" alt=""><figcaption></figcaption></figure> <figure><img src="/broken/files/YYPT5okXGguInaivR7vk" alt=""><figcaption></figcaption></figure> <figure><img src="/broken/files/01Ltyhb8EeV50usMqAOT" alt=""><figcaption></figcaption></figure></div>

<div><figure><img src="../.gitbook/assets/ELayerOverlay_AllTrigg.png" alt=""><figcaption></figcaption></figure> <figure><img src="../.gitbook/assets/ELayerOverlay_MuonTrigg.png" alt=""><figcaption></figcaption></figure> <figure><img src="../.gitbook/assets/ELayerOverlay_NonMuonTrigg.png" alt=""><figcaption></figcaption></figure></div>

<div><figure><img src="/broken/files/D74E3DRFZHwo8gNdv8AM" alt=""><figcaption></figcaption></figure> <figure><img src="/broken/files/obk6sYTd3LpR7HrJt8eC" alt=""><figcaption></figcaption></figure> <figure><img src="/broken/files/XT1V1N4jaXAhAWOclwXJ" alt=""><figcaption></figcaption></figure></div>

<div><figure><img src="../.gitbook/assets/NCellsLayerOverlay_AllTrigg.png" alt=""><figcaption></figcaption></figure> <figure><img src="../.gitbook/assets/NCellsLayerOverlay_MuonTrigg.png" alt=""><figcaption></figcaption></figure> <figure><img src="../.gitbook/assets/NCellsLayerOverlay_NonMuonTrigg.png" alt=""><figcaption></figcaption></figure></div>

<div><figure><img src="../.gitbook/assets/XPosVsLayer.png" alt=""><figcaption></figcaption></figure> <figure><img src="../.gitbook/assets/XPosVsLayer_MuonTrigg.png" alt=""><figcaption></figcaption></figure> <figure><img src="../.gitbook/assets/XPosVsLayer_WOMuonTrigg.png" alt=""><figcaption></figcaption></figure></div>

<div><figure><img src="../.gitbook/assets/XPosLayerOverlay_AllTrigg.png" alt=""><figcaption></figcaption></figure> <figure><img src="../.gitbook/assets/XPosLayerOverlay_MuonTrigg.png" alt=""><figcaption></figcaption></figure> <figure><img src="../.gitbook/assets/XPosLayerOverlay_NonMuonTrigg.png" alt=""><figcaption></figcaption></figure></div>

<div><figure><img src="../.gitbook/assets/YPosVsLayer.png" alt=""><figcaption></figcaption></figure> <figure><img src="../.gitbook/assets/YPosVsLayer_MuonTrigg.png" alt=""><figcaption></figcaption></figure> <figure><img src="../.gitbook/assets/YPosVsLayer_WOMuonTrigg.png" alt=""><figcaption></figcaption></figure></div>

<div><figure><img src="../.gitbook/assets/YPosLayerOverlay_AllTrigg.png" alt=""><figcaption></figcaption></figure> <figure><img src="../.gitbook/assets/YPosLayerOverlay_MuonTrigg.png" alt=""><figcaption></figcaption></figure> <figure><img src="../.gitbook/assets/YPosLayerOverlay_NonMuonTrigg.png" alt=""><figcaption></figcaption></figure></div>

Additional per layer plots are produced when running with the `-e [1/2]` option.

### September 2023 data

No scripts have been created yet.



### October 2023 data

No scripts have been created yet.



### August 2024 data

The primary script for the first look at a basic QA of calibrated data is `runQA_2024.sh`.&#x20;

```sh
# run first full data QA for Scan A
bash runQA_2024.sh $USERNAME ScanA
```

The 2nd argument defines which scan it is, please check which are currently available and expand where necessary.
