# Trigger Setup and controls

<div><figure><img src="../.gitbook/assets/Trigger/P7010033.JPG" alt=""><figcaption></figcaption></figure> <figure><img src="../.gitbook/assets/Trigger/P7010073.JPG" alt=""><figcaption></figcaption></figure></div>

The triggers are SiPM based and directly coupled to 1cm x 10cm or 10cm x 20cm plastic scintillator plates wrapped in ESR foil and encased in a 3D printed casing. The SiPMs are S13360-3025PE, with a Vbr of approximately 52V.

<div><figure><img src="../.gitbook/assets/Trigger/rn_image_picker_lib_temp_a549b3ff-1eb0-4d8a-8da7-d24ed87c131d.jpg" alt=""><figcaption></figcaption></figure> <figure><img src="../.gitbook/assets/Trigger/rn_image_picker_lib_temp_b6c858d0-bb7e-4649-b5b4-fc332c0951a3.jpg" alt=""><figcaption></figcaption></figure></div>

All of the triggers should work reasonably well with a -100mV threshold, except one which should be operated at about 50mV (as indicated on the tape).

The 3 cables attached to the detector should be cables as follows:

* 2 pins for HV (black ground, and other one is +HV)
* The 3 pin cable is +5V (red), gnd (black) and -5V (blue cable with green plug)
* The lemo cable can go directly into a nim discriminator

The +5V does not need to be exact, while the -5V should really be -5V or slightly more.

A first efficiency analysis has been performed for the triggers based on the 2026 April LFHCal test beam.

<div><figure><img src="../.gitbook/assets/Trigger/image-3.png" alt=""><figcaption></figcaption></figure> <figure><img src="../.gitbook/assets/Trigger/image-4.png" alt=""><figcaption></figcaption></figure></div>

You can control the trigger SiPM bias with the following Keithley link: [http://128.141.151.107/](http://128.141.151.107/). Same user name and password as for the other one.

For controlling the dead time and trigger logic have a look [here](http://focaltrigger.cern.ch:8000/). This is only for experts!
