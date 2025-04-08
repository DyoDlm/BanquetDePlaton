#!/bin/bash

BIN="./philosophers"
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

check_executable() {
	if [ ! -x "$BIN" ]; then
		echo -e "${RED}Error: $BIN not found or not executable.${NC}"
		exit 1
	fi
}

run_test() {
	echo -e "\nRunning test: $*"
	$BIN "$@" > log.txt &
	PID=$!

	sleep 5
	kill $PID 2>/dev/null

	if grep -q "died" log.txt; then
		echo -e "${RED}FAIL!
		Result: A philosopher died ${NC}"
	else
		echo -e "${GREEN}SUCCESS!
		Result: No one died ${NC}"
	fi
}

check_executable

echo "==== Testing Philosopher Program ===="

# BASIC TESTS
run_test 2 800 200 200
run_test 5 800 200 200
run_test 5 800 200 200 3
run_test 100 800 200 200 1

# EDGE CASES
run_test 1 800 200 200
run_test 5 310 200 100
run_test 5 800 200 200 0
run_test 5 600 200 100

#rm -f log.txt
