/* -*- c++ -*- */
/*
 * Copyright 2019 gr-iqbalance author.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_IQBALANCE_FIX_CC_IMPL_H
#define INCLUDED_IQBALANCE_FIX_CC_IMPL_H

#include <gnuradio/iqbalance/fix_cc.h>

namespace gr {
  namespace iqbalance {

    class fix_cc_impl : public fix_cc
    {
     public:
        fix_cc_impl(float mag, float phase);

        void apply_new_corrections (pmt::pmt_t msg);

        // Where all the action really happens
        int work(int noutput_items,
                 gr_vector_const_void_star &input_items,
                 gr_vector_void_star &output_items
        );
    };

  } // namespace iqbalance
} // namespace gr

#endif /* INCLUDED_IQBALANCE_FIX_CC_IMPL_H */

