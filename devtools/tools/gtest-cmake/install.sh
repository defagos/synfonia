#!/bin/bash

# ************************************************************
# Installs all files needed to compile Google Test with CMake
# ************************************************************

# User manual
usage() {
    echo
    echo "Generates a directory containing all makefiles for a given enviroment"
    echo
    echo "Usage: `basename $0` GOOGLE_TEST_MAIN_DIRECTORY"
    echo
}

# Check that the maximum number of parameters has not been exceeded
if [ "$#" != "1" ]; then
    usage
    exit 1
fi

# Directory containing this file (absolute)
SCRIPT_FILE_DIR=`dirname $0`
SCRIPT_FILE_DIR=`cd $SCRIPT_FILE_DIR; pwd`

# Directory where the output files must be saved (converted to absolute path)
OUTPUT_DIR=`cd $1; pwd`

# Main devtools directory where the generic scripts reside
MAIN_DEVTOOLS_DIR=$SCRIPT_FILE_DIR/../..

# Check that the destination directory seems correct
if [ ! -d "$OUTPUT_DIR/include/gtest" ]; then
    echo "Error: The directory $OUTPUT_DIR is not a Google Test main directory"
    exit 1
fi

# Copy the CMakeLists.txt files
cp $SCRIPT_FILE_DIR/CmakeLists.txt $OUTPUT_DIR
cp -r $SCRIPT_FILE_DIR/src $OUTPUT_DIR

# Copy the makefile generators
mkdir -p $OUTPUT_DIR/devtools/common
cp $MAIN_DEVTOOLS_DIR/generate*.sh $OUTPUT_DIR/devtools
cp -r $MAIN_DEVTOOLS_DIR/common/*.sh $OUTPUT_DIR/devtools/common