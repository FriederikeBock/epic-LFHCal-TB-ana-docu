---
description: >-
  This page describes the steps of starting up the HGCROC, programming it and
  running through the calibration procedures.
---

# Getting Started HGCROC & Calibrations

## Programming KCU

First of all you need to open source the environment for `vivado` and open it (see commands on ORNL-DAQ computer below).&#x20;

```
// sourcing vivado environment
source Xiling/2025.1/Vivado_Lab/setting64.sh
// open vivado lab
vivado_lab
```

This should bring you to the home screen of vivado. There you should follow the steps listed below

* Open the hardware manager
* Switch on KCU (if not yet done)
* Open target -> auto connect
* program xckcu - firmware version for 1G & 1 HGCROC proto board (v2)
* press play to check setup for each ASIC

## Configuring the HGCROC

The software to configure the HGCROC is called `H2GConfig` (see [link](setting-up-daq-pc.md#software-installation) for details where to find it).  This can be started as follows:

```
// starting HGCROC configuration program
python3 H2GConfig.py
```

<figure><img src="../.gitbook/assets/starting_window_mac.png" alt=""><figcaption></figcaption></figure>

This brings up the initial start window make sure you choose the appropriate number of KCU's and Asics (HGCROCs) per KCU. Which should bring you to the main window.&#x20;

<figure><img src="../.gitbook/assets/main_window_mac.png" alt=""><figcaption></figcaption></figure>

To test whether the KCUs are reachable use the `Ping FPGA` button, if that does not work check your network configuration and follow the steps laid out in [link](setting-up-daq-pc.md#setup-network).&#x20;

### Configuration Files

In the `config` folder, you can find the configuration files for the different configurations. Several configurations are provided as examples.

* `udp_config.json`: Configuration for the UDP communication. Including the IP addresses and ports for the different KCUs and the PC.
* `h2gcroc_1v4_r1.json`: Configuration for the H2GCROC registers. **Users should not modify this file**.
* `Example_config.json`: Example I2C configuration for testing the application.

After the first run, a `config.ini` file will be created in the same folder as the application. This file stores the last configuration used by the user. Deleting this file will reset the configuration to the default one.

For a brand new start of the setup please load the configurations&#x20;

* `config_a0.json` for `asic 0`
* `config_a1.json` for `asic 1`&#x20;

You can either do this by pressing `Send Current ASIC Config`  for a single asic or by `Send All Config` for all asics. After reconfiguring the asic using the configuration tool it should be checked that the the data lines and trigger lines have reasonable values using `vivado` for every asic (press `play` and check the values).

### Manual modifications of Configuration values <a href="#user-content-license" id="user-content-license"></a>

The HGCROC has a very large number of configuration parameters and consequently registers which can and/or have to be set. A detailed description of those to the best current knowledge can be found in:

{% file src="../.gitbook/assets/H2GCROC3_datasheet_1_4.pdf" %}

Nearly all of them can be adjusted using the H2GConfig gui in its various tabs which can be accessed via the side panel.

<figure><img src="../.gitbook/assets/SidePanel.png" alt="" width="55"><figcaption></figcaption></figure>

Below you find examples of each of the individual register panels, clicking on any of the bit fields will change the bit (0->1 or vice versa) so be careful when clicking randomly in the various positions.&#x20;

<div data-full-width="false"><figure><img src="../.gitbook/assets/TopHalfRegister.png" alt="" width="188"><figcaption></figcaption></figure> <figure><img src="../.gitbook/assets/GlobalAnalog_1_Register.png" alt="" width="188"><figcaption></figcaption></figure> <figure><img src="../.gitbook/assets/ReferenceVoltage.png" alt="" width="188"><figcaption></figcaption></figure> <figure><img src="../.gitbook/assets/MasterTDC1Register.png" alt="" width="188"><figcaption></figcaption></figure> <figure><img src="../.gitbook/assets/DigitalHalf1.png" alt="" width="188"><figcaption></figcaption></figure> <figure><img src="../.gitbook/assets/Halfwise1Register.png" alt="" width="188"><figcaption></figcaption></figure> <figure><img src="../.gitbook/assets/Calib1Register.png" alt="" width="188"><figcaption></figcaption></figure> <figure><img src="../.gitbook/assets/Channel36Register.png" alt="" width="188"><figcaption></figcaption></figure> <figure><img src="../.gitbook/assets/CM_2_register.png" alt="" width="188"><figcaption></figcaption></figure></div>

In order to correctly position the maximum of the signal with respect to the trigger signal you might need to touch the `L1_offset` bits, they can be found under `Digital_Half_0` & `Digital_Half_1`  remember to change them for all necessary ½ chips. The `L1_offset` is an 8bit number increasing the least  significant bit by 1 will shift the waveform to the right by 1 sample.&#x20;

## HGCROC calibration procedure

For the HGCROC there are 4 main calibration steps:

1. **IODelay scan:** Although this isn't really a calibration you'll need to run it everytime you reconfigured the asic (otherwise you data might be nonesense)
2. **Pedestal Calibration:** Determines where the minimum `ADC` value without any signal should be situated (recommended value `80`)
3. **ToA Calibration:** Determines at which threshold value equivalent the _Time of Arrival (ToA)_ is fired (rising edge). ATTENTION: The value we are setting here is given as `injection DAC` (Digital-to-Analog-Converter) which is not equivalent to the `ADC` value referred to during the pedestal calibration. The actual conversion factor between those depends on the SiPM type.&#x20;
4. **ToT Calibration:** Determines at which threshold value equivalent the _Time over Threshold (ToT)_ is fired (falling edge). Once more the settable value is  the `injection DAC` value no the `ADC` value.&#x20;

After these calibrations have been run the **2.5V Internal Injection** test should be run ideally for all channels to validate the thresholds also in `ADC` equivalent. These test however take very long (\~8min/4 channels) and it might not be advisable to run during a test beam setting.

<div><figure><img src="../.gitbook/assets/Screenshot at 2025-11-07 11-34-11.png" alt="" width="266"><figcaption></figcaption></figure> <figure><img src="../.gitbook/assets/Screenshot at 2025-11-07 11-35-17.png" alt="" width="375"><figcaption></figcaption></figure></div>

### Calibration Gui

It is highly recommended to run the `100_UI.py` script first. This script provides a user interface for selecting the calibration files and setting various parameters for the calibration process.

**Always start 101\_SocketPool before running any other script.** This script will forward the UDP packets from the H2GCROC3B to the calibration scripts. It is essential for the calibration process to function correctly.

In the FPGA tab, you can do the IODelay setting, pedestal calibration, ToA calibration, and ToT calibration.

* Config Folder: This is the json file that specifies the UDP address and port of the KCU system.

### Calibration Scripts Overview <a href="#user-content-calibration-scripts-overview" id="user-content-calibration-scripts-overview"></a>

<figure><img src="../.gitbook/assets/Screenshot at 2025-11-07 11-48-32 (1).png" alt=""><figcaption></figcaption></figure>

