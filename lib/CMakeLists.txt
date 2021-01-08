# Copyright 2011-2020 Free Software Foundation, Inc.
# Copyright 2013-2021 Sylvain Munaut <tnt@246tNt.com>
#
# This file is part of gr-iqbalance
#
# SPDX-License-Identifier: GPL-3.0-or-later

########################################################################
# Setup library
########################################################################
include(GrPlatform) #define LIB_SUFFIX

list(APPEND iqbalance_sources
     fix_cc.cc
     optimize_c.cc
)

add_library(gnuradio-iqbalance SHARED ${iqbalance_sources} ${LIBOSMODSP_SEL_SOURCES})
target_link_libraries(gnuradio-iqbalance gnuradio::gnuradio-runtime ${LIBOSMODSP_SEL_LIBRARIES})
target_include_directories(gnuradio-iqbalance
    PRIVATE ${LIBOSMODSP_SEL_INCLUDE_DIRS}
    PUBLIC ${Boost_INCLUDE_DIRS}
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
    PUBLIC $<INSTALL_INTERFACE:include>
  )
set_target_properties(gnuradio-iqbalance PROPERTIES DEFINE_SYMBOL "gnuradio_iqbalance_EXPORTS")

if(APPLE)
    set_target_properties(gnuradio-iqbalance PROPERTIES
        INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/lib"
    )
endif(APPLE)

########################################################################
# Install built library files
########################################################################
include(GrMiscUtils)
GR_LIBRARY_FOO(gnuradio-iqbalance)

########################################################################
# Print summary
########################################################################
message(STATUS "Using install prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "Building for version: ${VERSION} / ${LIBVER}")

########################################################################
# Build and register unit test
########################################################################
include(GrTest)

# If your unit tests require special include paths, add them here
#include_directories()
# List all files that contain Boost.UTF unit tests here
list(APPEND iqbalance_test_sources
)
# Anything we need to link to for the unit tests go here
list(APPEND GR_TEST_TARGET_DEPS gnuradio-test)

if(NOT iqbalance_test_sources)
    MESSAGE(STATUS "No C++ unit tests... skipping")
    return()
endif(NOT iqbalance_test_sources)

foreach(qa_file ${iqbalance_test_sources})
    GR_ADD_CPP_TEST("test_${qa_file}"
        ${CMAKE_CURRENT_SOURCE_DIR}/${qa_file}
    )
endforeach(qa_file)
