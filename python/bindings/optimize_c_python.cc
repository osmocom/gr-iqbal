/*
 * Copyright 2013-2021 Sylvain Munaut <tnt@246tNt.com>
 *
 * This file is part of gr-iqbalance
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <gnuradio/iqbalance/optimize_c.h>

#define D(...) ""

void bind_optimize_c(py::module& m)
{
	using optimize_c = gr::iqbalance::optimize_c;

	py::class_<optimize_c,
		gr::sync_block,
		gr::block,
		gr::basic_block,
		std::shared_ptr<optimize_c>>(m, "optimize_c", D(optimize_c))

		.def(py::init(&optimize_c::make),
			py::arg("period") = 0,
			D(optimize_c,make)
		)

		.def("set_period",
			&optimize_c::set_period,
			py::arg("period"),
			D(optimize_c,set_period)
		)

		.def("period",
			&optimize_c::period,
			D(optimize_c,period)
		)

		.def("mag",
			&optimize_c::mag,
			D(optimize_c,mag)
		)

		.def("phase",
			&optimize_c::phase,
			D(optimize_c,phase)
		)

		.def("reset",
			&optimize_c::reset,
			D(optimize_c,reset)
		)

		;
}
