---
description: >-
  This page is intended to describe the basics of the data taking using the
  HGCROC and the respective online monitoring.
---

# Data Taking HGCROC

The data taking is steered by the `H2GDAQ` program ([link](setting-up-daq-pc.md)). It allows you to configure the data taking with multiple KCU's (FPGA's) and different number of HGCROCs (asics). It can be started by:

```shellscript
python3 H2GDAQ.py
```

Followed by the configurable selection of the respective values

<figure><img src="../.gitbook/assets/Screenshot from 2025-11-18 18-36-40 (1).png" alt=""><figcaption></figcaption></figure>

That is followed by the main window of the DAQ data taking.&#x20;

<figure><img src="../.gitbook/assets/Screenshot from 2026-03-31 16-37-42.png" alt=""><figcaption></figcaption></figure>

The top right corner `Working Folder`  shows you where the data will be written to, you can change that using the `"Select Folder"` button and even print the full directory location to the terminal from which you executed the script, using the `"Print to Terminal"` button.&#x20;

The online monitoring tool can be enabled by ticking the respective tick mark in the following section. Make sure it is pointing to the most recent version of the code and youhave compiled that using `make` in the respective directory.

The next section describes various DAQ settings to choose when a run should end:&#x20;

* at a fixed event number (this counter might be buggy if more than one KCU is connected)
* after a fixed time
* manually

Its followed by the section to `Stop` and `Start` the DAQ and a `"Lock"`  should you desire to operate it with the RCDAQ system and would like to prevent accidental operations.

In the middle column the generator as well as eternal trigger settings are defined please make sure the values for the Data Collection, Generator and Fast Commands & Machine gun are shown as above:

```shellscript
## options with suggested paramters
//--- Data Collection -----
Data Coll En[7:0]    15                   ##needs to be adjusted for different number of asics
Trig Coll En[7:0]    0
Jumbo Enable    (unticked)
//--- Generator settings -----
Gen PreImp En    (ticked)
Gen Pre Int         16
Gen Nr Cycles        XXXX (this defines the number of event run by the generator)
Gen Interval        100000
// --- External trigger ------
Ext Trg En        (ticked) ## you will be using external triggers 
                   (unticked) ## for pedestal running
Ext Trg Delay        4 ## will need to be adjusted with beam
Ext Trg DeadTime     15 ## will need to be adjusted with beam               
// --- Fast Command ---------- ##DON'T touch!!!!!!!
DAQ FCMD             75
DAQ PUSH FCMD        75  
Gen Pre FCMD         45
Gen FCMD             75
// --- Machine gun -----------
Machine gun          10  ## defines how many sample/ trigger we take
```

The start and stop generator sections allows to enable injected signals to the ASIC to for instance run pedestal runs  (switch off external trigger in that case). It can also be used to trigger single events to test the trigger is being received in the software.

Keep in mind you need to adjust the  running with `Data Coll En`  according to the number of asics enabled, otherwise the output will not be correct and it might cause decoding problems. The setting should be:  `15` = 4 asics, `7` = 3 asics, `3` = 2 asics, `1` = 1 asic.

In the HV tab you can switch the respective HV on for each ASIC and entire FPGA's by ticking or unticking the boxes and clicking the `"Send HV Setting"` button.

## Procedure after Reboot of KCU

1. Reprogram KCU
2. Ping IP
3. Run IO-delay script (directly in python)&#x20;
4. Check in vivado that its aligned
5. Configure with H2GConfig using appropriate config files for all asics
6. Take pedestal and check in online monitoring (if not correct restart at set 3.)
7. Start running&#x20;

Don't forget to make sure the run-numbers increased in particular if the program terminated unexpectedly.

## Procedure after Recalibration

1. Ping IP
2. Run IO-delay script (directly in python)&#x20;
3. Check in vivado that its aligned
4. Configure with H2GConfig using appropriate config files for all asics
5. Take pedestal and check in online monitoring (if not correct restart at set 2.)
6. Start running&#x20;

Don't forget to make sure the run-numbers increased in particular if the program terminated unexpectedly.

## Online monitoring

