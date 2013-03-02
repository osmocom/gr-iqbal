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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gr_io_signature.h>
#include "iqbalance_fix_cc.h"


iqbalance_fix_cc_sptr
iqbalance_make_fix_cc (float mag, float phase)
{
	return gnuradio::get_initial_sptr (new iqbalance_fix_cc(mag, phase));
}


iqbalance_fix_cc::iqbalance_fix_cc (float mag, float phase)
  : gr_sync_block ("fix_cc",
		   gr_make_io_signature(1, 1, sizeof (gr_complex)),
		   gr_make_io_signature(1, 1, sizeof (gr_complex))),
    d_mag(mag),
    d_phase(phase)
{
	message_port_register_in(pmt::mp("iqbal_corr"));
	set_msg_handler(pmt::mp("iqbal_corr"),
			boost::bind(&iqbalance_fix_cc::apply_new_corrections, this, _1));
}


iqbalance_fix_cc::~iqbalance_fix_cc()
{
	/* Nothing to do */
}


void
iqbalance_fix_cc::apply_new_corrections (pmt::pmt_t msg)
{
	if (!pmt_is_f32vector(msg))
		return;

	this->set_mag(pmt_f32vector_ref(msg, 0));
	this->set_phase(pmt_f32vector_ref(msg, 1));
}


int
iqbalance_fix_cc::work (int noutput_items,
			gr_vector_const_void_star &input_items,
			gr_vector_void_star &output_items)
{
	const gr_complex *in = (const gr_complex *) input_items[0];
	gr_complex *out = (gr_complex *) output_items[0];
	int i;

	const float magp1 = 1.0f + this->d_mag;
	const float phase = this->d_phase;

	for (i=0; i<noutput_items; i++) {
		gr_complex v = in[i];
		out[i] = gr_complex(
			v.real() * magp1,
			v.imag() + phase * v.real()
		);
	}

	return noutput_items;
}
