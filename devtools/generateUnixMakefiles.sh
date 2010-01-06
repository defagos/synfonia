#!/bin/sh

#*****************************************************
# Unix (out-of-source) makefile generator for Synfonia
#*****************************************************

# Set directories
SYNFONIA_DEV_DIR=`pwd`

# Generate the Unix makefile for all configurations
echo
echo "Generating Unix makefile"
echo "------------------------"

echo
echo "Generating Debug makefile"
mkdir -p $SYNFONIA_DEV_DIR/UnixMakefiles/Debug
cd $SYNFONIA_DEV_DIR/UnixMakefiles/Debug
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug ../../..

echo
echo "Generating Release makefile"
mkdir -p $SYNFONIA_DEV_DIR/UnixMakefiles/Release
cd $SYNFONIA_DEV_DIR/UnixMakefiles/Release
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ../../..

echo
echo "Generating RelWithDebInfo makefile"
mkdir -p $SYNFONIA_DEV_DIR/UnixMakefiles/RelWithDebInfo
cd $SYNFONIA_DEV_DIR/UnixMakefiles/RelWithDebInfo
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=RelWithDebInfo ../../..

echo
echo "Generating MinSizeRel makefile"
mkdir -p $SYNFONIA_DEV_DIR/UnixMakefiles/MinSizeRel
cd $SYNFONIA_DEV_DIR/UnixMakefiles/MinSizeRel
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=MinSizeRel ../../..

# Back to dev directory
cd $SYNFONIA_DEV_DIR