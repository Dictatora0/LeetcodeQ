#!/bin/bash

# 面向四道重点真题的 smoke tests。
# 额外包含：
# 1. 二进制题暴力版与优化版的边界测试
# 2. 二进制题在 1..1000 的自动对拍

set -u

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"
SOURCE_ROOT="$PROJECT_ROOT/interview_algorithm_toolbox/12_real_past_problems"
BUILD_DIR="$(mktemp -d "${TMPDIR:-/tmp}/interview_algorithm_toolbox_smoke.XXXXXX")"

CXXFLAGS=(-std=c++17 -Wall -Wextra -O2)

PASS_COUNT=0
FAIL_COUNT=0

compile_target() {
    local source_file="$1"
    local output_file="$2"

    if g++ "${CXXFLAGS[@]}" "$source_file" -o "$output_file"; then
        echo "[BUILD PASS] ${source_file#$PROJECT_ROOT/}"
    else
        echo "[BUILD FAIL] ${source_file#$PROJECT_ROOT/}"
        FAIL_COUNT=$((FAIL_COUNT + 1))
    fi
}

run_case() {
    local case_name="$1"
    local executable="$2"
    local input_data="$3"
    local expected_output="$4"
    local actual_output

    actual_output="$(printf "%s" "$input_data" | "$executable")"

    if [ "$actual_output" = "$expected_output" ]; then
        echo "[PASS] $case_name"
        PASS_COUNT=$((PASS_COUNT + 1))
    else
        echo "[FAIL] $case_name"
        echo "  expected:"
        printf '    %s\n' "$expected_output"
        echo "  actual:"
        printf '    %s\n' "$actual_output"
        FAIL_COUNT=$((FAIL_COUNT + 1))
    fi
}

ODD_EXE="$BUILD_DIR/maximum_odd_product_subset"
FRACTION_EXE="$BUILD_DIR/fraction_descending_sort"
BRUTE_EXE="$BUILD_DIR/binary_suffix_ones_sum_bruteforce"
OPT_EXE="$BUILD_DIR/binary_suffix_ones_sum_optimized"
AB_EXE="$BUILD_DIR/ab_transformation_string"

compile_target "$SOURCE_ROOT/maximum_odd_product_subset.cpp" "$ODD_EXE"
compile_target "$SOURCE_ROOT/fraction_descending_sort.cpp" "$FRACTION_EXE"
compile_target "$SOURCE_ROOT/binary_suffix_ones_sum_bruteforce.cpp" "$BRUTE_EXE"
compile_target "$SOURCE_ROOT/binary_suffix_ones_sum_optimized.cpp" "$OPT_EXE"
compile_target "$SOURCE_ROOT/ab_transformation_string.cpp" "$AB_EXE"

if [ "$FAIL_COUNT" -gt 0 ]; then
    echo "Smoke tests aborted because some targets failed to compile."
    echo "Temporary build dir: $BUILD_DIR"
    exit 1
fi

run_case \
    "maximum_odd_product_subset boundaries" \
    "$ODD_EXE" \
    $'4\n1\n7\n4\n2 4 6 8\n4\n1 3 5 7\n6\n1 2 3 4 5 6\n' \
    $'1\n-1\n4\n3'

run_case \
    "fraction_descending_sort mixed signs and zero" \
    "$FRACTION_EXE" \
    $'6\n1 2\n2 3\n0 5\n-1 3\n999 1000\n1000 1001\n' \
    $'1000/1001\n999/1000\n2/3\n1/2\n0/5\n-1/3'

run_case \
    "binary_suffix_ones_sum brute boundaries" \
    "$BRUTE_EXE" \
    $'5\n1\n2\n3\n7\n8\n' \
    $'1\n1\n4\n12\n12'

run_case \
    "binary_suffix_ones_sum optimized boundaries" \
    "$OPT_EXE" \
    $'5\n1\n2\n3\n7\n8\n' \
    $'1\n1\n4\n12\n12'

run_case \
    "ab_transformation_string boundaries" \
    "$AB_EXE" \
    $'8\na\nb\nab\nba\naabb\nabab\nabba\naaabbb\n' \
    $'NO\nNO\nYES\nNO\nYES\nYES\nNO\nYES'

MISMATCH_AT=-1
for n in $(seq 1 1000); do
    brute_output="$(printf "1\n%d\n" "$n" | "$BRUTE_EXE")"
    opt_output="$(printf "1\n%d\n" "$n" | "$OPT_EXE")"
    if [ "$brute_output" != "$opt_output" ]; then
        MISMATCH_AT="$n"
        break
    fi
done

if [ "$MISMATCH_AT" -eq -1 ]; then
    echo "[PASS] binary_suffix_ones_sum brute vs optimized check (1..1000)"
    PASS_COUNT=$((PASS_COUNT + 1))
else
    echo "[FAIL] binary_suffix_ones_sum brute vs optimized check (1..1000)"
    echo "  first mismatch at n = $MISMATCH_AT"
    FAIL_COUNT=$((FAIL_COUNT + 1))
fi

echo "----------------------------------------"
echo "Smoke summary"
echo "  passed: $PASS_COUNT"
echo "  failed: $FAIL_COUNT"
echo "  build dir: $BUILD_DIR"

if [ "$FAIL_COUNT" -gt 0 ]; then
    exit 1
fi

exit 0
