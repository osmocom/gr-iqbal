# Copyright 2011-2020 Free Software Foundation, Inc.
# Copyright 2013-2021 Sylvain Munaut <tnt@246tNt.com>
#
# This file is part of gr-iqbalance
#
# SPDX-License-Identifier: GPL-3.0-or-later

########################################################################
# Install public header files
########################################################################
install(FILES
    api.h
    fix_cc.h
    optimize_c.h
    DESTINATION include/gnuradio/iqbalance
)
