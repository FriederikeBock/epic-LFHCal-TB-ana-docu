---
description: Features and things you need to know about the various beam lines
---

# Beam line specifics

## SPS H2 beam line

<div><figure><img src="../.gitbook/assets/WhatsApp Image 2026-05-13 at 14.12.51.jpeg" alt=""><figcaption><p>Patch-panel location in H2 area.</p></figcaption></figure> <figure><img src="../.gitbook/assets/rn_image_picker_lib_temp_f1a86c9a-a787-4d51-bad7-8b833c46c716.jpg" alt=""><figcaption><p>Patch-panel in H2 control room (HN383) to TB area.</p></figcaption></figure> <figure><img src="../.gitbook/assets/rn_image_picker_lib_temp_ccdc73c8-03aa-4b4e-9d69-3ce5dee5042e.jpg" alt=""><figcaption><p>Patch-panel to CCC (for beam tuning)</p></figcaption></figure></div>

See above for patch panel locations, left most patch panel picture shows patch-panel to CCC for Bastien/Nicos.&#x20;

### Nikhef stage

Nikhef stage can only be steered from down stairs moving panel, locations can be retrieved via raspberry-Pi `ssh -Y pi@h2raspitablepos` (ask Fredi/Oskar for password).&#x20;

Go to `~/H2_LaserDisto`  there are several scripts. Oskar wrote a new version of the position display for us which takes the offsets into account. This can be run with:&#x20;

{% code overflow="wrap" %}
```bash
#Center position for 2026 LFHCal TB : offset x (horizontal) = 1.298, offset Y (vertical) = 0.853
python3 laser_monitor_dual_mod.py --offsetH 1.298 --offsetV 0.853
```
{% endcode %}

Then move the stage and watch were it goes.
