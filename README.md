---
cover: .gitbook/assets/setuptowardsbeam.jpg
coverY: 0
---

# Welcome to the LFHCal TB tutorial

This page is meant to make you familiar with the setup of the LFHCal test beams executed during the last years, prepare you for upcoming test beams in terms of setting up the HGCROC readout as well as allowing you to simulate our test beam geometry using the central epic-software framework.&#x20;

This page is divided in multiple sections:

* [HGCROC SETUP - TEST BEAM ](/broken/pages/YtqvmLvUD5ngWnNasHcv):
  * This section walks you through how to setup the [HGCROC-protoboards ](hgcroc-setup-test-beam/setting-up-the-hgcroc-board.md)and the [DAQ computer](hgcroc-setup-test-beam/setting-up-daq-pc.md). Moreover, it explains how to [setup and calibrate the HGCROC](hgcroc-setup-test-beam/getting-started-hgcroc-and-calibrations.md) prior to data taking and explains how to [take data](hgcroc-setup-test-beam/data-taking-hgcroc.md) using this setup. Last but not least it gives an introduction on how to [convert the HGCROC data to a root](hgcroc-setup-test-beam/data-decoding-10g.md) readable format in a standalone way.
* [TB ANALYSIS BASICS](/broken/pages/QntfzDcWOqSAWbLKM9A4):
  * This section gives an overview where to find the TB-analysis package and how to install it [(link)](tb-analysis-basics/). It explains how to [get access to the data](tb-analysis-basics/getting-the-data.md) from the different campaigns, their initial data format and [how to convert](tb-analysis-basics/converting-the-data.md) it to a root readable format compatible with the analysis software laid out in the following sections. Moreover, it explains how the electronics channel numbering relates to the physical space and how to [build the nessesary mapping files](tb-analysis-basics/creating-a-mapping-file.md) to do this correctly.
* [CALIBRATION](/broken/pages/CAnj9Dsru8iix78DwHHa)
  *   The calibration section explains the process necessary to get from raw TB data to a calibrated output which can be used for physics performance studies. The current steps described are:

      * The [pedestal extraction](calibration/pedestal-extraction.md)
      * The [TOA Phase extraction](calibration/toa-phase-extraction.md) (HGCROC data only)
      * The [MIP calibration](calibration/mip-calibration.md)

      It is also explained how the corresponding calibrations are then applied to the data ([link](calibration/apply-calibrations.md)).&#x20;
* [DATA ANALYSIS](/broken/pages/S6yc9wk0jkNJlgKY8fkx)
  * This sections explains the initial software prepared for the [basic QA of the data](data-analysis/basic-qa-of-calibrated-data.md) as well as a very simple version of an [event display](data-analysis/simple-event-display.md).
* [COMPARISONS](/broken/pages/CfMEDSiyRKOVL6VDH1M2)
  * This section explains the initial software prepared to do comparisons of multiple runs regarding their calibration objects as well as initial data content [(link)](comparisons/compare-calibrations.md).&#x20;
* [TB SIMULATIONS](/broken/pages/g657JDQuqh4UgQDTXs5E)
  * This section is meant to explain how to setup the simulation of the TB geometry and emulate the respective readout versions. It is currently significantly under construction.&#x20;
* [OLDER SOFTWARE](/broken/pages/dErNGsOG0QTgwVcptcfU)
  * In this section the initial software for the analysis prior to 2024 is described, which might serve as basis for some extensions regarding the single photon peak extraction for instance. &#x20;

