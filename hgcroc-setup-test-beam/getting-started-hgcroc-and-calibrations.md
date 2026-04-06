---
description: >-
  This page describes the steps of starting up the HGCROC, programming it and
  running through the calibration procedures.
---

# Getting Started HGCROC & Calibrations

## Programming KCU

First of all you need to open source the environment for `vivado` and open it (see commands on ORNL-DAQ computer below).&#x20;

```shellscript
// sourcing vivado environment
source Xilinx/2025.1/Vivado_Lab/settings64.sh
// open vivado lab
vivado_lab
```

This should bring you to the home screen of vivado. There you should follow the steps listed below

* Open the hardware manager
* Switch on KCU (if not yet done)
* Open target -> auto connect
* program xckcu - firmware version for&#x20;
  * 10GB & 2 HGCROC proto boards (v5.071)
    * &#x20;TB-DAQ PC location:  `~/Software/HGCROC/fw/5.071/kcu105_teng_hpc_lpc.bit`
  * programm KCU a second time with same firmware
  * "refresh" to make debug probes visible&#x20;
  * press play to check setup for each ASIC
* 2 KCU's can't be simultaneously programmed with this version of vivado,  so the programming and checking step have to be repeated for the other KCU

<figure><img src="../.gitbook/assets/Screenshot from 2025-11-18 17-08-56.png" alt=""><figcaption></figcaption></figure>

## HGCROC calibration procedure

For the HGCROC there are 4 main calibration steps:

1. **IODelay scan:** Although this isn't really a calibration you'll need to run it everytime you reconfigured the asic (otherwise you data might be nonesense)
2. **Pedestal Calibration:** Determines where the minimum `ADC` value without any signal should be situated (recommended value `80`)
3. **ToA Calibration:** Determines at which threshold value equivalent the _Time of Arrival (ToA)_ is fired (rising edge). ATTENTION: The value we are setting here is given as `injection DAC` (Digital-to-Analog-Converter) which is not equivalent to the `ADC` value referred to during the pedestal calibration. The actual conversion factor between those depends on the SiPM type.&#x20;
4. **ToT Calibration:** Determines at which threshold value equivalent the _Time over Threshold (ToT)_ is fired (falling edge). Once more the settable value is  the `injection DAC` value no the `ADC` value.&#x20;

<div><figure><img src="../.gitbook/assets/Screenshot at 2025-11-07 11-34-11.png" alt="" width="266"><figcaption></figcaption></figure> <figure><img src="../.gitbook/assets/Screenshot at 2025-11-07 11-35-17.png" alt="" width="375"><figcaption></figcaption></figure></div>

After these calibrations have been run the **Internal Injection (3 options: low, high, 2.5V)** test should be run ideally for all channels to validate the thresholds also in `ADC` equivalent. These test however take fairly long (\~2-4min/4 channels) and it might not be advisable to run during a test beam setting.

