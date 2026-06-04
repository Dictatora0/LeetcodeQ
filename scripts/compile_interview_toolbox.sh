#!/bin/bash

# 仓库根目录入口，转发到 interview_algorithm_toolbox 的批量编译脚本。

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"

exec "$PROJECT_ROOT/interview_algorithm_toolbox/scripts/compile_all.sh"
