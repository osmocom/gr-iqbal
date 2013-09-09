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

#include <gnuradio/io_signature.h>
#include <gnuradio/iqbalance/optimize_c.h>

#define GCC_VERSION (			\
		__GNUC__ * 10000 +	\
		__GNUC_MINOR__ * 100 +	\
		__GNUC_PATCHLEVEL__	\
	)

#if GCC_VERSION >= 40800
# define complex _Complex
# undef _GLIBCXX_HAVE_COMPLEX_H
#endif

extern "C" {
#include <osmocom/dsp/cxvec.h>
#include <osmocom/dsp/iqbal.h>
}

#define FFT_SIZE	1024
#define FFT_COUNT	4


namespace gr {

iqbalance::optimize_c::sptr
iqbalance::optimize_c::make(int period)
{
	return gnuradio::get_initial_sptr (new iqbalance::optimize_c(period));
}

iqbalance::optimize_c::optimize_c(int period)
  : gr::sync_block ("optimize_c",
		   gr::io_signature::make(1, 1, sizeof (gr_complex)),
		   gr::io_signature::make(0, 0, 0)),
    d_period(period), d_count(0), d_first(true), d_mag(0.0f), d_phase(0.0f)
{
	message_port_register_out(pmt::mp("iqbal_corr"));
}


iqbalance::optimize_c::~optimize_c()
{
	/* Nothing to do */
}


void
iqbalance::optimize_c::forecast(int noutput_items, gr_vector_int &ninput_items_required)
{
	unsigned ninputs = ninput_items_required.size ();
	for (unsigned i = 0; i < ninputs; i++)
		ninput_items_required[i] = FFT_SIZE * FFT_COUNT;
}


int
iqbalance::optimize_c::work(int noutput_items,
		  gr_vector_const_void_star &input_items,
		  gr_vector_void_star &output_items)
{
	const gr_complex *in = (const gr_complex *) input_items[0];
	const int N = FFT_SIZE * FFT_COUNT;
	struct osmo_cxvec _sig, *sig = &_sig;
	struct osmo_iqbal_opts opts;
	float p[2];

	if (!this->d_period)
		return noutput_items;

	if (this->d_count) {
		int missing = this->d_period - this->d_count;

		if (missing <= 0) {
			this->d_count = 0;
			return 0;
		} else if (missing >= noutput_items) {
			this->d_count += noutput_items;
			return noutput_items;
		} else {
			this->d_count = 0;
			return missing;
		}
	}

	if (noutput_items < N)
		return 0;

	this->d_count += N;

	memcpy(&opts, &osmo_iqbal_default_opts, sizeof(opts));
	opts.fft_size = FFT_SIZE;
	opts.fft_count = FFT_COUNT;
	opts.start_at_prev = 1;

	p[0] = this->d_mag;
	p[1] = this->d_phase;

	osmo_cxvec_init_from_data(sig, (float complex *)in, N);
	osmo_iqbal_cxvec_optimize(sig, &p[0], &p[1], &opts);

	if (this->d_first) {
		this->d_first = false;
		this->d_mag   = p[0];
		this->d_phase = p[1];
	} else {
		this->d_mag   = (0.95f * this->d_mag  ) + (p[0] * 0.05f);
		this->d_phase = (0.95f * this->d_phase) + (p[1] * 0.05f);
	}

	p[0] = this->d_mag;
	p[1] = this->d_phase;
	pmt::pmt_t msg = pmt::init_f32vector(2, p);
	message_port_pub(pmt::mp("iqbal_corr"), msg);

	return N;
}

} /* namespace gr */

