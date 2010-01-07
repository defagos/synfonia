# CMake build rules for the core unit tests
# -----------------------------------------

# Public includes
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include)

# Test source files
ADD_EXECUTABLE(core_test
    main
    clone_test
    platform_test)

# Use Boost
INCLUDE_DIRECTORIES_BOOST()

# Use Google Test
INCLUDE_DIRECTORIES_GOOGLE_TEST()
TARGET_LINK_LIBRARIES_GOOGLE_TEST(core_test)

# Add to unit tests
ADD_TEST(core_test
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/core_test)