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

#include <gnuradio/iqbalance/fix_cc.h>

#define D(...) ""

void bind_fix_cc(py::module& m)
{
	using fix_cc = gr::iqbalance::fix_cc;

	py::class_<fix_cc,
		gr::sync_block,
		gr::block,
		gr::basic_block,
		std::shared_ptr<fix_cc>>(m, "fix_cc", D(fix_cc))

		.def(py::init(&fix_cc::make),
			py::arg("mag") = 0.0f,
			py::arg("phase") = 0.0f,
			D(fix_cc,make)
		)

		.def("set_mag",
			&fix_cc::set_mag,
			py::arg("mag"),
			D(fix_cc,set_mag)
		)

		.def("mag",
			&fix_cc::mag,
			D(fix_cc,mag)
		)

		.def("set_phase",
			&fix_cc::set_phase,
			py::arg("phase"),
			D(fix_cc,set_phase)
		)

		.def("phase",
			&fix_cc::phase,
			D(fix_cc,phase)
		)

		;
}
