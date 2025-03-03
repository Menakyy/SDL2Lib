#!/bin/bash
set -e
PROJECT_ROOT=$(realpath "$(dirname "$0")/..")
cd "$PROJECT_ROOT"

if [ $# -lt 1 ] ; then
    echo "usage: coverage_html.sh gcc|clang"
    echo -e "\t Select compiler used to generate coverage data!"
    exit 1
fi
COMPILER="$1"
if [ "$1" == "clang" ] ; then
    GCOV_TOOL="llvm-cov gcov"
elif [ "$1" == "gcc" ] ; then
    GCOV_TOOL="gcov"
else
    echo "usage: coverage_html.sh gcc|clang"
    echo -e "\tInvalid argument!"
    exit 2
fi

BUILD_POSTFIX="$2"

cd "build$BUILD_POSTFIX"
lcov -d . --gcov-tool "$GCOV_TOOL" --capture -o coverage.info
lcov -r coverage.info \
    "/usr/include/*" \
    "*cpputest*" \
    -o filtered.info
genhtml -o coverage filtered.info --demangle-cpp
# rm coverage.info filtered.info