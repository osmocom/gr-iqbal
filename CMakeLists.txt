# Copyright 2011-2020 Free Software Foundation, Inc.
# Copyright 2013-2021 Sylvain Munaut <tnt@246tNt.com>
#
# This file is part of gr-iqbalance
#
# SPDX-License-Identifier: GPL-3.0-or-later

########################################################################
# Project setup
########################################################################
cmake_minimum_required(VERSION 3.8)
project(gr-iqbalance CXX C)
include(GNUInstallDirs)
enable_testing()

#policy setup
cmake_policy(SET CMP0011 NEW)

#select the release build type by default to get optimization flags
if(NOT CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE "Release")
   message(STATUS "Build type not specified: defaulting to release.")
endif(NOT CMAKE_BUILD_TYPE)
set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "")

########################################################################
# GNURadio setup
########################################################################
list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_SOURCE_DIR}/cmake/Modules)

# Find GNURadio
find_package(Gnuradio "3.9" REQUIRED)

# Set the version information here
set(VERSION_MAJOR 3)
set(VERSION_API   9)
set(VERSION_ABI   0)
set(VERSION_PATCH 0)
include(GrVersion) #setup version info

########################################################################
# Compiler specific setup
########################################################################
if((CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
    CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    AND NOT WIN32)
    #http://gcc.gnu.org/wiki/Visibility
    add_definitions(-fvisibility=hidden)
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_STANDARD 14)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_STANDARD 14)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_CXX_STANDARD 14)
else()
    message(WARNING "C++ standard could not be set because compiler is not GNU, Clang or MSVC.")
endif()

if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_C_STANDARD 11)
elseif(CMAKE_C_COMPILER_ID MATCHES "Clang")
    set(CMAKE_C_STANDARD 11)
elseif(CMAKE_C_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_C_STANDARD 11)
else()
    message(WARNING "C standard could not be set because compiler is not GNU, Clang or MSVC.")
endif()

########################################################################
# Find boost
########################################################################
find_package(Boost "1.65" REQUIRED system)

if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost required to compile iqbalance")
endif()

########################################################################
# Find FFTW3
########################################################################
find_package(FFTW3f)

if(NOT FFTW3f_FOUND)
    message(FATAL_ERROR "FFTW3 required to compile iqbalance")
endif()

########################################################################
# Find libosmo-dsp
########################################################################
find_package(LibOsmoDSP)

if(LIBOSMODSP_FOUND)
    set(LIBOSMODSP_SEL_INCLUDE_DIRS ${LIBOSMODSP_INCLUDE_DIRS})
    set(LIBOSMODSP_SEL_LIBRARIES ${LIBOSMODSP_LIBRARIES})
    set(LIBOSMODSP_SEL_SOURCES "")
endif()

if(NOT LIBOSMODSP_FOUND)
    message(STATUS "libosmodsp not found, using local checkout")
    set(LIBOSMODSP_SEL_INCLUDE_DIRS ${FFTW3f_INCLUDE_DIRS} "${CMAKE_CURRENT_SOURCE_DIR}/libosmo-dsp/include/")
    set(LIBOSMODSP_SEL_LIBRARIES ${FFTW3f_LIBRARIES})
    set(LIBOSMODSP_SEL_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/libosmo-dsp/src/cxvec.c ${CMAKE_CURRENT_SOURCE_DIR}/libosmo-dsp/src/iqbal.c)
endif()

########################################################################
# Install directories
########################################################################
include(GrPlatform) #define LIB_SUFFIX

if(NOT CMAKE_MODULES_DIR)
  set(CMAKE_MODULES_DIR lib${LIB_SUFFIX}/cmake)
endif(NOT CMAKE_MODULES_DIR)

set(GR_INCLUDE_DIR      include)
set(GR_CMAKE_DIR        ${CMAKE_MODULES_DIR}/gnuradio)
set(GR_PKG_DATA_DIR     ${GR_DATA_DIR}/${CMAKE_PROJECT_NAME})
set(GR_PKG_DOC_DIR      ${GR_DOC_DIR}/${CMAKE_PROJECT_NAME})
set(GR_PKG_CONF_DIR     ${GR_CONF_DIR}/${CMAKE_PROJECT_NAME}/conf.d)
set(GR_PKG_LIBEXEC_DIR  ${GR_LIBEXEC_DIR}/${CMAKE_PROJECT_NAME})

########################################################################
# On Apple only, set install name and use rpath correctly, if not already set
########################################################################
if(APPLE)
    if(NOT CMAKE_INSTALL_NAME_DIR)
        set(CMAKE_INSTALL_NAME_DIR
            ${CMAKE_INSTALL_PREFIX}/${GR_LIBRARY_DIR} CACHE
            PATH "Library Install Name Destination Directory" FORCE)
    endif(NOT CMAKE_INSTALL_NAME_DIR)
    if(NOT CMAKE_INSTALL_RPATH)
        set(CMAKE_INSTALL_RPATH
            ${CMAKE_INSTALL_PREFIX}/${GR_LIBRARY_DIR} CACHE
            PATH "Library Install RPath" FORCE)
    endif(NOT CMAKE_INSTALL_RPATH)
    if(NOT CMAKE_BUILD_WITH_INSTALL_RPATH)
        set(CMAKE_BUILD_WITH_INSTALL_RPATH ON CACHE
            BOOL "Do Build Using Library Install RPath" FORCE)
    endif(NOT CMAKE_BUILD_WITH_INSTALL_RPATH)
endif(APPLE)

########################################################################
# Find gnuradio build dependencies
########################################################################
find_package(Doxygen)

########################################################################
# PyBind11 Related
########################################################################

find_package(pybind11 REQUIRED)
execute_process(
    COMMAND "${PYTHON_EXECUTABLE}" -c
    "try:\n import numpy\n import os\n inc_path = numpy.get_include()\n if os.path.exists(os.path.join(inc_path, 'numpy', 'arrayobject.h')):\n  print(inc_path, end='')\nexcept:\n pass"
    OUTPUT_VARIABLE PYTHON_NUMPY_INCLUDE_DIR)

########################################################################
# Setup doxygen option
########################################################################
if(DOXYGEN_FOUND)
    option(ENABLE_DOXYGEN "Build docs using Doxygen" ON)
else(DOXYGEN_FOUND)
    option(ENABLE_DOXYGEN "Build docs using Doxygen" OFF)
endif(DOXYGEN_FOUND)

########################################################################
# Create uninstall target
########################################################################
configure_file(
    ${CMAKE_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake
@ONLY)

add_custom_target(uninstall
    ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake
)

########################################################################
# Add subdirectories
########################################################################
add_subdirectory(include/gnuradio/iqbalance)
add_subdirectory(lib)
add_subdirectory(apps)
add_subdirectory(docs)
add_subdirectory(python)
add_subdirectory(grc)
