# Readme for Chelpis project: GPIO signaling for Side-Channel-Attack (SCA) 

This branch (`proj/sca`) is based on [tpm2-tss release 4.1.0](https://github.com/tpm2-software/tpm2-tss/releases/tag/4.1.0) (2024-04-26).

Chelpis provide modifications to stock TSS such that timings of sensitive TPM actions are easier located.

GPIO signals are provided on dedicated pins to indicate the following status: [(rpi pin definitions)](https://www.raspberrypi.com/documentation/computers/raspberry-pi.html)

- GPIO 17 - TSS enabled
- GPIO 27 - operations on TSS context file
- GPIO 22 - operations on secret

GPIO signals can be observed using LEDs, or wired to other equipmenets for more advanced usages.

Stock `tpm2-tools` will be built, installed and directly executed from shell to drive this (moded) TSS and all lower-level components.

## Interested crypto operations

- key generation
- signing (w/ private key)

## Interested algorithms

- RSA2048
- P256

# Setup

We develop & test on [raspberry pi 4b](https://www.raspberrypi.com/products/raspberry-pi-4-model-b/) together with [Infineon OPTIGA TPM2 evaluation board for rpi](https://www.infineon.com/cms/en/product/evaluation-boards/optiga-tpm-9672-rpi-eval/)

Simple LEDs are 

## Hardware Setup

Please refer to chapter 3 of [OPTIGA TPM RPi Quickstarter User Guide](https://www.infineon.com/dgdl/Infineon-Optiga_TPM_RPi_Quickstarter_User_Guide-UserManual-v01_00-EN.pdf?fileId=8ac78c8c8e7ead30018ee5a4d85b04bd&da=t)

## OS and Driver Setup

Please refer to chapter 4 of [OPTIGA TPM RPi Quickstarter User Guide](https://www.infineon.com/dgdl/Infineon-Optiga_TPM_RPi_Quickstarter_User_Guide-UserManual-v01_00-EN.pdf?fileId=8ac78c8c8e7ead30018ee5a4d85b04bd&da=t)

Chelpis actually uses Raspberry Pi OS Lite (64-bit, 2024-03-15).

## Software Setup

### Install build dependencies

```
sudo apt update
sudo apt install autoconf-archive libcmocka0 libcmocka-dev procps iproute2 build-essential git pkg-config gcc libtool automake libssl-dev uthash-dev autoconf doxygen libjson-c-dev libini-config-dev libcurl4-openssl-dev uuid-dev libltdl-dev libusb-1.0-0-dev libftdi-dev
```

### Install pigpio

[pigpio](https://github.com/joan2937/pigpio) is a C library for the Raspberry which allows control of the General Purpose Input Outputs (GPIO).

```
wget https://github.com/joan2937/pigpio/archive/master.zip
unzip master.zip
cd pigpio-master
make
sudo make install
```

### Install moded TSS

We will build from source and install softwares for this project.

```
git clone -b proj/sca --depth 1 git@github.com:chelpis/tpm2-tss.git
cd tpm2-tss
./bootstrap
./configure --enable-static=no --enable-fapi=no --disable-tcti-mssim --disable-tcti-swtpm --disable-tcti-libtpms --disable-doxygen-doc
make -j4
sudo make install
sudo ldconfig
```

### Install tpm2-tools

```
git clone -b 5.7 --depth 1 git@github.com:tpm2-software/tpm2-tools.git
cd tpm2-tss
./bootstrap
./configure --disable-unit --disable-fapi
make -j4
sudo make install
```
