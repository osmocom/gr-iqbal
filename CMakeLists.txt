# Copyright 2011,2012 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.


########################################################################
# Project setup
########################################################################
cmake_minimum_required(VERSION 3.8)
include(GNUInstallDirs)
project(gr-iqbalance CXX C)
enable_testing()

#select the release build type by default to get optimization flags
if(NOT CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE "Release")
   message(STATUS "Build type not specified: defaulting to release.")
endif(NOT CMAKE_BUILD_TYPE)
set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "")

########################################################################
# set search path for cmake modules to OOT, Gnuradio
########################################################################
list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_SOURCE_DIR}/cmake/Modules)
find_package(Gnuradio "3.8" REQUIRED runtime)

# Set the version information here
set(VERSION_INFO_MAJOR_VERSION 3)
set(VERSION_INFO_API_COMPAT    8)
set(VERSION_INFO_MINOR_VERSION 0)
set(VERSION_INFO_MAINT_VERSION "")
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
    set(CMAKE_CXX_STANDARD 11)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_STANDARD 11)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_CXX_STANDARD 11)
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
find_package(Boost "1.67" REQUIRED system)

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
    set(LIBOSMODSP_SEL_LIBRARY_DIRS ${LIBOSMODSP_LIBRARY_DIRS})
    set(LIBOSMODSP_SEL_SOURCES "")
endif()

if(NOT LIBOSMODSP_FOUND)
    message(STATUS "libosmodsp not found, using local checkout")
    set(LIBOSMODSP_SEL_INCLUDE_DIRS ${FFTW3f_INCLUDE_DIRS} "libosmo-dsp/include/")
    set(LIBOSMODSP_SEL_LIBRARIES ${FFTW3f_LIBRARIES})
    set(LIBOSMODSP_SEL_LIBRARY_DIRS ${FFTW3f_LIBRARY_DIRS})
    set(LIBOSMODSP_SEL_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/libosmo-dsp/src/cxvec.c ${CMAKE_CURRENT_SOURCE_DIR}/libosmo-dsp/src/iqbal.c)
endif()

########################################################################
# Install directories
########################################################################
include(GrPlatform) #define LIB_SUFFIX

if(NOT CMAKE_MODULES_DIR)
  set(CMAKE_MODULES_DIR lib${LIB_SUFFIX}/cmake)
endif(NOT CMAKE_MODULES_DIR)

set(GR_RUNTIME_DIR      bin)
set(GR_LIBRARY_DIR      lib${LIB_SUFFIX})
set(GR_INCLUDE_DIR      include)
SET(GR_CMAKE_DIR        ${CMAKE_MODULES_DIR}/gr-iqbal)
set(GR_DATA_DIR         share)
set(GR_PKG_DATA_DIR     ${GR_DATA_DIR}/${CMAKE_PROJECT_NAME})
set(GR_DOC_DIR          ${GR_DATA_DIR}/doc)
set(GR_PKG_DOC_DIR      ${GR_DOC_DIR}/${CMAKE_PROJECT_NAME})
set(GR_CONF_DIR         etc)
set(GR_PKG_CONF_DIR     ${GR_CONF_DIR}/${CMAKE_PROJECT_NAME}/conf.d)
set(GR_LIBEXEC_DIR      libexec)
set(GR_PKG_LIBEXEC_DIR  ${GR_LIBEXEC_DIR}/${CMAKE_PROJECT_NAME})
set(GRC_BLOCKS_DIR      ${GR_PKG_DATA_DIR}/grc/blocks)

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
# Setup the include and linker paths
########################################################################
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${Boost_INCLUDE_DIRS}
    ${LIBOSMODSP_SEL_INCLUDE_DIRS}
    ${GNURADIO_ALL_INCLUDE_DIRS}
)

link_directories(
    ${Boost_LIBRARY_DIRS}
    ${LIBOSMODSP_SEL_LIBRARY_DIRS}
    ${GNURADIO_ALL_LIBRARY_DIRS}
)

# Set component parameters
set(GR_IQBALANCE_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include CACHE INTERNAL "" FORCE)
set(GR_IQBALANCE_SWIG_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/swig CACHE INTERNAL "" FORCE)

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
add_subdirectory(swig)
add_subdirectory(python)
add_subdirectory(grc)
add_subdirectory(apps)
add_subdirectory(docs)

########################################################################
# Create Pkg Config File
########################################################################
file(TO_NATIVE_PATH "${CMAKE_INSTALL_PREFIX}"           prefix)
file(TO_NATIVE_PATH "\${prefix}"                        exec_prefix)
file(TO_NATIVE_PATH "\${exec_prefix}/${GR_LIBRARY_DIR}" libdir)
file(TO_NATIVE_PATH "\${prefix}/${GR_INCLUDE_DIR}"      includedir)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/gnuradio-iqbalance.pc.in
    ${CMAKE_CURRENT_BINARY_DIR}/gnuradio-iqbalance.pc
@ONLY)

install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/gnuradio-iqbalance.pc
    DESTINATION ${GR_LIBRARY_DIR}/pkgconfig
)

########################################################################
# Install cmake search helper for this library
########################################################################
#install(FILES cmake/Modules/gnuradio-iqbalanceConfig.cmake
#    DESTINATION ${CMAKE_MODULES_DIR}/gnuradio-iqbalance
#)
