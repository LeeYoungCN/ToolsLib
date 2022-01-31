#!/bin/bash
source ./public_config.sh
pushd .. >> /dev/null
cmake --build ${buildcache_path} --target all
