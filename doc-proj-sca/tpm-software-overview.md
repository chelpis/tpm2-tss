# TPM software overview

![tpm2-sw-diagram](https://www.intel.com/content/dam/developer/articles/technical/tpm2-software-stack-open-source/tpm2-sw-diagram-785358.jpg 'ddd')

# TPM Device Driver

[The specific driver source code](https://github.com/raspberrypi/linux/blob/rpi-6.6.y/drivers/char/tpm/tpm_tis_spi_main.c) used in this project.

# In-kernel TPM Resource Manager

[The specific RM source code](https://github.com/raspberrypi/linux/blob/rpi-6.6.y/drivers/char/tpm/tpmrm-dev.c) used in this project

TCG also provides their open source user-space TAB/RM (see difference [here](https://github.com/tpm2-software/tpm2-abrmd#tpm2-abrmd-vs-in-kernel-rm)), we do not use this because:

1. async / multi-tasking is not required
2. keep it as simple / direct as possible

# TCG TPM Software Stack (TSS)

TCG TSS includes TCTI, SAPI, ESAPI and FAPI (not needed for this project). Figures in chapter 2 of their [overview document](https://trustedcomputinggroup.org/wp-content/uploads/TSS_Overview_Common_v1_r10_pub09232021.pdf) are helpful.

## Alternatives to TCG TSS

Wikipedia listed some [notable open source TPM libraries](https://en.wikipedia.org/wiki/Trusted_Platform_Module#TPM_software_libraries). They should all talk to TAB/RM layer through provided TCTI interface.

# Application

Applications link to TSS libraries to use TPM through SAPI / ESAPI / FAPI.

Here we use TCG [tpm2-tools](https://github.com/tpm2-software/tpm2-tools). 

Please note that not all versions of tpm2-tools supports all tpm2-tss. Check out [depencency matrix](https://tpm2-software.github.io/versions/). As of 2024/05, the latest versions are tpm2-tss 4.1.0 & tpm2-tools 5.7.

## Other notable applications

Besides those provided in [depencency matrix](https://tpm2-software.github.io/versions/) on above, here are some more notable applications.

- [TCG github](https://github.com/tpm2-software/)
- [OpenSSL TPM2 provider](https://github.com/tpm2-software/tpm2-openssl)

