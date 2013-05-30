/* -*- c++ -*- */

#define IQBALANCE_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "iqbalance_swig_doc.i"


%{
#include "gnuradio/iqbalance/fix_cc.h"
#include "gnuradio/iqbalance/optimize_c.h"
%}

%include "gnuradio/iqbalance/fix_cc.h"
GR_SWIG_BLOCK_MAGIC2(iqbalance, fix_cc);

%include "gnuradio/iqbalance/optimize_c.h"
GR_SWIG_BLOCK_MAGIC2(iqbalance, optimize_c);
