# CMake build rules for Synfonia
# ---------------------------------
# Using CMake, this file generates the files needed to build Synfonia in a platform-independent
# way. You will need to install CMake first (www.cmake.org).
#
# Usage: CMake supports out-of-source and in-source builds. Out-of-source builds are strongly
#        recommended since they keep the source tree intact:
#    i) Out-of-source build: Create a directory somewhere, switch to this directory and execute
#                            cmake from there, giving it the directory where this CMakeLists.txt
#                            file is located. Usually the out-of-source build takes place
#                            in a subdirectory created in the same directory as the CMakeLists.txt
#                            file, e.g.:
#                                    cd <main CMakeLists.txt directory>
#                                    mkdir build
#                                    cd build
#                                    cmake ..
#    ii) In-source build: This is the degenerated case where cmake is executed directly from
#        the directory where CMakeLists.txt is located, i.e.:
#                                    cd <main CMakeLists.txt directory>
#                                    cmake .
#
# Use the cmake -G flag if you want to set the makefile generator manually.
#
# Supported configurations: Debug, Release, RelWithDebInfo, MinSizeRel

# Coding style
# ------------
# I am no CMake expert, here are a few choices I made. These reflect my current understanding
# of how CMake deals with visibility of variables / functions, and might therefore not be optimal:
#  - The main CMakeLists.txt file (this file!) calculates some global constants which do not
#    appear in the cache, but which can be freely used by child CMakeLists.txt. These variables
#    are denoted CONST_<NAME> and their content must not be altered once it has been properly set.
#  - Public functions are denoted FCT_<NAME>. Functions used internally for implementation
#    purposes are denoted PFCT_<NAME>
#  - Function parameter names and names of variables defined locally in a function are in all
#    lowercase. They are denoted _<name> and <name> respectively.
#  - All other identifyers and the language keywords are written in uppercase
#  - Public reusable functions are defined in the main CMakeLists.txt so that they are available
#    to children CMakeLists.txt files.
#  - Some variables must be supplied by the developer manually using the cache (which can be
#    conveniently edited using the CMake GUI). These variables are most notably used to define the
#    location of the includes and static libraries needed to compile and link the project.
#    I preferred this approach over FIND_PACKAGE for the following reasons:
#      - the functions called using FIND_PACKAGE often need external configuration variables
#        set using the cache, i.e. they are not completely self-sufficient
#      - they must be maintained with newer releases of the project they locate, and they might
#        therefore not be able to locate recent versions
#      - if the project they are related to changes its layout (e.g. where includes are found,
#        or where binaries are generated), they might not do their work correctly or they might
#        fail until someone fixes them
#      - they cannot cope with the granularity we need (x86 / x64, configurations, compilers, ...).
#        They probably usually work fine for projects using the standard binaries, but we need more
#        binaries, which we probably will need to compile ourselves for non-standard ones
#      - in all cases in which such functions would fail (and in our case they would certainly)
#        we would have to supply the paths to the include and static libraries manually anyway
#    Of course a little cache configuration will be required, but I think this will be less
#    frustrating and more predictable than having FIND_PACKAGE fail or return the wrong paths.

CMAKE_MINIMUM_REQUIRED(VERSION 2.6 FATAL_ERROR)
PROJECT(synfonia)

# Final binary products are separated using three directory levels for easy identification, as
# follows:
#   - 1st directory level: lib for static libraries, dll for dynamic link libraries and bin
#                          for executables
#   - 2nd directory: platform (MSVC10x86 and MSVC10x64 for Visual C++ 2010 compiler 32 / 64 bits,
#                    MinGW for MinGW, etc.)
#   - 3rd directory level: A subdirectory is created for each configuration (Debug, Release,
#                          RelWithDebInfo, MinSizeRel)
# A remark about the Visual Studio solution generators: Though a single solution can support
# 32 and 64-bit platforms when created by hand, CMake generators cannot. If we want both solution
# flavors, we therefore need two cmake runs with different generators.
# Other generators conform to the "autotools convention of one configuration per build tree"
# (see http://www.cmake.org/pipermail/cmake/2004-July/005286.html)

# Visual Studio 2010 solution (32-bits)
IF(${CMAKE_GENERATOR} STREQUAL "Visual Studio 10")
	SET(CONST_PLATFORM MSVC10x86)
	# The Visual Studio solution generators automatically generate separate output directories for
	# each configuration. We do not need to generate the 3rd directory level
	SET(OUTPUT_SUBDIR ${CONST_PLATFORM})
