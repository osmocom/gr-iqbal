/* -*- c++ -*- */
/* 
 * Copyright 2013  Sylvain Munaut <tnt@246tNt.com>
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


#ifndef INCLUDED_IQBALANCE_FIX_CC_H
#define INCLUDED_IQBALANCE_FIX_CC_H

#include <iqbalance_api.h>
#include <gr_sync_block.h>

class iqbalance_fix_cc;

typedef boost::shared_ptr<iqbalance_fix_cc> iqbalance_fix_cc_sptr;

IQBALANCE_API iqbalance_fix_cc_sptr iqbalance_make_fix_cc (float mag=0.0f, float phase=0.0f);

/*!
 * \brief <+description+>
 * \ingroup block
 *
 */
class IQBALANCE_API iqbalance_fix_cc : public gr_sync_block
{
 private:
  friend IQBALANCE_API iqbalance_fix_cc_sptr iqbalance_make_fix_cc (float mag, float phase);

  iqbalance_fix_cc(float mag, float phase);

  float d_mag, d_phase;

 public:
  ~iqbalance_fix_cc();

  void set_mag(float mag) { this->d_mag = mag; }
  void set_phase(float phase) { this->d_phase = phase; }

  float mag() const { return this->d_mag; }
  float phase() const { return this->d_phase; }

  void apply_new_corrections (pmt::pmt_t msg);

  int work (int noutput_items,
            gr_vector_const_void_star &input_items,
            gr_vector_void_star &output_items);
};

#endif /* INCLUDED_IQBALANCE_FIX_CC_H */

