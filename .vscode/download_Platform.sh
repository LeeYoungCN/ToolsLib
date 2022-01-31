#!/bin/bash
if [ -d Platform ]; then
    rm -rf Platform
fi

git clone git@github.com:LeeYoungCN/Platform.git

root=$(pwd)
platform_path=$(cd Platform;pwd)
cd ${platform_path}/build
./init_env.sh
cd ${root}
if [ ! -d ${root}/.vscode ]; then
    mkdir -p ${root}/.vscode
fi

if [ ! -e ${root}/.vscode/task.json ];then
    cp -rf ${platform_path}/template/task.json ${root}/.vscode/
fi

if [ ! -e ${root}/CMakeLists.txt ];then
    cp -rf ${platform_path}/template/CMakeLists.txt ${root}/CMakeLists.txt
fi