The online monitor is a root application which can be started from a shell for reanalyzing an output file of the `H2GDAQ` or is run directly by the `H2GDAQ` application. The source code can be found [here](https://github.com/tlprotzman/h2g_online_monitoring). This application needs to be compiled so first order of business go into the checked out repository and compile it using `make` . Make sure you installed and loaded the `root` libraries for that.

```shellscript
// compile
cd h2g_online_monitoring
make
```

For automatically starting the online QA the **tickmark "Run Monitoring"** under the section "Online Monitoring" needs to be set and the path to the online monitoring software as well as the correct configuration (i.e $ONLINEMonSoftware/configs/lfhcal\_10sample\_testORNLSumV2.cfg) needs to be correctly set. This will in the backend for each new started run call the root based online monitoring. Setting the `DATA_DIRECTORY`  variable as the output directory of the DAQ-Software.&#x20;

An example of such a config file can be found below. This are starting points, should the read file have different settings in the header for MAX\_SAMPLES, NUM\_ASIC, NUM\_FPGA these will be overwritten with the numbers on contained in the actual file.

```
cat configs/lfhcal_10sample_testORNLSumV2.cfg 
###############
MAX_SAMPLES=11    ## number of samples
DETECTOR_ID=1     ## detector ID   1 == LFHCal
SETUP_ID=4        ## Setup ID    4 = Summing board version 2
NUM_FPGA=1        ## number of enabled FPGA's
NUM_ASIC=1        ### number of enabled ASICs
##############
```

A log file will be piped to the DAQ-data output directory as well contained the cout's of the online monitoring (might be worth to look at those from time to time). The file should start with something as follows, resetting the correct values.&#x20;

```
Parsing config file configs/lfhcal_10sample_testORNLSumV2.cfg
Key: MAX_SAMPLES, Value: 11
Key: DETECTOR_ID, Value: 1
Key: SETUP_ID, Value: 4
Key: NUM_FPGA, Value: 1
Key: NUM_ASIC, Value: 1
MADE IT HERE
base directory for data: /media/fbock/Lennard4TB/SummingBoardTestFull/raw/
Run file version:  0.14
Resetting NUM_FPGA to 1
Resetting NUM_ASIC to 4
Data enable check-----> 15	8	16	4
Setting PACKET_SIZE to 1358
Resetting MAX_SAMPLES to 10


Configuring for detector ID 1: LFHCal
SETUP ID 4: 2026 LFHCal TB setup v2 summing board
Configuration values:
NUM_LINES: 5
NUM_FPGA: 1
NUM_ASIC: 4
NUM_CHANNELS: 72
NUM_LINES: 5
MAX_SAMPLES: 10
MACHINE_GUN_MAX_TIME: 600
PACKET_SIZE: 1358


Configuring for detector ID 1: LFHCal
SETUP ID 4: 2026 LFHCal TB setup v2 summing board
Configuration values:
NUM_LINES: 5
NUM_FPGA: 1
NUM_ASIC: 4
NUM_CHANNELS: 72
NUM_LINES: 5
MAX_SAMPLES: 10
MACHINE_GUN_MAX_TIME: 600
PACKET_SIZE: 1358
Real decoding started
```

It should be followed by lines like this, everytime the h2g is updated and the online monitor is consequently run over the new data.&#x20;

```
Attempting to open file /media/fbock/Lennard4TB/SummingBoardTestFull/raw//Run234.h2g
Skipping first 25
Starting at byte 922
Building events... done!
Updating canvases...
===========================================
FPGA 0 statistics
Read Nr. 0 Received total: 	12376	 missed total:	0
===========================================
FPGA 0 completed 948/953 events.
 done!
Building events... done!
Updating canvases...
```

Ideally in particular the number of `missed total`  should remain 0 or at least with respect to the `received total`  be small. These numbers indicated how well the data could be reconstructed and statistics for each FPGA will be printed.&#x20;

Should you wanna rerun the online monitor manually on your own computer you'll have to set the `DATA_DIRECTORY` manually, and you an optionally set the `MONITORING_PORT` .

```
export DATA_DIRECTORY=/media/fbock/Lennard4TB/SummingBoardTestFull/raw/
export MONITORING_PORT=12345
root -b -x -q -l 'RunMonitoring.c(234,"configs/lfhcal_10sample_testORNLSumV2.cfg",0,false)'
```

To stop running the online monitor (if you started it yourself) press `ctrl+c` this will abort the process and also save a large fraction of the canvases as pdf in the original online-monitoring software folder.&#x20;

The histograms of the online monitor will be posted to "`localhost:12345`" (where the later is the `MONITORING_PORT` you set, by default this is `12345`). It can be opened in a web-browser. If you would like to for instance see the online monitoring of the curent run on the DAQ computer you can open an ssh tunnel to the monitoring computer:

```
ssh -L 12345:localhost:12345 user@computer
```

Afterwards you can open in a web-browser similar to running on your local computer the root file visualization on localhost:12345

<div><figure><img src="../.gitbook/assets/Screenshot at 2026-03-31 15-13-49.png" alt=""><figcaption></figcaption></figure> <figure><img src="../.gitbook/assets/Screenshot at 2026-03-31 15-14-08.png" alt=""><figcaption></figcaption></figure></div>

The monitoring is rather simple and the online root-browser interface allows us to check the integrity of the data. If you wanna keep in sync with the file as its being read click the tick mark **"Monitoring".** In that case the plots will be updated as the data comes in. Otherwise it remains in the status of the time you pulled it up. If you started the monitoring together with the DAQ run, it will automatically restart the process, but make sure you actually have the **Monitoring tick-mark** enabled.&#x20;

<mark style="background-color:red;">**It is advisable to open multiple tabs to localhost, so that you don't continuously need to switch between the different root plot layouts.**</mark>

Under the folder: _`QA Plots -> FPGA Summaries`_ a  plot with ADC, TOT and TOA for each channel can be found (channel numbers are calculated as `AsicNr*72+chInAsic`) As we are not using all 72 channels available in the asic but only 64, there will be empty vertical lines in regular intervals.

<figure><img src="../.gitbook/assets/Screenshot at 2026-03-31 15-56-09.png" alt=""><figcaption><p>Example were only one asic (asic 0) is actually connected to SiPMs, but all 4 connected asics were configured to read-out data. </p></figcaption></figure>

In the top panel the ADC (low energy response) is filled. The most probable response should be around `80` for each channel as set by the pedestal calibration . Large fluctuations indicate something didn't go right in the calibration or the configuration file wasn't correctly loaded (like seen for asics 1-3 in the above plot). If this happens please stop the run and reconfigure the asics. These plots need to be monitored in particular at the beginning of each run.&#x20;

Under the _`QA Plots -> DAQ Performance`_ several plots allowing to monitor the number of received packets, missed packets as well as fully reconstructable events can be found per FPGA (KCU).  These plots have to be monitored constantly, to check for sever problems during the data taking with misaligned events or similar problems. If you want you can arrange them as follows by selecting the "grid 2x2" option in the drop-down menu and clearing the canvas ones. Afterwards click the plots in the order you want.&#x20;

<figure><img src="../.gitbook/assets/Screenshot at 2026-03-31 15-17-56.png" alt=""><figcaption></figcaption></figure>

Individual "summary" plots of ADC, TOA & TOT can be found under the _`QA Plots-> Spectra -> adc`_ , _`QA Plots-> Spectra -> tot`_ , _`QA Plots-> Spectra -> toa`_  folders the _`strip_***_per_channel_$X`_  plots would be the individual panels in the _`QA Plots -> FPGA Summaries`_ plots.&#x20;

<figure><img src="../.gitbook/assets/Screenshot at 2026-03-31 15-19-00.png" alt=""><figcaption></figcaption></figure>

Each of these folder also has per asic summary plots _`QA Plots-> Spectra -> adc -> adc_fpga_0_asic_0`  ._ The visualize the actual distributions seen in each channel. However, they are order here by number of channel and we expect the last column to only show pedestal values, as those channels aren't connected to SiPMs. <mark style="color:red;">**These plots aren't correctly geometry ordered!**</mark>&#x20;

<figure><img src="../.gitbook/assets/Screenshot at 2026-03-31 16-17-52.png" alt=""><figcaption></figcaption></figure>

**For looking at the correct geometrically order channels please have a look at the `LFHCAL` -Folder!**&#x20;

In order to have the correct visualization for the LFHCal you need to have selected the correct setup ID in the configuration file (`setup_ID = 3` (green summing board), `setup_ID = 4` (red summing board), `setup_ID = 2` (2025 TB)). The geometrical order would then be from the top right corner

* layer 0: top row "chocolate bar" plot 1-4, bottom row "chocolate bar" plot 5-8
* layer 1: top row "chocolate bar" plot 1-4, bottom row "chocolate bar" plot 5-8
* layer 2: top row "chocolate bar" plot 1-4, bottom row "chocolate bar" plot 5-8
* layer 3: top row "chocolate bar" plot 1-4, bottom row "chocolate bar" plot 5-8
* layer 4: top row "chocolate bar" plot 1-4, bottom row "chocolate bar" plot 5-8
* layer 5: top row "chocolate bar" plot 1-4, bottom row "chocolate bar" plot 5-8
* layer 6: top row "chocolate bar" plot 1-4, bottom row "chocolate bar" plot 5-8
* layer 7: top row "chocolate bar" plot 1-4, bottom row "chocolate bar" plot 5-8

If we are running with the summing board the next asic would be connected to the next module using the same mapping, for reference have a look at the visualizations on the [create mapping page](../tb-analysis-basics/creating-a-mapping-file.md).

<figure><img src="../.gitbook/assets/Screenshot at 2026-03-31 15-15-20 (1).png" alt=""><figcaption><p>ADC spectra for 1 asic in correct LFHCal geometrical arrangement (layer 0 top row).</p></figcaption></figure>

<figure><img src="../.gitbook/assets/Screenshot at 2026-03-31 15-16-29.png" alt=""><figcaption><p>Max ADC spectra for 1 asic in correct LFHCal geometrical arrangement (layer 0 top row).</p></figcaption></figure>

<figure><img src="../.gitbook/assets/Screenshot at 2026-03-31 15-14-56 (1).png" alt=""><figcaption><p>Full waveforms as function of sample nr for 1 asic in correct LFHCal geometrical arrangement (layer 0 top row).</p></figcaption></figure>

<figure><img src="../.gitbook/assets/Screenshot at 2026-03-31 15-15-59.png" alt=""><figcaption><p>TOA distribution for 1 asic in correct LFHCal geometrical arrangement (layer 0 top row).</p></figcaption></figure>

Please make sure you go through all ASICs and all these summary plots on a regular basis and check that the data looks reasonable, if in question don't hesitate to point problems out to the TB-coordinators.