# Visual Studio 2010 solution (64-bits)
ELSEIF(${CMAKE_GENERATOR} STREQUAL "Visual Studio 10 Win64")
	SET(CONST_PLATFORM MSVC10x64)
	# The Visual Studio solution generators automatically generate separate output directories for
	# each configuration. We do not need to generate the 3rd directory level
	SET(OUTPUT_SUBDIR ${CONST_PLATFORM})
# Visual Studio 2008 solution (32-bits)
ELSEIF(${CMAKE_GENERATOR} STREQUAL "Visual Studio 9 2008")
	SET(CONST_PLATFORM MSVC9x86)
	# The Visual Studio solution generators automatically generate separate output directories for
	# each configuration. We do not need to generate the 3rd directory level
	SET(OUTPUT_SUBDIR ${CONST_PLATFORM})
# Visual Studio 2008 solution (64-bits)
ELSEIF(${CMAKE_GENERATOR} STREQUAL "Visual Studio 9 2008 Win64")
	SET(CONST_PLATFORM MSVC9x64)
	# The Visual Studio solution generators automatically generate separate output directories for
	# each configuration. We do not need to generate the 3rd directory level
	SET(OUTPUT_SUBDIR ${CONST_PLATFORM})
# MinGW compiler (32-bits)
ELSEIF(${CMAKE_GENERATOR} STREQUAL "MinGW Makefiles")
	SET(CONST_PLATFORM MinGW)
	# The build configuration must be explicitly specified
	IF (NOT CMAKE_BUILD_TYPE)
		MESSAGE(FATAL_ERROR "Missing configuration. Add -DCMAKE_BUILD_TYPE when calling cmake")
	ENDIF()
	# We need to generate all directory levels
	SET(OUTPUT_SUBDIR ${CONST_PLATFORM}/${CMAKE_BUILD_TYPE})
# Unix Makefiles
ELSEIF (${CMAKE_GENERATOR} STREQUAL "Unix Makefiles")
	SET(CONST_PLATFORM UnixMakefiles)
	# The build configuration must be explicitly specified
	IF (NOT CMAKE_BUILD_TYPE)
		MESSAGE(FATAL_ERROR "Missing configuration. Add -DCMAKE_BUILD_TYPE when calling cmake")
	ENDIF()
	# We need to generate all directory levels
	SET(OUTPUT_SUBDIR ${CONST_PLATFORM}/${CMAKE_BUILD_TYPE})
# For all generators we do not support officially: error
ELSE()
	MESSAGE(FATAL_ERROR "The generator ${CMAKE_GENERATOR} is currently not supported for Synfonia")
ENDIF()

# Set the output directories
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/${OUTPUT_SUBDIR})
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/dll/${OUTPUT_SUBDIR})
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${OUTPUT_SUBDIR})

# Helper function for retrieving an include path defined by a cache variable named
# EXT_${_name}_INCLUDE, for example EXT_BOOST_INCLUDE; error if this variable does not exist
#   @param _name: The name of the library the includes belong to
FUNCTION(PFCT_EXT_INCLUDE_DIRECTORIES _name)
	# Error if the variable giving the include location does not exist 
	IF(NOT EXT_${_name}_INCLUDE)
		MESSAGE(FATAL_ERROR "Missing cache variable EXT_${_name}_INCLUDE of type path, giving "
			"the location of the includes for ${_name}")
	ENDIF()
	
	# Include the directory
	INCLUDE_DIRECTORIES(${EXT_${_name}_INCLUDE})
ENDFUNCTION()

# Helper function for checking that the variable giving the location of a static library has
# been defined, and binding the location giben by EXT_${_name}_LIB_${_config}_${CONST_PLATFORM}
# to the library ${_name}_lib; error if the variable does not exist
#   @param _name: The relevant part of the library name ${_name}_lib
#   @param _config: The configuration
FUNCTION(PFCT_CHECK_AND_BIND_LIB _name _config)
	# Error if the variable giving the library location does not exist 
	IF(NOT EXT_${_name}_LIB_${_config}_${CONST_PLATFORM})
		MESSAGE(FATAL_ERROR "Missing cache variable EXT_${_name}_LIB_${_config}_${CONST_PLATFORM} "
			"of type filepath, giving the location of the ${CONST_PLATFORM} ${_config} static "
			"library file for ${_name} (for use with ${CMAKE_GENERATOR})")
	ENDIF()
	
	# Binds its location on disk on a per-configuration basis
	SET_PROPERTY(
		TARGET ${_name}_lib
		PROPERTY IMPORTED_LOCATION_${_config} ${EXT_${_name}_LIB_${_config}_${CONST_PLATFORM}})
