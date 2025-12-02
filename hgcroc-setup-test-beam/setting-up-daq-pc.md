---
description: This page describes the general setup need for the DAQ PC
---

# Setting up DAQ PC

## Software installation

You will need the following software installed

* **root**, either install it [manually ](https://root.cern/install/)or with the corresponding package manager of your distribution if available. Keep in mind you might need the developer packages too.
* **vivado**: fpga programming software [link](https://www.xilinx.com/support/download.html)
* **python3**
* **H2GConfig:** Python based standalone hgcroc configuration software courtesy of Shihai Jia
  * 1G Software [link](https://gitlab.cern.ch/sjia/H2GConfig)&#x20;
  * 10G Software [link](https://gitlab.cern.ch/fbock/H2GConfig/-/tree/10GBNorbertdevel?ref_type=heads) check out branch `10GNorbertdevel`
* **H2GCalib\_3b**:  Python based standalone hgcroc calibration software courtesy of Shihai Jia [l](https://gitlab.cern.ch/sjia/h2gcalib_3b)
  * 1G Software [link](https://gitlab.cern.ch/sjia/h2gcalib_3b)
  * Old 1G Software adapted to 10G [link](https://gitlab.cern.ch/fbock/h2gcalib_3b/-/tree/10GNorbertDevel?ref_type=heads) checkout branch `10GNorbertdevel`
  * New 10G Software [link](https://gitlab.cern.ch/sjia/h2gcalibx)
* **H2GDAQ:** Python based standalone DAQ software courtesy of Shihai Jia
  * 1G Software [link](https://gitlab.cern.ch/sjia/H2GDAQ/-/tree/dev-0v12?ref_type=heads) check out branch `dev-012`
  * 10G Software [link](https://gitlab.cern.ch/fbock/H2GDAQ) check out branch `main`&#x20;
* **h2g\_online\_monitoring:** C++ based online monitoring software (which can be automatically started from H2GDAQ) courtesy of Tristan Protzman [link](https://github.com/tlprotzman/h2g_online_monitoring)
* **h2g\_decode**: C++ based data stream decoder courtesy of Tristan Protzman [link](https://github.com/tlprotzman/h2g_decode/)

Keep in mind some of these packages might need further dependencies and or compilation. Have a look at their respective installation instructions or README's.

## Setup network

The firmware of the KCU and thus HGCROC boards by default expects to be situated in the subnet 10.1.2.XXX, see below how to setup the corresponding subnet on the `enp1s0f0`as an example.&#x20;

```shellscript
# -> check which routes are set: (as super user)
ip addr
ip addr show
ip route
ip route show
ip link

# show device specifications (ORNL examples)
ethtool enp1s0f1
ethtool enp1s0f0
ethtool enp3s0f1
ethtool enp3s0f0

# add new ip address for device:
ip addr add 10.1.2.207/24 dev enp1s0f0
# test if reachable:
ping 10.1.2.207
ping 8.8.8.8 # local host
ping 10.1.2.208 -s 32 # needs KCU to be programmed to respond (expected address for KCU by default)

## display the IPv4 network neighbour cache
arp -a


```

For the CERN 2025 PS TB please set up the network as follows should we need a restart of the DAQ computer. Two blue (CAT7 ethernet) cables should be connected to the 2 KCUs and the two port 10GB ethernet card in the DAQ computer.

```shellscript
# connect only FPGA1 - UCR01 & UCR02
sudo ip addr add 10.1.2.207/32 dev enp8s0f0
sudo ip route add 10.1.2.208 via 10.1.2.207 dev enp8s0f0
# programm FPGA1 in vivado
# check you can ping 10.1.2.208
ping 10.1.2.208 -s 32

# connect FPGA3 - GSU01 & ANL01
sudo ip addr add 10.1.2.206/32 dev enp8s0f1
sudo ip route add 10.1.2.209 via 10.1.2.206 dev enp8s0f1
# programm FPGA3 in vivado
# check you can ping 10.1.2.209
ping 10.1.2.209 -s 32

ip route show
## output should look like:
 default via 128.141.219.1 dev eno1 proto dhcp src 128.141.219.87 metric 100
 10.1.2.0/24 dev enp8s0f0 proto kernel scope link src 10.1.2.207
 10.1.2.0/24 dev enp8s0f1 proto kernel scope link src 10.1.2.206
 10.1.2.208 via 10.1.2.207 dev enp8s0f0
 10.1.2.209 via 10.1.2.206 dev enp8s0f1
 128.141.219.0/24 dev eno1 proto kernel scope link src 128.141.219.87 metric 100
 192.168.0.0/24 dev eno1 proto kernel scope link src 192.168.0.100 metric 100
```

Moreover it is necessary to at least make the following temporary network changes to your linux system.

```bash
#temporary network changes:
sudo sysctl -w net.core.rmem_max=8388608
sudo sysctl -w net.core.wmem_max=8388608
sudo sysctl -w net.core.rmem_default=8388608
sudo sysctl -w net.core.wmem_default=8388608

sudo sysctl -w net.core.netdev_max_backlog=250000
sudo sysctl -w net.ipv4.udp_mem='8388608 8388608 8388608'
sudo sysctl -w net.ipv4.udp_rmem_min=16384
sudo sysctl -w net.ipv4.udp_wmem_min=16384
```

They can also be made permanent by editing `/etc/sysctl.conf` and adding the following lines:

```bash
net.core.rmem_max=8388608
net.core.wmem_max=8388608
net.core.rmem_default=8388608
net.core.wmem_default=8388608

net.core.netdev_max_backlog=250000
net.ipv4.udp_mem=8388608 8388608 8388608
net.ipv4.udp_rmem_min=16384
net.ipv4.udp_wmem_min=16384
```

Then run the following command to apply the changes:

```bash
sudo sysctl -p
```

## Setup python environment

Often the latest linux distributions don't allow the system wide installation of different python versions or modules in order not to break any of the system installations. Hence a temporary python environment needs to be created, which can be pulled up with the necessary packages installed.&#x20;

```bash
# install venv
sudo apt update
sudo apt install python3-venv
    
# navigate to the project directory 
cd /home/localadmin/Software/HGCROC/

# create virtual environment 
python3 -m venv hgcroc_env

# activate correct HGCROC python environment
source /home/localadmin/Software/HGCROC/hgcroc_env/bin/activate

# install desired packages
pip install package_name

#exit python environment
deactivate

```
