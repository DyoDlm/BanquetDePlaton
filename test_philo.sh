#!/bin/bash

BIN="./philo"
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

check_executable() {
	if [ ! -x "$BIN" ]; then
		make dbug || (echo "Compilation failed, wtf" && exit 1)
	fi
}

print_head(){
	TEST_NAME="$*"
	echo -e "\nRunning test: $TEST_NAME${NC}"
}

run_test() {
	$BIN "$@" > log.txt &
	PID=$!
	while kill -0 $PID 2>/dev/null; do
		sleep 0.1
	done

	if grep -iq "died" log.txt || grep -iq "DIED" log.txt; then
		echo -e "test [$n] : ${RED}[KO]${NC}"
	else
		cat log.txt | grep "ALL PHILO"
		if [ $? != 0 ]; then
			echo "${YELLOW}WARNING ALL PHILO MAY NOT HAVE EATEN MAX_EAT"
		fi
		echo -e "test [$n] : ${GREEN}[OK]${NC}"
	fi
	rm log.txt
}

loop_the_test() {
	n=0
	for i in {1..10}; do
		n=$i
		run_test "$@"
	done
}

do_test() {
	print_head "$@"
	loop_the_test "$@"
}

check_executable

echo "==== Testing Philosopher Program ===="

# Tests 100%
#echo -e "\nTesting 100% SUCCESS RATE"
#do_test 5 800 200 200 10

# Test 80-90%
#echo -e "\nTesting 80-90% SUCCESS RATE"
#for ARGS in \
#	"131 610 200 200 10" \
#	"131 610 200 200 10" \
#	"131 601 200 200 10" \
#	"198 610 200 200 10" \
#	"198 800 200 200 10"
#do
#	do_test $ARGS
#done

### Test 70-100%
#echo -e "\nTesting 60-70% SUCCESS RATE"
#for ARGS in \
#	"199 610 200 200 10" \
#	"199 601 200 200 10" \
#	"199 610 200 100 10"
#do
#	do_test $ARGS
#done

# Test <= 50 %
echo -e "\nTesting <= 50% SUCCESS RATE"

for ARGS in \
	"50 401 200 200 10" \
	"198 401 200 200 10" 
do
	do_test $ARGS
done

# Test 0%
echo -e "\nTesting 0% SUCCESS RATE"
do_test 130 401 200 200 10
