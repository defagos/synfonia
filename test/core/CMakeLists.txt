# CMake build rules for the core unit tests
# -----------------------------------------

# Test source files
ADD_EXECUTABLE(core_test
    main
    clone_test
    exception_test
    float_test)

# Use core library
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include)
TARGET_LINK_LIBRARIES(core_test core)

# Use Boost
INCLUDE_DIRECTORIES_BOOST()

# Use Google Test
INCLUDE_DIRECTORIES_GOOGLE_TEST()
TARGET_LINK_LIBRARIES_GOOGLE_TEST(core_test)

# Add to unit tests
ADD_TEST(core_test
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/core_test)