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

<figure><img src="../.gitbook/assets/Screenshot from 2025-11-18 18-39-07 (1).png" alt=""><figcaption></figcaption></figure>

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
Data Coll En[7:0]    15
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

