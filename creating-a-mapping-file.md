---
description: >-
  This page illustrates how you can create a new mapping file in case you are
  running with data taking in a different configuration than the 2023 or 2024
  test beams.
icon: map
cover: .gitbook/assets/mapping_CAEN_Asic0 .png
coverY: 0
---

# Creating a Mapping File

## From read-out level to proper geometry- TB 2024-CAEN example&#x20;

In order to translate the different channels in one (or multiple) CAEN readout unit(s) into physical space i.e. layer, column, row and module within our detector, we need to define a mapping file. For the 2024 TB each assembly was connected to an 8 layer connector board, which was then connected to either a CAEN DT5202 or one HGCROC on the KCU.&#x20;

<div><figure><img src=".gitbook/assets/IMG-20240828-WA0000.jpg" alt="" width="375"><figcaption><p>Connector board for 2024 test beam campaign to connect 8 assembles to one readout unit</p></figcaption></figure> <figure><img src=".gitbook/assets/IMG-20240828-WA0002.jpg" alt="" width="375"><figcaption><p>Ribbon cables to connect connector board (for 8 assemblies) and 1 readout unit (i.e. CAEN DT5202).</p></figcaption></figure></div>

A picture of the mapping of one CAEN unit to 8 physical layers can be seen below and the full picture of the mapping for the TB is displayed below as well.&#x20;

<figure><img src=".gitbook/assets/mapping_CAEN_Asic0 .png" alt=""><figcaption><p>Mapping of individual channels within the assemblies (black text) to the corresponding channels within one CAEN DT5202 readout unit (blue text) using the ribbon cables and 8 layer connector boards. </p></figcaption></figure>

<figure><img src=".gitbook/assets/mappingFullModule_CAEN.png" alt=""><figcaption><p>Mapping of all layers and channels to the 8 CAEN DT5202 readout unit used in the August 2024 PS TB.</p></figcaption></figure>

To ease the generation of the necessary mapping text file (i.e [2024TB-file](https://github.com/eic/epic-lfhcal-tbana/blob/main/configs/mappingFile_202409_CAEN.txt)) you can use the [CreateMapping.C](https://github.com/eic/epic-lfhcal-tbana/blob/main/NewStructure/CreateMapping.C) macro, as follows:

```
root -b -x -q -l 'CreateMapping.C+("../configs/mappingSingleCAENUnit.txt","../configs/layersCAEN_PSTB_2024.txt","../configs/modulePositions_2024.txt","Mapping.txt",0,0)'
```

The options in order are explained in the following, with parts of the examples from the 2024 CAEN TB.

* Definition of mapping within a single readout unit: `../configs/mappingSingleCAENUnit.txt`&#x20;

```csv
#CAEN board channel #layer in 8-stack #board channel  #row  #column
0   7   1   1   0
1   7   2   1   1
2   7   3   1   2
3   7   4   1   3
...
```

* Definition of  assignment of individual layers to different readout modules:  `../configs/layersCAEN_PSTB_2024.txt`

```csv
#layer  #assembly #CAEN board   #layer in CAEN unit # Module Number
0   C001    0 0 0
1   C002    0 1 0
2   C003    0 2 0 
3   C065    0 3 0
4   C066    0 4 0
5   C067    0 5 0
6   C070    0 6 0
7   C071    0 7 0
8   C009    1 0 0
9   C010    1 1 0
10  C011    1 2 0
...
```

* Definition of module positions, given as modules number and their centers in x and y: `../configs/modulePositions_2024.txt`

```csv
#ModuleNr #ModuleX #ModuleY
0   0   0
```

* Output file to be generated with the final mapping file:  `Mapping.txt`

```csv
#CAEN board	CAEN Ch	layer	assembly	board channel	row	column modNr modX modY
0	56	0	001	1	1	0	0	0	0
0	57	0	001	2	1	1	0	0	0
0	58	0	001	3	1	2	0	0	0
0	59	0	001	4	1	3	0	0	0
0	60	0	001	5	0	3	0	0	0
0	61	0	001	6	0	2	0	0	0
0	62	0	001	7	0	1	0	0	0
0	63	0	001	8	0	0	0	0	0
0	48	1	002	1	1	0	0	0	0
...
```

* Option to switch between labels for CAEN :`0` and HGCROC: `1` labeling
* Debug level to get more print outs for debugging: `0`-nothing, `1`-minimal, `2`-full     &#x20;



## From read-out level to proper geometry- TB 2024-HGCROC example&#x20;

This works following exactly the same example but of course the corresponding layer association files and single readout unit files have to be replaced with the HGCROC versions and correspondingly the previous to last argument has to be set to `1`  for the appropriate HGCROC labeling:

```bash
$SINGLEUNITFILE="../configs/mappingSingleHGCROCAsic_alternate.txt"
$LAYERSFILE1="../configs/layersHGCROC_PSTB2024_Run5-67.txt"    # Runs 5-67
$LAYERSFILE2="../configs/layersHGCROC_PSTB2024_Run68-117.txt"   # Runs 68-117
$LAYERSFILE3="../configs/layersHGCROC_PSTB2024_Run118-337.txt" # Runs 118-337
```

```
root -b -x -q -l 'CreateMapping.C("../configs/mappingSingleHGCROCAsic_alternate.txt","../configs/layersHGCROC_PSTB2024_Run5-67.txt","../configs/modulePositions_2024.txt","../configs/mapping_HGCROC_PSTB2024_Run5-67_alternate.txt",1,0)'
```

## Predefined mappings with their physical connector boards and readout hardware

In order to analyse any data you need to know which channel in the respective read out unit belongs to which specific channel in the physical space. As an example below the association of a single CAEN unit with the ribbon cable and the full TB using the CAEN units.&#x20;



<figure><img src=".gitbook/assets/mapping_CAEN_Asic0_withConnectorboard (1).png" alt=""><figcaption><p>Mapping of the individual channels within one assembly (black text) to one CAEN DT5202 (blue text) unit using the ribbon cables and the 8 layer connector boards from the TB in 2024.</p></figcaption></figure>

The corresponding single unit file can be found in: `configs/mappingSingleCAENUnit.txt` .

Similarly the same connector board with the HGCROC board version 1. Follows the following mapping for a single ASIC: `configs/mappingSingleHGCROCAsic_alternate.txt`&#x20;

<figure><img src=".gitbook/assets/mapping_KCU2_Asic1_Starting0109_noon_fixed_withBoards.png" alt=""><figcaption><p>Mapping of the individual channels within one assembly (black text) to one HGCROC board version 1 (blue text) unit using the ribbon cables and the 8 layer connector boards from the TB in 2024.</p></figcaption></figure>

