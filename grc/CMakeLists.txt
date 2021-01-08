# Copyright 2011-2020 Free Software Foundation, Inc.
# Copyright 2013-2021 Sylvain Munaut <tnt@246tNt.com>
#
# This file is part of gr-iqbalance
#
# SPDX-License-Identifier: GPL-3.0-or-later

install(FILES
    iqbalance_fix_cc.block.yml
    iqbalance_optimize_c.block.yml
    iqbalance.tree.yml
    DESTINATION share/gnuradio/grc/blocks
)
