/*
 * Copyright 2011-2020 Free Software Foundation, Inc.
 * Copyright 2013-2021 Sylvain Munaut <tnt@246tNt.com>
 *
 * This file is part of gr-iqbalance
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include <gnuradio/attributes.h>

#ifdef gnuradio_iqbalance_EXPORTS
#  define IQBALANCE_API __GR_ATTR_EXPORT
#else
#  define IQBALANCE_API __GR_ATTR_IMPORT
#endif
