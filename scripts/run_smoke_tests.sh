#!/bin/bash

# 仓库根目录入口，转发到 interview_algorithm_toolbox 的 smoke tests。

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"

exec "$PROJECT_ROOT/interview_algorithm_toolbox/scripts/run_smoke_tests.sh"
