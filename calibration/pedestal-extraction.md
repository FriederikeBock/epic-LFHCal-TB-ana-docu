---
cover: ../.gitbook/assets/LG_Noise.png
coverY: -137.21066666666667
---

# Pedestal extraction

Any test beam analysis starts with the understanding of the data and possible shifts observed in the baseline. A pedestal is commonly referred to as a minimum setable value above which the actual signal is extracted. However, as all electronics also have electrical noise this value can fluctuate slightly for each event around the set value.&#x20;

It is of key importance to understand what is the pedestal mean and width (tells us something about the noise levels) for your data.&#x20;

## CAEN data

For the data taken with the CAEN DT5202 during the test beam campaings in 2023 & 2024 the intended pedestal value should have been 50 ADC for both HG and LG for each channel. However, as the read-out electronics isn't ideal and we were running often with multiple CAEN DT5202 units the channel-by-channel observed values often aren't at 50 ADC. Thus for the October 2023 & August 2024 dedicated pedestal runs have been taken, which were internally triggered by the DT5202 with random triggers. Based on these data the corresponding pedestal means and width for each channel and HV setting can be extracted. Ideally these should stay stable if no major changes in the cabling and/or settings have been done.

### Extraction of Pedestal for a single run

The extraction of the pedestals for a single run can be started as follow:

```sh
./DataPrep -f -d 1 -p -i raw_$RUNNR.root -o PedestalCalib_$RUNNR.root -O $PLOTDIRECTORY -r $RUNLISTFILE
```

The option `-p` is the key to trigger the extraction of the Pedestals based on the raw-file (`raw_$RUNNR.root`), defined by `-i raw_$RUNNR.root`. The destination of the root output is defined by `-o PedestalCalib_$RUNNR.root` and Plots will be created in `$PLOTDIRECTORY`, as given by `-O`.  In order to have the plots correctly labeled the run list needs to be given with `-r`, as for the conversion of the data and `-f` and `-d` are used in the same manner as for `./Convert`. In addition to the output as defined by `-o`, a file with histograms will be stored for later use, the file name is the as for the `-o` option replacing replacing `".root"` with `"_hists.root".`

