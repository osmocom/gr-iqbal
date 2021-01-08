/*
 * Copyright 2020-2021 Free Software Foundation, Inc.
 * Copyright 2013-2021 Sylvain Munaut <tnt@246tNt.com>
 *
 * This file is part of gr-iqbalance
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <pybind11/pybind11.h>

#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <numpy/arrayobject.h>

namespace py = pybind11;

void bind_fix_cc(py::module& m);
void bind_optimize_c(py::module& m);

// We need this hack because import_array() returns NULL
// for newer Python versions.
// This function is also necessary because it ensures access to the C API
// and removes a warning.
void* init_numpy()
{
	import_array();
	return NULL;
}

PYBIND11_MODULE(iqbalance_python, m)
{
	// Initialize the numpy C API
	// (otherwise we will see segmentation faults)
	init_numpy();

	// Allow access to base block methods
	py::module::import("gnuradio.gr");

	bind_fix_cc(m);
	bind_optimize_c(m);
}
