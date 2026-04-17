#!/bin/bash

# Exit on error
set -e

# Compile the project
echo "Compiling..."
mkdir -p build
cd build
cmake ..
make
cd ..

# Run tests
echo "Running tests..."
for i in 1 2 3 4; do
    echo "=================================="
    echo "Testing benchmark $i"

    # Run the program and redirect output to a temporary file
    ./build/LTL_checker $i > tmp.out

    # Compare with expected output
    if diff -qw tmp.out benchmark/$i.ans > /dev/null; then
        echo "Test $i: PASS"
    else
        echo "Test $i: FAIL"
        echo "Expected:"
        cat benchmark/$i.ans
        echo "Got:"
        cat tmp.out
    fi
done

# Clean up
rm -f tmp.out
rm -rf build
echo "=================================="
echo "All tests completed."
