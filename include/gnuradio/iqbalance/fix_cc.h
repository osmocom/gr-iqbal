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

    class IQBALANCE_API fix_cc : public gr::sync_block
    {
     private:
      fix_cc(float mag, float phase);

      float d_mag, d_phase;

     public:
      typedef std::shared_ptr<fix_cc> sptr;

      static sptr make(float mag=0.0f, float phase=0.0f);

      ~fix_cc();

      void set_mag(float mag) { this->d_mag = mag; }
      void set_phase(float phase) { this->d_phase = phase; }

      float mag() const { return this->d_mag; }
      float phase() const { return this->d_phase; }

      void apply_new_corrections (pmt::pmt_t msg);

      int work (int noutput_items,
                gr_vector_const_void_star &input_items,
                gr_vector_void_star &output_items);
    };

  } // namespace iqbalance
} // namespace gr
