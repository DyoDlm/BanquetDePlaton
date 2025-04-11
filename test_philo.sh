#!/bin/bash

BIN="./philosophers"
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

DFLAGS="valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --errors-for-leak-kinds=all"

check_executable() {
	if [ ! -x "$BIN" ]; then
		make dbug || (echo "compilation failed, wtf" && exit 1)
	fi
}

run_test() {
	TEST_NAME="$*"
	echo -e "\nRunning test: $TEST_NAME${NC}"
	$BIN "$@" > log.txt &
	PID=$!
	sleep 5
	kill $PID 2>/dev/null
	if grep -q "DIED" log.txt; then
		echo -e "${YELLOW}WARNING!
		Result: A philosopher died ${NC}"
	else
		echo -e "${GREEN}SUCCESS!
		Result: No one died ${NC}"
	fi
}

run_helgrind_test() {
	TEST_NAME="$*"
	echo -e "\nRUNNNING HELGRIND: $TEST_NAME${NC}"
	
	$DFLAGS $BIN "$@" > /dev/null 2> valgrind_log.txt &
	PID=$!
	sleep 5
	kill $PID 2>/dev/null

	if grep -1 "ERROR SUMMARY: 0 errors" valgrind_log.txt; then
		echo -e "${GREEN}Helgrind clean mtfak ${NC}"
	else
		echo -e "${RED}ISSUES DETECTED ${NC}"
		grep "==" valgrind_log.txt | grep -v "still reachable"
	fi
}

check_executable

echo "==== Testing Philosopher Program ===="

#	Tests infinis
run_test 2 800 200 200 
run_test 5 800 200 200 
run_test 5 800 200 200 3 
run_test 100 800 200 200 1

#	Tests avec max eat
run_test 1 800 200 200 
run_test 5 310 200 100 
run_test 5 800 200 200 0 
run_test 5 600 200 100 

#	Test avec data races potentielles
run_helgrind_test 2 800 200 200 3
run_helgrind_test 5 800 200 200 3
run_helgrind_test 100 800 200 200 1
