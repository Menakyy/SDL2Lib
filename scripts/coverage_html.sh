#!/bin/bash
set -e
PROJECT_ROOT=$(realpath "$(dirname "$0")/..")
cd "$PROJECT_ROOT"

if [ $# -lt 1 ] ; then
	echo "usage: lcov.sh gcc|clang"
	echo -e "\t Select compiler used to generate coverage data!"
	exit 1
fi
COMPILER="$1"
if [ "$1" == "clang" ] ; then
	LCOV_ARGS="--gcov-tool $(realpath scripts/gcov-llvm-wrapper.sh)"
elif [ "$1" == "gcc" ] ; then
	LCOV_ARGS=""
else
	echo "usage: lcov.sh gcc|clang"
	echo -e "\tInvalid argument!"
	exit 2
fi

BUILD_POSTFIX="$2"

cd "build$BUILD_POSTFIX"
lcov -d . --capture -o coverage.info $LCOV_ARGS
lcov -r coverage.info \
	"/usr/include/*" \
	"*cpputest*" \
	-o filtered.info $LCOV_ARGS
genhtml -o coverage filtered.info --demangle-cpp
# rm coverage.info filtered.info
