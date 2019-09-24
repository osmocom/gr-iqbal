INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_IQBALANCE iqbalance)

FIND_PATH(
    IQBALANCE_INCLUDE_DIRS
    NAMES iqbalance/api.h
    HINTS $ENV{IQBALANCE_DIR}/include
        ${PC_IQBALANCE_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    IQBALANCE_LIBRARIES
    NAMES gnuradio-iqbalance
    HINTS $ENV{IQBALANCE_DIR}/lib
        ${PC_IQBALANCE_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
          )

include("${CMAKE_CURRENT_LIST_DIR}/iqbalanceTarget.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(IQBALANCE DEFAULT_MSG IQBALANCE_LIBRARIES IQBALANCE_INCLUDE_DIRS)
MARK_AS_ADVANCED(IQBALANCE_LIBRARIES IQBALANCE_INCLUDE_DIRS)