During this process the original data will be copied to the new file and the existing (empty) calibration objects contained in $raw\_$RUNNR.root will be expanded for each tile/cell to contain the respective pedestal position and width for HG and LG. All other values of the calibration will be initiated with their respetive default values. More details on the actual calib- object structure and various access functions can be found in [Calib.h](https://github.com/eic/epic-lfhcal-tbana/blob/main/NewStructure/Calib.h). Below you can find the default values for a single TileCalib-object.&#x20;

```cpp
TileCalib{
  double PedestalMeanH  = -1000.;     // pedestal mean HG ADC (CAEN) or first sample ADC (HGCROC)
  double PedestalMeanL  = -1000.;     // pedestal mean LG ADC (CAEN) or average pedestal ADC (HGCROC)
  double PedestalSigH   = -1000.;     // width of pedest HG ADC (CAEN) or width of first sample ADC distribution (HGCROC)
  double PedestalSigL   = -1000.;     // width of pedest LG ADC (CAEN) or width of average pedestal ADC distribution (HGCROC)
  double ScaleH         = -1000.;     // Max Mip in HG ADC (CAEN) or ADC (HGCROC) 
  double ScaleWidthH    = -1000.;     // FWHM of Mip in HG ADC (CAEN) or ADC (HGCROC) 
  double ScaleL         = -1000.;     // Max Mip in LG ADC (CAEN) 
  double ScaleWidthL    = -1000.;     // FWHM Mip in LG ADC (CAEN) 
  double LGHGCorr       = -64;        // slope of correlation between LG (x axis) & HG (y axis) for CAEN data 
  double LGHGCorrOff    = -1000.;     // intercept of correlation between LG (x axis) & HG (y axis) for CAEN data 
  double HGLGCorr       = -64;        // slope of correlation between HG (x axis) & LG (y axis) for CAEN data
  double HGLGCorrOff    = -1000.;     // intercept of correlation between HG (x axis) & LG (y axis) for CAEN data
  short BadChannel      = -64;        // bad channel flag: 0 - off, 1 - bad, 2 - funky, 3 - good
} ;
```

The executable will produce a variety of control plots for each cell and overview plots for the full ensemble of cells in order to monitor the correct execution of the program. Make sure you actually check those! A few example plots are given below.

<figure><img src="../.gitbook/assets/HG_Noise.png" alt=""><figcaption><p>Raw HG  ADCs for each cell. </p></figcaption></figure>

<figure><img src="../.gitbook/assets/LG_Noise.png" alt=""><figcaption><p>Raw LG ADCs for each cell.</p></figcaption></figure>

Above you find the HG or LG ADCs for each tile/cell as function of the cell ID. They are displayed in the region where the pedestal would be expected (0 < ADC < 300). For this particular run a full 8M LFHCal module with 64 layers was read out by 8 CAEN units. In principle the pedestal offset for all of these had been set to ADC = 50. However, it can be seen that for some of the read-out units a significantly different offset seems to have been applied. The individual spectra for each cell are plotted in overview plots per layer together with the corresponding Gaussian fits to assess the pedestal mean and  width.&#x20;

<figure><img src="../.gitbook/assets/Noise_HG_Layer15.png" alt=""><figcaption><p>Single Tile HG spectra for Layer 15 together with the respective Pedestal fit. The mean and sigma for each tile are indicated in the legend of each panel. If no fit is drawn the corresponding fitting routine failed.</p></figcaption></figure>



<figure><img src="../.gitbook/assets/Noise_LG_Layer15.png" alt=""><figcaption><p>Single Tile LG spectra for Layer 15 together with the respective Pedestal fit. The mean and sigma for each tile are indicated in the legend of each panel. If no fit is drawn the corresponding fitting routine failed.</p></figcaption></figure>

Overview plots displaying the fitted values in a 2 dimensional version as function of the layer and the respective channel within the layer are also produced.&#x20;

<figure><img src="../.gitbook/assets/HG_NoiseMean (2).png" alt=""><figcaption><p>HG pedestal mean for each layer and channel on the board. The brd channels 0-3 reflect the lower row of the assembly, while 4-7 reflect the upper row of each assembly.</p></figcaption></figure>

<figure><img src="../.gitbook/assets/HG_NoiseSigma (2).png" alt=""><figcaption><p>HG pedestal width for each layer and channel on the board. The brd channels 0-3 reflect the lower row of the assembly, while 4-7 reflect the upper row of each assembly.</p></figcaption></figure>

<figure><img src="../.gitbook/assets/LG_NoiseMean (2).png" alt=""><figcaption><p>LG pedestal mean for each layer and channel on the board. The brd channels 0-3 reflect the lower row of the assembly, while 4-7 reflect the upper row of each assembly.</p></figcaption></figure>

<figure><img src="../.gitbook/assets/LG_NoiseSigma (2).png" alt=""><figcaption><p>LG pedestal width for each layer and channel on the board. The brd channels 0-3 reflect the lower row of the assembly, while 4-7 reflect the upper row of each assembly.</p></figcaption></figure>

By default all plots will be generated as pdf files, allowing you to merge pdfs into one single pdf by running:

```sh
 pdfunite *.pdf summary.pdf
```

in the respective plots folder. Alternatively the output format can be changed using the option:`-F png`  added to the original call of the executable. Most common graphics formats are available as outputs within root i.e. `png, pdf, eps, jpg`.

Before continuing with the analysis make sure your pedestals are well fitted and correctly describe the data. If for whatever reason the fits aren't working please have a look at&#x20;

`bool Analyses::GetPedestal(void)` in [Analyses.cc](https://github.com/eic/epic-lfhcal-tbana/blob/main/NewStructure/Analyses.cc) and&#x20;

`bool TileSpectra::FitNoise(double*, int, bool )` in [TileSpecta.cc](https://github.com/eic/epic-lfhcal-tbana/blob/main/NewStructure/TileSpectra.cc)

which are implementing the processing of the pedestals and the fitting respectively.&#x20;

For some of the data no proper pedestal runs have been taken and consequently the pedestal extraction isn't this trivial for those cases the pedestal can be extracted first on the muon/hadron sample and then after a first pass of the mip extraction a dedicated local noise triggered sample can be generated and refitted. Below you find an example for the 2023 September campaign, where this was the case. The key option here is `-n`, however prior to running this a first attempt to extract the mip values needs to be done and stored in `rawPedAndMuon_$RUNNR.root`.&#x20;

```sh
./DataPrep -f -d 1 -y 2023 -n -i rawPedAndMuon_$RUNNR.root -o rawPedAndMuonNoise_$RUNNR.root -O $PLOTOUTPUT -r $RUNLISTSEPT2023
```

For the local noise trigger `n` cells before and after the current cell are evaluated (same row and column, different layer) and their raw-initial pedestal corrected signals summed and averaged. If the resulting `TriggerPrimitive` is below `frac*avMIP,` the corresponding cell is flagged as noise triggered for this event. An example of this implementation can be found in:

`bool GetNoiseSampleAndRefitPedestal(void)`  in [Analyses.cc](https://github.com/eic/epic-lfhcal-tbana/blob/main/NewStructure/Analyses.cc) and&#x20;

`double CalculateLocalMuonTrigg(Calib, TRandom3*, int, int, double)` in [Event.cc](https://github.com/eic/epic-lfhcal-tbana/blob/main/NewStructure/Event.cc)

`bool InspectIfNoiseTrigg(int, double, double)` in [Event.cc](https://github.com/eic/epic-lfhcal-tbana/blob/main/NewStructure/Event.cc)

Skimming of just the cells containing noise obtained in this manner can be achieve by running with the `-N` option:

```sh
./DataPrep -f -d 1 -N -i rawPedAndMuonNoise_$RUNNR.root -o raw_pedonly_$RUNNR.root 
```

For some of the data set again scripts have been prepared to run them in an ordered fashion, if possible use those.

### September 2023 data

A basic calibration script has been prepared. Similar to the [Converter-scripts](../tb-analysis/converting-the-data.md#caen-data-conversion) please add your user name and respective data location respectively.

To extract a first pass of the pedestal run:

<pre class="language-sh"><code class="lang-sh"><strong>bash runCalibration_Sept2023.sh $USERNAME pedestal
</strong></code></pre>

Afterwards run the mip extraction as described in the next chapter and then:

<pre class="language-sh"><code class="lang-sh"><strong>bash runCalibration_Sept2023.sh $USERNAME pedestalRe
</strong></code></pre>

Feel free to comment in and out run numbers and partial data sets in these scripts as needed.

### October 2023 data

No script has been prepared yet.

### August 2024 data

The scripts for the 2024 data taking campaign are developed the furthest. In order to extract the pedestal run:

<pre class="language-sh"><code class="lang-sh"><strong>bash runCalibration_2024.sh $USERNAME pedestal
</strong></code></pre>

Feel free to comment in and out run numbers and partial data sets in these scripts as needed. The run numbers for the different campaings for the muon and pedestal runs for this data set are defined with

```bash
muonHVScan_42V='309'
pedHVScan_42V='308'

muonScanA_45V='244 250 282 283'
pedScanA_45V='271 277'
```

and similar variable for convenience.

## HGCROC data

The&#x20;
