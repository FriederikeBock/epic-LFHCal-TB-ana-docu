# ToA Phase extraction

The HGCROC in the mode we are using provides can be pieced together as a waveform which contains `n` samples for `ADC, TOA` and  `TOT`, respectively. While the `ADC` will always contain a value (i.e the pedestal) the `TOA` and `TOT` values will only be filled when a certain threshold is surpassed. That value is configurable and is set in the online calibration on a channel by channel basis. Below you see an example waveform:

```
#Waveform data format:
S.Nr   0    1    2    3    4    5    6    7    8    9    10
ADC    80   80   80   150  800  120  100  80   80   80   80     
TOA    0    0    0    0    50   0    0    0    0    0    0
TOT    0    0    0    0    0    500  0    0    0    0    0    
```

<figure><img src="../.gitbook/assets/Screenshot at 2025-11-07 11-34-11.png" alt="" width="399"><figcaption></figcaption></figure>

One sample reflects a 25 ns wide evaluation intervals. Both ToA and ADC are 10bit numbers and are evaluated in the same 25 ns interval. This means in an ideal case a delta\_toa of 1 reflects a real time difference of `25ns/1024 = 24.4ps.` Unfortunately this isn't entirely true in reality and we would need to run a full fledged TOA calibration as described in the following presentation by one of our CMS colleagues, in order to have them truely reflecting the same width.&#x20;

{% file src="../.gitbook/assets/ToA_HGCAL_DPG27Mar24.pdf" %}

For now we don't plan to implement this calibration as we aren't planning to use the ToA for physics analysis in the near term future. However, knowing when a minimum threshold was surpassed allows to improve the knowledge of actual waveform to a finer granularity than is provided by the 25ns samples. Hence we need to understand the `TOA` response nonetheless to first order.

A TOA value should be written to the next sample after the threshold had been surpassed. However, it is sampled of a 160MHz clock, which is derived from our 40 MHz clock. This clocks might not be fully aligned and could have 4 different phases, which can vary for each half of the HGCROC chip.&#x20;
