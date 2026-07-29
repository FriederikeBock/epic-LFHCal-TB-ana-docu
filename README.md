---
cover: .gitbook/assets/setuptowardsbeam.jpg
coverY: 0
---

# Welcome to the LFHCal TB tutorial

This page is meant to make you familiar with the setup of the LFHCal test beams executed during the last years, prepare you for upcoming test beams in terms of setting up the HGCROC readout as well as allowing you to simulate our test beam geometry using the central epic-software framework.

This page is divided in multiple sections:

* [HGCROC SETUP - TEST BEAM ](https://app.gitbook.com/s/s5C8zkGYS3GkZpbQrPK0/hgcroc-setup-test-beam):
  * This section walks you through how to setup the [HGCROC-protoboards ](hgcroc-setup-test-beam/setting-up-the-hgcroc-board.md)and the [DAQ computer](hgcroc-setup-test-beam/setting-up-daq-pc.md). Moreover, it explains how to [setup and calibrate the HGCROC](hgcroc-setup-test-beam/getting-started-hgcroc-and-calibrations.md) prior to data taking and explains how to [take data](hgcroc-setup-test-beam/data-taking-hgcroc.md) using this setup. Last but not least it gives an introduction on how to [convert the HGCROC data to a root](hgcroc-setup-test-beam/data-decoding-10g.md) readable format in a standalone way.
* [TB ANALYSIS BASICS](https://app.gitbook.com/s/s5C8zkGYS3GkZpbQrPK0/tb-analysis-basics):
  * This section gives an overview where to find the TB-analysis package and how to install it [(link)](https://github.com/FriederikeBock/epic-LFHCal-TB-ana-docu/blob/main/tb-analysis-basics/README.md). It explains how to [get access to the data](tb-analysis-basics/getting-the-data.md) from the different campaigns, their initial data format and [how to convert](tb-analysis-basics/converting-the-data.md) it to a root readable format compatible with the analysis software laid out in the following sections. Moreover, it explains how the electronics channel numbering relates to the physical space and how to [build the nessesary mapping files](tb-analysis-basics/creating-a-mapping-file.md) to do this correctly.
* [CALIBRATION](https://app.gitbook.com/s/s5C8zkGYS3GkZpbQrPK0/calibration)
  *   The calibration section explains the process necessary to get from raw TB data to a calibrated output which can be used for physics performance studies. The current steps described are:

      * The [pedestal extraction](calibration/pedestal-extraction.md)
      * The [TOA Phase extraction](calibration/toa-phase-extraction.md) (HGCROC data only)
      * The [MIP calibration](calibration/mip-calibration.md)

      It is also explained how the corresponding calibrations are then applied to the data ([link](calibration/apply-calibrations.md)).
* [DATA ANALYSIS](https://app.gitbook.com/s/s5C8zkGYS3GkZpbQrPK0/data-analysis)
  * This sections explains the initial software prepared for the [basic QA of the data](data-analysis/basic-qa-of-calibrated-data.md) as well as a very simple version of an [event display](data-analysis/simple-event-display.md).
* [COMPARISONS](https://app.gitbook.com/s/s5C8zkGYS3GkZpbQrPK0/comparisons)
  * This section explains the initial software prepared to do comparisons of multiple runs regarding their calibration objects as well as initial data content [(link)](comparisons/compare-calibrations.md).
* [TB SIMULATIONS](https://app.gitbook.com/s/s5C8zkGYS3GkZpbQrPK0/tb-simulations)
  * This section is meant to explain how to setup the simulation of the TB geometry and emulate the respective readout versions. It is currently significantly under construction.
* [OLDER SOFTWARE](https://app.gitbook.com/s/s5C8zkGYS3GkZpbQrPK0/older-software)
  * In this section the initial software for the analysis prior to 2024 is described, which might serve as basis for some extensions regarding the single photon peak extraction for instance.
