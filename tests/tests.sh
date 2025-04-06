#!/bin/bash
# Test script for a program with test cases
# Usage: ./test_script.sh <program_path> <test_cases_file>

# Check if both arguments are provided
if [ $# -lt 2 ]; then
    echo "Error: Insufficient arguments!"
    echo "Usage: $0 <program_path> <test_cases_file>"
    exit 1
fi

PROGRAM_PATH="$1"
TESTS_FILE="$2"

# Check if program file exists
if [ ! -f "$PROGRAM_PATH" ]; then
    echo "Error: Program file '$PROGRAM_PATH' not found!"
    exit 1
fi

# Check if tests file exists
if [ ! -f "$TESTS_FILE" ]; then
    echo "Error: Test cases file '$TESTS_FILE' not found!"
    echo "Please create a tests file with shuffle and solution pairs."
    echo "Format: 'shuffle_sequence , expected_solution'"
    exit 1
fi

# Copy the program to current directory
rm curr_prog*
cp "$PROGRAM_PATH" curr_prog.cpp

# Compile the program
echo "Compiling program..."
g++ -std=c++17 -Wall -Wextra -O2 curr_prog.cpp -o curr_prog
if [ $? -ne 0 ]; then
    echo "Error: Compilation failed!"
    exit 1
fi
echo "Compilation successful."

# Count total number of tests
total_tests=$(grep -c "" "$TESTS_FILE")

# Function to verify a solution
verify_solution() {
    local shuffle="$1"
    local expected_solution="$2"
    
    # Run the program and capture the output
    output=$(./curr_prog --shuffle "$shuffle" --use_hash)
    
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