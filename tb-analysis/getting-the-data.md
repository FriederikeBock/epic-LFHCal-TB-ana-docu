---
description: >-
  This section aims at explaining how you can get the LFHCal TB data if you
  didn't obtain it from a disk during the TB or from Fredi ;).
icon: floppy-disk
---

# Getting the data

## Step 1: Install eic-shell

In order to obtain the basic full eic-software stack please follow the instructions given in [https://eic.github.io/tutorial-setting-up-environment/](https://eic.github.io/tutorial-setting-up-environment/) . This is the easiest way to get access to the data and provides you with a full root installation, which you will need in any case.&#x20;

## Step 2: Get the data

```
// enter eic-shell
./eic-shell

//Enter the xrootd environment:
xrdfs root://dtn-eic.jlab.org

// see all files
ls /volatile/eic/EPIC/MC_input/LFHCal_BT/

```

For instance the converted root trees for the CAEN data from 2024 can be found here:&#x20;

```
ls /volatile/eic/EPIC/MC_input/LFHCal_BT/converted/CAEN_Sept24_TB_PS/
```

Please remember the converted data always corresponds a specific version of the software. If you are changing the basic data structure, you will have to reconvert the data yourself. The rae data can be found here:&#x20;

```
ls /volatile/eic/EPIC/MC_input/LFHCal_BT/raw/CAEN_Sept24_TB_PS/
```

You can download specific files using outside of xrootd:

```
xrdcp root://dtn-eic.jlab.org/volatile/eic/EPIC/MC_input/LFHCal_BT/raw/CAEN_Sept24_TB_PS/Run5_list.txt Run5_list.txt
```

