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

rm -rf ${executable_output_path}
rm -rf ${buildcache_path}
