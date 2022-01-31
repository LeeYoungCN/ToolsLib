#!/bin/bash
source ./public_config.sh
./cmake_build.sh

pushd .. >> /dev/null
cd ./${executable_output_path}

./${target_name}.exe ${1} ${2}