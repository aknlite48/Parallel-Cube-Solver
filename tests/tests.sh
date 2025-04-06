#!/bin/bash
# Test script for cube solver
# Tests the solver with different input sequences from a specified tests file

# Default tests file
TESTS_FILE="tests.txt"

# Check if a file name was provided as argument
if [ $# -ge 1 ]; then
    TESTS_FILE="$1"
fi

# Compile the program
rm 3cube_solver.cpp
rm Makefile
cp ../3cube_solver.cpp .
cp ../Makefile .
make clean
make

# Check if tests file exists
if [ ! -f "$TESTS_FILE" ]; then
    echo "Error: $TESTS_FILE file not found!"
    echo "Please create a tests file with shuffle and solution pairs."
    echo "Format: 'shuffle_sequence , expected_solution'"
    exit 1
fi

# Count total number of tests
total_tests=$(grep -c "" "$TESTS_FILE")

# Function to verify a solution
verify_solution() {
    local shuffle="$1"
    local expected_solution="$2"
    
    # Run the solver and capture the output
    output=$(./3cube_solver --shuffle "$shuffle" --use_hash)
    
    # Extract the solution sequence using grep and sed
    actual_solution=$(echo "$output" | grep -a "Solution sequence:" | sed 's/Solution sequence: //')
    
    # Check if solution matches expected
    if [ "$actual_solution" = "$expected_solution" ]; then
        return 0
    else
        echo -e "\n"  # Clear the progress bar line
        echo "FAIL: Shuffle: $shuffle"
        echo "  Expected: $expected_solution"
        echo "  Got:      $actual_solution"
        return 1
    fi
}

# Function to update progress bar
update_progress() {
    local current=$1
    local total=$2
    local width=50
    local percentage=$((current * 100 / total))
    local completed=$((width * current / total))
    local remaining=$((width - completed))
    
    # Clear the current line
    echo -ne "\r"
    echo -n "["
    printf "%${completed}s" | tr ' ' '#'
    printf "%${remaining}s" | tr ' ' ' '
    echo -n "] $percentage% ($current/$total)"
}

# Run tests until a failure
echo "Running tests from $TESTS_FILE..."
current=0

# Read from specified tests file, preserving special characters
while IFS="," read -r shuffle solution; do
    # Trim whitespace but preserve special characters
    shuffle=$(echo "$shuffle" | sed 's/^[[:space:]]*//;s/[[:space:]]*$//')
    solution=$(echo "$solution" | sed 's/^[[:space:]]*//;s/[[:space:]]*$//')
    
    ((current++))
    update_progress "$current" "$total_tests"
    
    if ! verify_solution "$shuffle" "$solution"; then
        exit 1
    fi
done < "$TESTS_FILE"

# If we get here, all tests passed
echo -e "\nAll tests passed!"
exit 0