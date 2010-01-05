# CMake build rules for the Google Test static library
# ----------------------------------------------------

# Public includes
INCLUDE_DIRECTORIES(../include)

# The gtest-all.cc file has been introduced to compile Google Test easily by including
# the relevant src/*.cpp files, but at the cost of the following trick
INCLUDE_DIRECTORIES(..)

# Microsoft Visual C++ 2010: Implements TR1, cannot be currently disabled. We disable Google
# own implementation
# TODO: Might change with the final release of VS 2010 and with more recent versions of
#       gtest-port.h. Will probably be dropped in the future
IF(MSVC AND NOT(MSVC_VERSION LESS 1600))
	ADD_DEFINITIONS(-DGTEST_USE_OWN_TR1_TUPLE=0)
ENDIF()

# Project source files
ADD_LIBRARY(gtest
	gtest-all)