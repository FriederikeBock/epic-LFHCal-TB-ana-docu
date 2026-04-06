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

```bash
// enter eic-shell
./eic-shell

//Enter the xrootd environment:
xrdfs root://dtn-eic.jlab.org

// see all files
ls /volatile/eic/EPIC/TestBeam/LFHCal/
2023_SPSH4/    2023_PST09/     2024_PST09/      2025_PST09/    2026_PST10/    2026_SPSH2/
```

For instance the raw data files can be found&#x20;

```bash
# 2023 raw data
ls /volatile/eic/EPIC/TestBeam/LFHCal/2023_SPSH4/rawCAEN
ls /volatile/eic/EPIC/TestBeam/LFHCal/2023_PST09/rawCAEN

# 2024 raw data
ls /volatile/eic/EPIC/TestBeam/LFHCal/2024_PST09/rawCAEN
ls /volatile/eic/EPIC/TestBeam/LFHCal/2024_PST09/rawHGCROC

# 2025 raw data
ls /volatile/eic/EPIC/TestBeam/LFHCal/2025_PST09/raw 

# 2026 raw data
ls /volatile/eic/EPIC/TestBeam/LFHCal/2026_PST10/raw 
ls /volatile/eic/EPIC/TestBeam/LFHCal/2026_SPSH2/raw 
```

You can download specific files using outside of xrootd:

```bash
xrdcp root://dtn-eic.jlab.org/volatile/eic/EPIC/TestBeam/LFHCal/2025_PST09/raw/Run181.h2g
 Run181.h2g
```

