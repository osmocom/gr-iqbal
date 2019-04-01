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

#ifndef INCLUDED_IQBALANCE_OPTIMIZE_C_H
#define INCLUDED_IQBALANCE_OPTIMIZE_C_H

#include "api.h"
#include <gnuradio/sync_block.h>

namespace gr {
  namespace iqbalance {

    /*!
     * \brief <+description of block+>
     * \ingroup iqbalance
     *
     */
    class IQBALANCE_API optimize_c : virtual public gr::sync_block
    {
    protected:
        int d_period, d_count;
        bool d_first;
        float d_mag, d_phase;

        optimize_c(int period, int count, bool first, float mag, float phase): d_period(period), d_count(count),
                                                                               d_first(first),
                                                                               d_mag(mag), d_phase(phase) {}
     public:

        typedef boost::shared_ptr<optimize_c> sptr;

        /*!
        * \brief Return a shared_ptr to a new instance of iqbalance::optimize_c.
        *
        * To avoid accidental use of raw pointers, iqbalance::optimize_c's
        * constructor is in a private implementation
        * class. iqbalance::optimize_c::make is the public interface for
        * creating new instances.
        */
        static sptr make(int period=0);

        void set_period(int period) { this->d_period = period; }
        int period() const { return this->d_period; }

        float mag() const { return this->d_mag; }
        float phase() const { return this->d_phase; }

        void reset(void) {
            this->d_first = true;
            this->d_count = 0;
            this->d_mag = this->d_phase = 0.0f;
        }
    };

  } // namespace iqbalance
} // namespace gr

#endif /* INCLUDED_IQBALANCE_OPTIMIZE_C_H */

