# CMake build rules for the core project
# --------------------------------------

# Public includes
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include)

# Source files
ADD_LIBRARY(core
    exception)