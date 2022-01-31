#!/bin/bash
function copy_tmplate_file()
{
    file_name="${1}"
    file_name=${file_name#${template_path}\/}
    if [ ! -e ${root}/${file_name} ];then
        cp -rf ${template_path}/${file_name} ${root}/${file_name}
    fi
}

function copy_all_file()
{
    for f in $(ls -a $1); do
        if [ ${f} == "." -o ${f} == ".." ]; then
            continue
        fi
        if [ -d ${f} ]; then
            copy_all_file "${1}/${f}"
        else
            copy_tmplate_file "${1}/${f}"
        fi
    done
}

function backup_file()
{
    file="${1}"
    echo ${file}
    if [ -d ${file} ]; then
        mv -f "${file}" "${file}_backup"
    fi
}

function reset_from_backup()
{
    file="${1}"
    if [ -d "${file}_backup" ]; then
        mv -f "${file}_backup" "${file}"
    fi
}

function delete_backup()
{
    file="${1}"
    if [ -d "${file}_backup" ]; then
        rm -rf "${file}_backup"
    fi
}

function git_clone_repository()
{
    ssh_path="${1}"
    repository=${ssh_path#*/}
    repository=${repository%*.git}
    backup_file "${repository}"
    git clone "${ssh_path}"
    if [ $? -ne 0 ]; then
        reset_from_backup "${repository}"
        exit
    fi
    delete_backup "${repository}"
}

git_clone_repository "git@github.com:LeeYoungCN/Platform.git"
root=$(pwd)
platform_path=$(cd Platform;pwd)
template_path="${platform_path}/template"
cd ${platform_path}/build
./init_env.sh
cd ${root}

if [ ! -d ${root}/.vscode ]; then
    mkdir -p ${root}/.vscode
fi

copy_all_file ${template_path}
