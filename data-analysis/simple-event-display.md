---
description: Overview of how to run a simple event display.
---

# Simple Event display

## CAEN data

The main program to run a basic event diplay is the `./Display`. It produces a 3D plot showing the energy depositions in the 2024 test beam geometry, with the sizes and colors corresponding to the bins' contents. It can be run be run either over a particular event in the given run, or a range. It can only be run on calibrated data, otherwise all bins will be filled with `0`.

Sometimes, if run over more than 100 events, the colors are not assigned - to be debugged, the problem doesn't appear when run over a signle event.

Following options are implemented:

* common with the rest of the macros:
  * \`-d\` : switch to debug info with debug level 0 to n
  * \`-F\` : set plot extention expliticly, default is pdf
  * \`-i\` : input file in root format,
  * \`-P\` : plots directory path,
  * \`-r\` : name of run list file,
  * \`-y\` : setting year externally,
* specific for the event display:
  * &#x20;\`-e\` : setting event number to plot, default 0,
  * \`-N\` : setting number of events to plot, default 1,
  * \`-M\` : plot only muon triggered events (in the given range)

Example of how to run it:

```
./Display -d 1 -i $INPUT_FILE -r $RUN_LIST -P $PLOT_DIR -e 5 [-N 10 -M]
```

The primary script implemented for the event display is `runEventDisplay_2024.sh`:

<figure><img src="/broken/files/wjerIFNp1sFEGptb9wrN" alt=""><figcaption></figcaption></figure>

<figure><img src="/broken/files/aI13wj2e1l1n4Zlm5NTS" alt=""><figcaption></figcaption></figure>

<figure><img src="/broken/files/6RTs5NXdchXLTPVLrWsy" alt=""><figcaption></figcaption></figure>

<figure><img src="/broken/files/H5CR46lXAJLNBO4wqSfX" alt=""><figcaption></figcaption></figure>

<figure><img src="/broken/files/Eyqhr5NUFBpyCtcPeNhN" alt=""><figcaption></figcaption></figure>

```
bash runEventDisplay_2024.sh $USERNAME $BEAM_TYPE $EVENT_NUMBER $HOW_MANY_EVENTS [muonTrig]
```

where: `$BEAM_TYPE` can be `muon`, `electron`, `hadron.`

Alternative views with projections in `X,Y` and `Z` are also provided:

<div><figure><img src="../.gitbook/assets/EventDisplay_Colored_evt000031.png" alt=""><figcaption></figcaption></figure> <figure><img src="../.gitbook/assets/EventDisplay_MonoChrome_evt000031.png" alt=""><figcaption></figcaption></figure> <figure><img src="../.gitbook/assets/EventDisplay_muonHighlighed_evt000031.png" alt=""><figcaption></figcaption></figure></div>