ENDFUNCTION()

# Helper function for binding a static library whose path is defined by a cache variable named
# EXT_${_name}_LIB_${CMAKE_BUILD_TYPE}_${CONST_PLATFORM}, for example
# EXT_BOOST_LIB_RELEASE_MSVC10; error if this variable does not exist.
#   @param _target: The name of the executable, static library, etc. which we are linking to
#   @param _name: The name of the static library we are linking
FUNCTION(PFCT_EXT_TARGET_LINK_LIBRARIES _target _name)
	# About the implementation: We cannot use TARGET_LINK_LIBRARIES in its simplest form here
	# since it is missing the configuration granularity we need. Therefore, we:
	#   - add a library alias for an IMPORTED library using ADD_LIBRARY. This maps an external
	#     library to a name in the internal namespace
	#   - set the properties of this library, most notably where it is located and to which
	#     configuration it belongs
	#   - we then can apply TARGET_LINK_LIBRARIES to link the imported library
	# Refer to the CMake documentation for more detail.

	# Microsoft Visual C++ Compiler: When generating a solution, we generate all configurations
	# at once in a single run of cmake. Therefore it makes sense to attach external libraries
	# on a per-configuration basis.
	# Other compilers: When generating build scripts, we generate a single configuration
	# ${CMAKE_BUILD_TYPE} per run of cmake. Intuitively we should therefore perform a switch
	# on the configuration, and depending on the result just link the static libraries for this
	# specific kind of configuration. Unfortunately, due to the fact that CMake supports both
	# generation of multiple configurations in a run (for MSVC) or of only one configuration
	# per run (for other compilers), there is no variable holding the configuration.
	# Therefore we bind all configurations even in the case of the generation of a single
	# configuration per run. The price to pay is that all environment variables must be set
	# for all configurations, even if they will be ignored (in such cases empty strings can be
	# provided).
	# For more information about this subtlety of CMake, read
	#   http://www.cmake.org/pipermail/cmake/2007-October/017082.html
	
	# Creates an alias for an external static library which will hold all configurations
	ADD_LIBRARY(${_name}_lib STATIC IMPORTED)
	
	# Binds its location on disk on a per-configuration basis
	PFCT_CHECK_AND_BIND_LIB(${_name} DEBUG)
	PFCT_CHECK_AND_BIND_LIB(${_name} RELEASE)
	PFCT_CHECK_AND_BIND_LIB(${_name} RELWITHDEBINFO)
	PFCT_CHECK_AND_BIND_LIB(${_name} MINSIZEREL)
	
	# Binds the library; this will link to the correct library for each configuration
	TARGET_LINK_LIBRARIES(${_target} ${_name}_lib)
ENDFUNCTION()

# Function for adding Boost includes to a project
# The include path is set using the cache variable EXT_BOOST_INCLUDE
FUNCTION(INCLUDE_DIRECTORIES_BOOST)
	PFCT_EXT_INCLUDE_DIRECTORIES(BOOST)
ENDFUNCTION()

# Function for adding Google Test includes to a project
# The include path is set using the cache variable EXT_GOOGLE_TEST_INCLUDE
FUNCTION(INCLUDE_DIRECTORIES_GOOGLE_TEST)
	# Microsoft Visual C++ 2010: Implements TR1, cannot be currently disabled. We disable Google
	# own implementation
	# TODO: Might change with the final release of VS 2010 and with future versions of
	#       gtest-port.h. Will probably be dropped in the future
	IF(MSVC AND NOT(MSVC_VERSION LESS 1600))
		ADD_DEFINITIONS(-DGTEST_USE_OWN_TR1_TUPLE=0)
	ENDIF()

	PFCT_EXT_INCLUDE_DIRECTORIES(GOOGLE_TEST)
ENDFUNCTION()

# Function for adding Google Test main libraries to a project. Different for each kind
# of configuration and platform)
# The file path is set using the variables EXT_GOOGLE_TEST_LIB_<configuration>_<platform>
#   @param _target The project to link the library to
FUNCTION(TARGET_LINK_LIBRARIES_GOOGLE_TEST _target)
	PFCT_EXT_TARGET_LINK_LIBRARIES(${_target} GOOGLE_TEST)
ENDFUNCTION()