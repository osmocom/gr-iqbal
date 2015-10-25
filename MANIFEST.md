title: gr-iqbalance
brief: GNU Radio block to correct IQ imbalance in quadrature receivers
tags:
    - iq imbalance
    - rx
    - osmocom
author:
    - Sylvain Munaut <tnt@246tNt.com>
copyright_owner:
    - Sylvain Munaut <tnt@246tNt.com>
license: GPLv3
repo: git://git.osmocom.org/gr-iqbal
icon: http://people.osmocom.org/~tnt/stuff/iqbal-icon.png
---
GNU Radio block to correct IQ imbalance in quadrature receivers

It's composed of two main block:
 - *fix* : Given a phase and amplitude error, it will correct a complex signal
 - *optimize*: Attempts to auto-detect the phase and amplitude error to feed to
   the fix block above

The gr-osmosdr driver can make use of this block automatically if gr-iqbalance
is installed prior to gr-osmosdr.
