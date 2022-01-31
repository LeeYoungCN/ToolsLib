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

function copy_tmplate_file()
{
    if [ ! -e ${root}/${1} ];then
        cp -rf ${platform_path}/template/${1} ${root}/${1}
    fi
}

if [ ! -d ${root}/.vscode ]; then
    mkdir -p ${root}/.vscode
fi

copy_tmplate_file ".vscode/tasks.json"
copy_tmplate_file "CMakeLists.txt"
copy_tmplate_file "download_Platform.sh"
copy_tmplate_file ".gitignore"
