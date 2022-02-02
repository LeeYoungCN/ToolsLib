#!/bin/bash
tool_arr=("CanFrame" "FileListTrans")

function judge_input()
{
    for tmp_target in ${tool_arr[*]}; do
        if [ "$1" == "${tmp_target}" ]; then
            return 0
        fi
    done
    echo "input error: $1"
    echo "tool_name = ${tool_arr[*]}"
    return 1
}

function start_cfg_build()
{
        ./cmake_cfg_build.sh "${1}"
        if [ $? -ne 0 ]; then
            exit
        fi
}

function build_all()
{
    for tmp_target in ${tool_arr[*]}; do
        start_cfg_build ${tmp_target}
    done
}

function build_input_target()
{
    judge_input ${1}
    if [ $? -eq 0 ]; then
        start_cfg_build ${1}
    fi
}

pushd ./../Platform/build >> /dev/null

if [ $# -eq 0 ]; then
    build_all
else
    for tmp in $*; do
        build_input_target ${tmp}
    done
fi

popd >> /dev/null