The calibration is handled and steered using `H2GCalibX`  package ([link](setting-up-daq-pc.md#software-installation)).&#x20;

### Setting IO-delay

The IO Delay Scan is used to adjust the timing of the signals received by the FPGA. This is crucial for ensuring that the signals are correctly aligned and processed. **Run this every time you do a power cycle / reprogram the FPGA.**

**This can either be done using the H2GCalib or with manual-python scripts. At this stage we suggest to run the manual python scripts.**

```shellscript
# For the 2026 LFHCal TB - go to:
cd /home/localadmin/Software/HGCROC/fw/5.071/Python/
# execute:
# for FPGA_0 10.1.2.208 connected to ORNL-02 & ORNL-03 HGCROC boards)
python3 003_10G_Test_Align_208_ORNL02-03.py     
# for FPGA_1 10.1.2.209
python3 003_10G_Test_Align_209.py  
```

At the end of the shell output the following lines hould be displayed for each ASIC, if they are looking as shown below, everything is fine.&#x20;

```shellscript
// Some code
Test ASIC 0...
Delay: 30
                 ASIC CMD  DLY10 AR   Data1    Data0    Trig3    Trig2    Trig1    Trig0
Iteration #000:  0xa0 0x0c 1e/1e 0x3f accccccc accccccc accccccc accccccc accccccc accccccc 
Iteration #001:  0xa0 0x0c 1e/1e 0x3f accccccc accccccc accccccc accccccc accccccc accccccc 
Iteration #002:  0xa0 0x0c 1e/1e 0x3f accccccc accccccc accccccc accccccc accccccc accccccc 
Iteration #003:  0xa0 0x0c 1e/1e 0x3f accccccc accccccc accccccc accccccc accccccc accccccc 
Iteration #004:  0xa0 0x0c 1e/1e 0x3f accccccc accccccc accccccc accccccc accccccc accccccc 
Iteration #005:  0xa0 0x0c 1e/1e 0x3f accccccc accccccc accccccc accccccc accccccc accccccc 
Iteration #006:  0xa0 0x0c 1e/1e 0x3f accccccc accccccc accccccc accccccc accccccc accccccc 
Iteration #007:  0xa0 0x0c 1e/1e 0x3f accccccc accccccc accccccc accccccc accccccc accccccc 
Iteration #008:  0xa0 0x0c 1e/1e 0x3f accccccc accccccc accccccc accccccc accccccc accccccc 
Iteration #009:  0xa0 0x0c 1e/1e 0x3f accccccc accccccc accccccc accccccc accccccc accccccc 
Iteration #010:  0xa0 0x0c 1e/1e 0x3f accccccc accccccc accccccc accccccc accccccc accccccc 
Iteration #011:  0xa0 0x0c 1e/1e 0x3f accccccc accccccc accccccc accccccc accccccc accccccc 
Iteration #012:  0xa0 0x0c 1e/1e 0x3f accccccc accccccc accccccc accccccc accccccc accccccc 
Iteration #013:  0xa0 0x0c 1e/1e 0x3f accccccc accccccc accccccc accccccc accccccc accccccc 
Iteration #014:  0xa0 0x0c 1e/1e 0x3f accccccc accccccc accccccc accccccc accccccc accccccc 
Iteration #015:  0xa0 0x0c 1e/1e 0x3f accccccc accccccc accccccc accccccc accccccc accccccc 
Iteration #016:  0xa0 0x0c 1e/1e 0x3f accccccc accccccc accccccc accccccc accccccc accccccc 
Iteration #017:  0xa0 0x0c 1e/1e 0x3f accccccc accccccc accccccc accccccc accccccc accccccc 
Iteration #018:  0xa0 0x0c 1e/1e 0x3f accccccc accccccc accccccc accccccc accccccc accccccc 
Iteration #019:  0xa0 0x0c 1e/1e 0x3f accccccc accccccc accccccc accccccc accccccc accccccc 
```

Should this not be the case, please replace the different IO-delays at the top of each script with either the proposed values (see full output of the script), or the a value in the middle of the first long block. To confirm you can check in vivado, by clicking run again. In case everything is fine it should look as below, with all the valid signals aligned (light green boxes). The first 4 double-lines correspond to the trigger signals and are followed by the 2 data lines and their respective valids.

<figure><img src="../.gitbook/assets/Screenshot from 2025-11-18 17-14-37.png" alt=""><figcaption></figcaption></figure>

### Calibration & Configuration Gui

The Calibration package require opening a different kind of terminal on ubuntu called `konsole` , running it in the standard Ubuntu terminal will not work.

You can start the gui from `konsole` by entering the respective H2GCalibX-Software directory and running:

```bash
# starting Calib & Config GUI
python3 200_UI.py
```

<figure><img src="../.gitbook/assets/image (13).png" alt=""><figcaption></figcaption></figure>

This script provides a user interface for selecting the calibration files and setting various parameters for the calibration process. Once more it will ask in the beginning to select how many KCU's and ASICs per KCU are connected. You can change the number of HGCROCs to be handeled by changing the ASIC number in the grey field behind the current number, this requires an explicit `ENTER`  command to be applied. Morevover you can change the default configuration of the HGCROC to be loaded. For the 2026 TB campaign this should be:

```
/home/lfhcal/Software/HGCROC/H2GCalibX/config/default_2025Oct_config.json
```

Another FPGA can be added or removed by typing&#x20;

* `^n` to get an additional FPGA tab&#x20;
* `^w`  to close the current FPGA tab
* `q` closes the entire gui

**Before starting any operation in this gui don't forget to start the socket pool  using the corresponding button! After you are done don't forget to terminate the socket before starting any other data taking process**.

The configuration folder (`./configs`) holds further general configuration scripts, like&#x20;

* `socket_pool_configX.json:` Configuration for the UDP communication. Including the IP addresses and ports for the different KCUs and the PC.
* `h2gcroc_1v4_r1.json`: Configuration for the H2GCROC registers. **Users should not modify this file**.

<figure><img src="../.gitbook/assets/image_Steering.png" alt=""><figcaption></figcaption></figure>

This gui as seen above cannot only handle the calibration but also serves as primary tool to configure the ASICs. The options under the tabs can be found as follows:

* `FPGA Settings`: general settings, i.e. base config, number of ASICs
* `Registers`: Loading of configuration files, changing specific register values
* `201 IODelayX`: Allows to run a IO-delay scan&#x20;
* `202 PedestalX`: Running of Pedestal calibration
* `203 ToAX`: Running of ToA calibration
* `204 ToTX`: Running of ToT calibration
* `205 Injection`: Cross checking the calibrations using the 3 different injection scans
* `206 ScanDAC`: Systematic scanning of multiple DAC values in a row using different injection scan options

### IO-delay scan <a href="#user-content-calibration-scripts-overview" id="user-content-calibration-scripts-overview"></a>

(Estimated running time: < 1 minute)

<mark style="color:red;background-color:red;">**Please don't run this for now, but rather use the "manual" script mentioned above for the IO-delay - this should only be done after reconfiguring the asic.**</mark>

You can find the results of the IO Delay Scan in the `./dump/102_IO_Delay_data_YYYYMMDD_HHMMSS` folder. There will be pdf files for how the IO Delay values are set. The dashed red line indicates the optimal IO Delay value, which should be in the middle of the widest locked region.

<figure><img src="../.gitbook/assets/Res_102.png" alt=""><figcaption></figcaption></figure>

After the IO-delay scan finished one should check in `vivado` that the data lines in case of a valid data flag are set to `acccccc` , while the trigger lines should be should show a different value.&#x20;

### Pedestal Calibration

(Estimated running time: \~ 3 minutes)

<figure><img src="../.gitbook/assets/image (15) (1).png" alt=""><figcaption></figcaption></figure>

In the backend this will be calling the script `202_PedestalCalibX.py` . The desired pedestal target \[ADC] can be set via the first line entry (here `80`), don't forget the `ENTER` , as otherwise the change won't be taken. **Recommended value range: 50-150 ADC.** The base configuration should be `/home/lfhcal/Software/HGCROC/H2GCalibX/config/default_2025Oct_config.json`  (Template JSON File).&#x20;

Moreover, gain settings can be adjusted: the _`Feedback Resistor (RF)`_, the _`Feedback Capacitor (CF)`_, the _`Current Conveyor Gain (CC)`_, and the _`CF Compensation (CFComp)`_ , make sure to type `ENTER` to bring them to effect.

The output of the pedestal calibration will be new I2C JSON files. And the file paths can be automatically loaded in the ToA calibration section. The output files will be saved in the `./dump/202_PedestalCalibX_YYYYMMDD_HHMMSS` folder. The result pdf file will show how the pedestal values are set.&#x20;

As current default configuration `config/default_2024Aug_config.json`  should be used. Make sure the fine channel calibration looks reasonable and no large outliers can be found. If the results aren't satisfactory reset the IO-delays and retry. If after a second attempt the calibration still hasn't succeeded. It could be tried to load a valid calibration from a different proto-board, primarily the `Noinv_vref` and `Inv_vref` bits in the Reference Voltage Register should be adjusted in that case.&#x20;

<div><figure><img src="../.gitbook/assets/02_pede_after_global_inv_scan.png" alt=""><figcaption></figcaption></figure> <figure><img src="../.gitbook/assets/03_coarse_pede_trim.png" alt=""><figcaption></figcaption></figure></div>

A good calibration should have the final pedestal values nicely aligned around the target value, with a small spread across all channels.

<div><figure><img src="../.gitbook/assets/00_global_inv_ref_scan.png" alt=""><figcaption></figcaption></figure> <figure><img src="../.gitbook/assets/04_global_inv_ref_scan_fine (1).png" alt=""><figcaption></figcaption></figure></div>

<div><figure><img src="../.gitbook/assets/05_fine_inv_vref_scan.png" alt=""><figcaption></figcaption></figure> <figure><img src="../.gitbook/assets/06_final_fine_pede_trim.png" alt=""><figcaption></figcaption></figure></div>

### Time-of-Arrivel(ToA) Calibration

(Estimated running time: \~ 20-30 minutes)

<figure><img src="../.gitbook/assets/image (16).png" alt=""><figcaption></figcaption></figure>

For the ToA calibration the previous Pedestal Calibration can be loaded using the `Read from 202 Output`  button, or the individual asics can be configured vias the browse buttons behind the file names. Make sure to always configure all ASICs with at least a basic file. In the backend the script `203_ToACalibX.py` , is being executed.

The `target ToA` given in **DAC (NOTE: it is by the unit of injection DAC, not ADC!)** can be given in the first line (here `50`), keep in mind the ToA calibration uses the **low injection** path for its calibration hence a value of 50 might be very noisy. We recommend running a few [injections](getting-started-hgcroc-and-calibrations.md#hgcroc-calibration-procedure) with low injection to determine the relation between ADC and DAC for your given gain settings.&#x20;

**For the LFHCal TB with the summing boards we recommend values between 150-250, which corresponds to approximate 15-25 ADC.**

Moreover, it can be steered how many channels are evaluated in parallel (here `8`) and how many channels are to be scanned per ASIC (here `76`).

The output files will be updated in the -i field in the ToT calibration section. The output files will be saved in the `./dump/203_ToACalibX_YYYYMMDD_HHMMSS` folder.&#x20;

The ToA-calibration is currently being executed in 3 steps (target for the example plots `100`), starting with a very coarse scanning window to estimate the first `ToA_vRef` values for the different half chips and then decreasing the stepping size an window size successively.  The red line indicated in each vertical column indicated the edge at which the ToA starts firing. These need to be adjusted such that they correspond to the same value (or similar) value for all channels.

X axis values represent the different channel numbers, while the y-axis values indicate the 12b-internal injection value being evaluated in each 2D bin. The z-axis represents the actual ToA-value. Different colors in different regions indicate a timing offset between the different HGCROC half chips.&#x20;

<div align="left"><figure><img src="../.gitbook/assets/round0_injection_scan_val2.png" alt=""><figcaption><p>Typical initial ToA calibration plot. </p></figcaption></figure> <figure><img src="../.gitbook/assets/round0_toa_halves_scan_val2.png" alt=""><figcaption></figcaption></figure></div>

A good calibration should have the final ToA values like, however the timing alignment of the different halfs (color scale) is currently not performed.&#x20;

<div><figure><img src="../.gitbook/assets/final_scan_val2.png" alt=""><figcaption><p>Result of a good ToA calibration with a target value of 50 DAC as turn on value. </p></figcaption></figure> <figure><img src="../.gitbook/assets/round2_toa_halves_scan_val2.png" alt=""><figcaption></figcaption></figure></div>

### Time-over-Threshold(ToT) Calibration

(Estimated running time: \~ 15-20 minutes)

<figure><img src="../.gitbook/assets/image (17).png" alt=""><figcaption></figcaption></figure>

For the ToT calibration the previous ToA Calibration can be loaded using the `Read from 203 Output`  button, or the individual asics can be configured vias the browse buttons behind the file names. Make sure to always configure all ASICs with at least a basic file. In the backend the script `301_ToACalib_Omega.py` , is being executed.

The `target ToT` given in **DAC (NOTE: it is by the unit of injection DAC, not ADC!)** can be given in the first line (here `750`), keep in mind the ToA calibration uses the **high injection** path for its calibration. We recommend running a few [injections](getting-started-hgcroc-and-calibrations.md#hgcroc-calibration-procedure) with high injection to determine the relation between ADC and DAC for your given gain settings and ascertain at which point the TOT should start firing (ideally somewhere between 800-1024 ADC).&#x20;

Moreover, it can be steered how many channels are evaluated in parallel (here `8`) and how many channels are to be scanned per ASIC (here `76`).

The output folder is `./dump/302_ToTCalib_Omega_YYYYMMDD_HHMMSS`. The resulting files is in the same format as the ToT calibration. Similarly as for the ToT calibration the calibration is run in multiple steps. X axis values represent the different channel numbers, while the y-axis values indicate the 12b-internal injection value being evaluated in each 2D bin. The z-axis represents the actual ToT-value. Different colors in different regions indicate a timing offset between the different HGCROC half chips.&#x20;

<div align="center"><figure><img src="../.gitbook/assets/scan0_val1.png" alt=""><figcaption><p>Typical initial ToT calibration plot. </p></figcaption></figure> <figure><img src="../.gitbook/assets/tot_halves_scan_val1.png" alt=""><figcaption></figcaption></figure></div>

&#x20;An example of a good ToT calibration result is shown below:

<figure><img src="../.gitbook/assets/final_scan_val1.png" alt=""><figcaption><p>Result of a good ToT calibration with a target value of 300 DAC as turn on value. </p></figcaption></figure>

### Internal Injection

(Estimated running time: \~ 50 minutes for all channels)

<figure><img src="../.gitbook/assets/image (18) (1).png" alt=""><figcaption></figcaption></figure>

This gui allows to run several variants of the injection scan with fixed injection values. The injection values can be set in the first line `Injection DAC`  (here set to 100). Make sure you type `ENTER` if you changed the value at the end of the line.&#x20;

The next row allows you to select the injection type

1. **Low injection**: both `Enable 2.5V Injection`  and `Enable High Range Injection`  set to **off**
2. **High injection**: `Enable 2.5V Injection`  **off** and `Enable High Range Injection`  set to **on**
3. **2.5V Injection:** `Enable 2.5V Injection`  **on** and `Enable High Range Injection`  set to **off**

The different injections use different injection paths, so make sure you select the one you wanted to check.

<figure><img src="../.gitbook/assets/Screenshot 2026-04-06 at 10.44.53 AM.png" alt=""><figcaption></figcaption></figure>

This script is used to inject a signal into the H2GCROC3\[B-D] channels for calibration purposes. It is not part of the main calibration flow but can be used for additional testing and verification.

Moreover, it can be steered how many channels are evaluated in parallel (here `8`) and how many channels are to be scanned per ASIC (here `76`).

The output files will be saved in the `./dump/`205\_Injection`_YYYYMMDD_HHMMSS` folder. The result pdf file will show the injected signal and the response of the channels. This can be used to verify the calibration results and the performance of the H2GCROC3\[B-D].

<div><figure><img src="../.gitbook/assets/Screenshot at 2026-04-06 16-28-29.png" alt=""><figcaption></figcaption></figure> <figure><img src="../.gitbook/assets/Screenshot at 2026-04-06 16-29-55.png" alt=""><figcaption><p>ToA configured to fire at 100 DAC (low injection), TOT configured to fired at 750 DAC (high injection). Hence no TOT plot.</p></figcaption></figure></div>

### Injection Scan

(Estimated running time: multiple hours for all channels)

This feature can be found under the `206 ScanDAC` tab and can be used to do a full scan of multiple DAC values in fixed intervals for several channels at once. It can be selected which injection should be executed in a similar way as for the Internal Injection with a fixed value.&#x20;

The output files will be saved in the `./dump/`206\_InjectionDAC`_YYYYMMDD_HHMMSS` folder. The result pdf file will show the injected signal (x-axis) and the maximum response of the channels. This can be used to verify the calibration results and the performance of the H2GCROC3\[B-D].

<figure><img src="../.gitbook/assets/Screenshot at 2026-04-06 16-25-30.png" alt=""><figcaption></figcaption></figure>

## Configuring the HGCROC

The configuration of the HGCROC is now also handled by the H2GCalibX under the tab `Registers` . The respective configurations can be loaded for each ASIC using the latest run configurations&#x20;

* Load from Pedestal Template (only base config)
* Load from Pedestal Output (pedestal file created in this session)
* Load from ToA Output (ToA file created in this session)
* Load from ToT Output (ToT file created in this session)

Otherwise you can browse the current folder using the `Browse Register JSON`  in order to look for an older JSON file. The respective configurations have to be situated in the _H2GCalibX software folder._ The current configuration can be saved using the `Save Register JSON`, should any modifications have been made. **This operation has to be repeated for all connected ASICS (shaded tabs).**

<figure><img src="../.gitbook/assets/image (14).png" alt=""><figcaption></figcaption></figure>

Afterwards, the configuration is send to all ASICs using the command `Send to All ASICSs` . The read-back function is currently not yet operational.

### Configuration Files

In the `config` folder, you can find the configuration files for the different configurations. Several configurations are provided as examples.

After the first run, a `caliblibX.ini` file will be created in the same folder as the application. This file stores the last configuration used by the user. Deleting this file will reset the configuration to the default one.

After reconfiguring the asic using the configuration tool it should be checked that the the data lines and trigger lines have reasonable values using `vivado` for every asic (press `play` and check the values).

<figure><img src="../.gitbook/assets/Screenshot from 2025-11-18 17-19-41.png" alt=""><figcaption></figcaption></figure>



### Manual modifications of Configuration values <a href="#user-content-license" id="user-content-license"></a>

<mark style="background-color:$danger;">**This is only adviced for experts or after explicit instructions by an expert!**</mark>

The HGCROC has a very large number of configuration parameters and consequently registers which can and/or have to be set. A detailed description of those to the best current knowledge can be found in:

{% file src="../.gitbook/assets/H2GCROC3_datasheet_1_4.pdf" %}

Nearly all of them can be adjusted using the `Register` part of the gui in its various tabs which can be accessed via the side panel.

<figure><img src="../.gitbook/assets/image (19).png" alt=""><figcaption></figcaption></figure>

Below you find examples of each of the individual register panels, clicking on any of the bit fields will change the bit (0->1 or vice versa) so be careful when clicking randomly in the various positions.&#x20;

<figure><img src="../.gitbook/assets/image (20).png" alt=""><figcaption></figcaption></figure>

In order to correctly position the maximum of the signal with respect to the trigger signal you might need to touch the `L1_offset` bits, they can be found under `Digital_Half_0` & `Digital_Half_1`  remember to change them for all necessary ½ chips. The `L1_offset` is an 8bit number increasing the least  significant bit by 1 will shift the waveform to the right by 1 sample.&#x20;

### What to do if Calib crashed and socket reconnection failed?

If the calib crashed in an unforseen way, the socket sometimes doesn't get closed, this is a bit of a problem, as there can be only one socket on the same port. Thus you need to find the process which still has the socket open.&#x20;

```bash
// show open ports/sockets
sudo ss -tulpn
// example output
Netid	State	 Recv-Q	Send-Q	Local Address:Port  	Peer Address:Port   Process	 
udp	UNCONN	0	960	0.0.0.0:43050	 	0.0.0.0:*	    users:(("cs_server",pid=2308457,fd=5))	 
udp	UNCONN	0	0	0.0.0.0:60611	 	0.0.0.0:*	    users:(("avahi-daemon",pid=1399,fd=14))	
udp	UNCONN	0	0	127.0.0.54:53	 	0.0.0.0:*	    users:(("systemd-resolve",pid=1322,fd=16))	
udp	UNCONN	0	0	127.0.0.53%lo:53	0.0.0.0:*	    users:(("systemd-resolve",pid=1322,fd=14))	
udp	UNCONN	0	0	0.0.0.0:1534		0.0.0.0:*	    users:(("vivado_lab",pid=2307920,fd=302))	 
udp	UNCONN	0	0	0.0.0.0:4000		0.0.0.0:*	    users:(("nxd",pid=2319,fd=13))	
udp	UNCONN	0	0	0.0.0.0:54216	 	0.0.0.0:*	    users:(("hw_server",pid=2308349,fd=5))	 
udp	UNCONN	8640	0	10.7.140.15:5353	0.0.0.0:*	    users:(("nxserver.bin",pid=2225,fd=60))	
udp	UNCONN	8640	0	10.1.2.207:5353		0.0.0.0:*	    users:(("nxserver.bin",pid=2225,fd=58))	
udp	UNCONN	0	0	0.0.0.0:5353		0.0.0.0:*	    users:(("nxserver.bin",pid=2225,fd=59))	
udp	UNCONN	0	0	0.0.0.0:5353		0.0.0.0:*	    users:(("avahi-daemon",pid=1399,fd=12))	
udp	UNCONN	0	0	[::]:4000		[::]:*	    	    users:(("nxd",pid=2319,fd=14))	
udp	UNCONN	0	0	[::]:54173	 	[::]:*	            users:(("avahi-daemon",pid=1399,fd=15))	
udp	UNCONN	0	0	[::]:5353		[::]:*	            users:(("avahi-daemon",pid=1399,fd=13))	
tcp	LISTEN	3	128	127.0.0.1:6002		0.0.0.0:*	    users:(("python3",pid=3837331,fd=4))	 
tcp	LISTEN	7	128	127.0.0.1:6001		0.0.0.0:*	    users:(("python3",pid=3837331,fd=5))	 
tcp	LISTEN	0	128	127.0.0.1:7001		0.0.0.0:*	    users:(("nxnode.bin",pid=4144,fd=27))	
tcp	LISTEN	0	100	127.0.0.1:22574	 	0.0.0.0:*	    users:(("nxserver.bin",pid=2225,fd=26))	
tcp	LISTEN	0	4096	127.0.0.1:631		0.0.0.0:*	    users:(("cupsd",pid=3610485,fd=7))	
tcp	LISTEN	0	16	127.0.0.1:3121		0.0.0.0:*	    users:(("hw_server",pid=2308349,fd=4))	 
tcp	LISTEN	0	4096	127.0.0.54:53	 	0.0.0.0:*	    users:(("systemd-resolve",pid=1322,fd=17))	
tcp	LISTEN	0	100	0.0.0.0:4000		0.0.0.0:*	    users:(("nxd",pid=2319,fd=7))	
tcp	LISTEN	0	5	127.0.0.1:42619	 	0.0.0.0:*	    users:(("cs_server",pid=2308457,fd=6))	 
tcp	LISTEN	0	64	127.0.0.1:25321	 	0.0.0.0:*	    users:(("nxserver.bin",pid=2225,fd=34))	
tcp	LISTEN	0	4	0.0.0.0:3000		0.0.0.0:*	    users:(("hw_server",pid=2308349,fd=7))	 
tcp	LISTEN	0	4	0.0.0.0:3001		0.0.0.0:*	    users:(("hw_server",pid=2308349,fd=8))	 
tcp	LISTEN	0	4	0.0.0.0:3002		0.0.0.0:*	    users:(("hw_server",pid=2308349,fd=10))	
tcp	LISTEN	0	4	0.0.0.0:3003		0.0.0.0:*	    users:(("hw_server",pid=2308349,fd=12))	
tcp	LISTEN	0	4	0.0.0.0:3004		0.0.0.0:*	    users:(("hw_server",pid=2308349,fd=14))	
tcp	LISTEN	0	4	0.0.0.0:3005		0.0.0.0:*	    users:(("hw_server",pid=2308349,fd=16))	
tcp	LISTEN	0	100	127.0.0.1:25001	 	0.0.0.0:*	    users:(("nxrunner.bin",pid=4167,fd=14))	
tcp	LISTEN	0	100	127.0.0.1:12001	 	0.0.0.0:*	    users:(("nxnode.bin",pid=4144,fd=20))	
tcp	LISTEN	0	4096	127.0.0.53%lo:53	0.0.0.0:*	    users:(("systemd-resolve",pid=1322,fd=15))	
tcp	LISTEN	0	4096	0.0.0.0:22	 	0.0.0.0:*	    users:(("systemd",pid=1,fd=92))	 
tcp	LISTEN	0	4096	[::1]:631	 	[::]:*	            users:(("cupsd",pid=3610485,fd=6))	
tcp	LISTEN	0	100	[::]:4000		[::]:*	            users:(("nxd",pid=2319,fd=8))	
tcp	LISTEN	0	128	[::1]:7001		[::]:*	            users:(("nxnode.bin",pid=4144,fd=25))	
tcp	LISTEN	0	4096	[::]:22			[::]:*	            users:(("systemd",pid=1,fd=93))   
// search for process bound to 127.0.0.1 port 6002/6001 this should be a python process
127.0.0.1:6002    users:(("python3",pid=3837331,fd=4))      
127.0.0.1:6001    users:(("python3",pid=3837331,fd=5))                                 
// kill the respective process in the backend
kill -9 3837331
```
