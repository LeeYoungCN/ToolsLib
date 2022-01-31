#!/bin/bash
source ./public_config.sh
pushd .. >> /dev/null

function CreateFolder()
{
    if [ -e ${1} ];then
        rm -rf ${1}
    fi
    mkdir ${1}
}

CreateFolder ${executable_output_path}
CreateFolder ${buildcache_path}

cmake -S . -B ${buildcache_path} -DTARGET_NAME=${target_name} -G "MinGW Makefiles"

popd >> /dev/null
./cmake_build.sh