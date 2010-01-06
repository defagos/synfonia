#!/bin/sh

#********************************************************
# Unix (out-of-source) makefile generator for Google Test
#********************************************************

# Set directories
GOOGLE_TEST_DEV_DIR=`pwd`

# Generate the Unix makefile for all configurations
echo
echo "Generating Unix makefile"
echo "------------------------"

echo
echo "Generating Debug makefile"
mkdir -p $GOOGLE_TEST_DEV_DIR/UnixMakefiles/Debug
cd $GOOGLE_TEST_DEV_DIR/UnixMakefiles/Debug
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug ../../..

echo
echo "Generating Release makefile"
mkdir -p $GOOGLE_TEST_DEV_DIR/UnixMakefiles/Release
cd $GOOGLE_TEST_DEV_DIR/UnixMakefiles/Release
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ../../..

echo
echo "Generating RelWithDebInfo makefile"
mkdir -p $GOOGLE_TEST_DEV_DIR/UnixMakefiles/RelWithDebInfo
cd $GOOGLE_TEST_DEV_DIR/UnixMakefiles/RelWithDebInfo
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=RelWithDebInfo ../../..

echo
echo "Generating MinSizeRel makefile"
mkdir -p  $GOOGLE_TEST_DEV_DIR/UnixMakefiles/MinSizeRel
cd $GOOGLE_TEST_DEV_DIR/UnixMakefiles/MinSizeRel
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=MinSizeRel ../../..

# Back to dev directory
cd $GOOGLE_TEST_DEV_DIR