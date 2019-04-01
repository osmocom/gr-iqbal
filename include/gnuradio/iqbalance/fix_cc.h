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

#include "api.h"
#include <gnuradio/sync_block.h>

namespace gr {
  namespace iqbalance {

    /*!
     * \brief <+description of block+>
     * \ingroup iqbalance
     *
     */
    class IQBALANCE_API fix_cc : virtual public gr::sync_block
    {
    protected:
        float d_mag, d_phase;
        fix_cc(float mag, float phase): d_mag(mag), d_phase(phase) {}

    public:

        typedef boost::shared_ptr<fix_cc> sptr;

        /*!
        * \brief Return a shared_ptr to a new instance of iqbalance::fix_cc.
        *
        * To avoid accidental use of raw pointers, iqbalance::fix_cc's
        * constructor is in a private implementation
        * class. iqbalance::fix_cc::make is the public interface for
        * creating new instances.
        */
        static sptr make(float mag=0.0f, float phase=0.0f);

        void set_mag(float mag) { this->d_mag = mag; }
        void set_phase(float phase) { this->d_phase = phase; }

        float mag() const { return this->d_mag; }
        float phase() const { return this->d_phase; }
    };

  } // namespace iqbalance
} // namespace gr

#endif /* INCLUDED_IQBALANCE_FIX_CC_H */

