#!/bin/bash
echo "Start init enviriment!"
script_path=$(pwd)
cd ..
file_name=public_config.sh
target_name="${1}"

# 创建文件
function create_file()
{
    if [ -e ${1} ];then
        rm -rf ${1}
    fi
    touch ${1}
}

# 写入public_config.sh 文件
function write_to_file()
{
    echo ${1} >> ${file_name}
}

# 获取CMakeList，TXT所在路径
function get_cmake_source_dir()
{
    cmake_source_dir=$(pwd)
    write_to_file "cmake_source_dir=${cmake_source_dir}"
}

# 根据关键字获取 CMakeLists.txt 设置项
function get_set_info_by_keyword()
{
    key_word="$1"
    target_line=$(cat CMakeLists.txt | grep "set(${key_word}.*)")
    echo $target_line
}

# 获取TARGET_NAME
function get_target_name()
{
    write_to_file "target_name=${target_name}"
}

# 获取路径设置
function get_path()
{
    line="${1}"
    target_path=${line##*/}
    target_path=${target_path%%)*}
    echo "${target_path}"
}

# 获取可执行文件的路径
function get_executable_output_path()
{
    output_path_line=$(get_set_info_by_keyword "EXECUTABLE_OUTPUT_PATH")
    executable_output_path=$(get_path "${output_path_line}")
    write_to_file "executable_output_path=${executable_output_path}"
}

# 获取CMake中间件的生成路劲
function get_buildcache_path()
{
    buildcache_line=$(get_set_info_by_keyword "BUILDCACHE_PATH")
    buildcache_path=$(get_path "${buildcache_line}")
    write_to_file "buildcache_path=${buildcache_path}"
}

# 刷新launch.json可执行文件的路径
function set_exe_path_in_launch()
{
    pushd ${cmake_source_dir}/.vscode >> /dev/null
    key="\"program\""
    value="${executable_output_path}/${target_name}.exe"
    old_line=$(cat launch.json | grep "${key}.*")
    old_line=${old_line##*\{workspaceFolder\}\/}
    old_line=${old_line%%\",*}
    command="s#${old_line}#${value}#g"
    sed -i ${command} launch.json
    popd >> /dev/null
}

create_file ${file_name}
get_cmake_source_dir
get_target_name
get_executable_output_path
get_buildcache_path
set_exe_path_in_launch

mv ${file_name} ${script_path}

echo "Init enviriment success!"