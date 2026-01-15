---
description: >-
  This page describes the general structure of the h2g_decode and how it is
  supposed to work for the 10G data structure.
---

# Data decoding 10G

## Setup

The standalone program for the decoding of the H2GCROC data is called **h2g\_decode** it has been writtine by Tristan Protzman ([link](https://github.com/tlprotzman/h2g_decode/)). It is fully c++ based and need as prerequisit a working root installation.&#x20;

It was originally designed for the decoding of the data acquired with the firmware version 3.XX and has been recently extended to be able to accommodate the more recent data format produced by firmware versions higher than 5.06X. The software designed to be fully backward compatible.

```bash
# Usage of h2g-decode
./h2g_run --help
Usage: h2g_decode -r <run_number> [-d <detector_id>] [-n <num_kcu>] [-g] [-G LEVEL] [-T]
  -r, --run         Run number (required)
  -d, --detector    Detector ID (default: 0, LFHCAL: 1, EEEMCAL: 2)
  -n, --num-kcu     Number of KCUs (default: 4)
  -a, --num-asic    Number of ASICs per KCU (default: 2)
  -g, --debug       Enable debug output with INFO level
  -G, --debug-level Set debug level explicitly:
                      0: OFF, 1: ERROR, 2: WARNING, 3: INFO, 4: DEBUG, 5: TRACE
  -T, --truncate    Enable ADC truncation
  -h, --help        Show this help message
```

The decoder in its standalone mode can be started as follows, apriori the raw-file directory (`$DATA_DIRECTORY`) and your desired output directory (`$OUTPUT_DIRECTORY`) should be set using global variables. If the data directory is not set correctly the program will seg fault not having found the raw file.  Afterwards the program can be started with the command below

```bash
# set data and 
export DATA_DIRECTORY=/WHEREVER/YOUR/DATA/IS
export OUTPUT_DIRECTORY=/WHEREVER/YOUR/WANT/THE/OUTPUT/TO/BE
 
# start decoder
## this will start the decoding for the file Run$RUNNR.h2g (i.e. $RUNNR=122) 
## which has n KCUs ($NKCU) with m HGCROCs ($NHGCROC) attached  (i.e. 2 and 4 respectively)
## it will print log information to the info level (-G 3)
./h2g_run -r $RUNNR -d 1 -n $NKCU -a $NHGCROC -G 3 

## remember you can redirect the output to the shell at any point, which is particularly helpful for debbuging
./h2g_run -r $RUNNR -d 1 -n $NKCU -a $NHGCROC -G 3 > log_$RUNNR.log

 
```
