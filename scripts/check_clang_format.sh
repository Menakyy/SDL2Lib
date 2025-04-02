#!/bin/bash

echo "Checking clang-format compliance..."

unformatted=$(find . -type f \( -name "*.cpp" -o -name "*.h" \) ! -path "./lib/*" ! -path "./build/*" -exec clang-format --dry-run --Werror {} + 2>&1)

if [ -n "$unformatted" ]; then
    echo "$unformatted"
    echo ""
    echo "Some files are not properly formatted. Please run 'make clang-format-all-files'."
    exit 1
else
    echo "All files are properly formatted."
fi
