#!/bin/bash

# 统一 C++ 编译脚本的路径解析与输出目录规则

build_mode() {
    if [ "${MODE:-release}" == "debug" ]; then
        echo "debug"
    else
        echo "release"
    fi
}

build_output_root() {
    local project_root="$1"
    echo "$project_root/build/$(build_mode)"
}

build_cxxflags() {
    if [ "$(build_mode)" == "debug" ]; then
        echo "-std=c++17 -g -O0 -Wall -Wextra"
    else
        echo "-std=c++17 -O2 -Wall"
    fi
}

normalize_path() {
    local project_root="$1"
    local input_path="$2"

    if [[ "$input_path" != /* ]]; then
        input_path="$project_root/$input_path"
    fi

    local input_dir
    input_dir="$(cd "$(dirname "$input_path")" && pwd)"
    echo "$input_dir/$(basename "$input_path")"
}

output_file_for_source() {
    local project_root="$1"
    local source_file="$2"
    local output_root="$3"
    local relative_path

    if [[ "$source_file" == "$project_root"/* ]]; then
        relative_path="${source_file#$project_root/}"
    else
        relative_path="external/$(basename "$source_file")"
    fi

    relative_path="${relative_path%.cpp}"
    echo "$output_root/$relative_path"
}
