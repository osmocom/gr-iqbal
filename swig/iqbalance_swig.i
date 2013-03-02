/* -*- c++ -*- */

#define IQBALANCE_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "iqbalance_swig_doc.i"


%{
#include "iqbalance_fix_cc.h"
#include "iqbalance_optimize_c.h"
%}

GR_SWIG_BLOCK_MAGIC(iqbalance,fix_cc);
%include "iqbalance_fix_cc.h"

GR_SWIG_BLOCK_MAGIC(iqbalance,optimize_c);
%include "iqbalance_optimize_c.h"
