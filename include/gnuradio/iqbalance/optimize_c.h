/* -*- c++ -*- */
/*
 * Copyright 2011-2020 Free Software Foundation, Inc.
 * Copyright 2013-2021 Sylvain Munaut <tnt@246tNt.com>
 *
 * This file is part of gr-iqbalance
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include <gnuradio/iqbalance/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace iqbalance {

    class IQBALANCE_API optimize_c : public gr::sync_block
    {
     private:
      optimize_c(int period);

      int d_period, d_count;
      bool d_first;
      float d_mag, d_phase;

     public:
      typedef boost::shared_ptr<optimize_c> sptr;

      static sptr make(int period=0);

      ~optimize_c();

      void set_period(int period) { this->d_period = period; }
      int period() const { return this->d_period; }

      float mag() const { return this->d_mag; }
      float phase() const { return this->d_phase; }

      void reset(void) {
    	this->d_first = true;
    	this->d_count = 0;
    	this->d_mag = this->d_phase = 0.0f;
      }

      void forecast (int noutput_items, gr_vector_int &ninput_items_required);

      int work (int noutput_items,
                gr_vector_const_void_star &input_items,
                gr_vector_void_star &output_items);
    };

  } // namespace iqbalance
} // namespace gr
