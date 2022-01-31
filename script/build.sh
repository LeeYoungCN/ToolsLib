#!/bin/bash

if [ $# -eq 0 ]; then
    echo "0"
    ./init_env.sh "Default"
    ./cmake_cfg_build.sh
    exit
fi

for target_name in $*
do
    ./init_env.sh "${target_name}"
    ./cmake_cfg_build.sh
done
