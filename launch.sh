#!/bin/bash

SRC_DIR="./srcs"
LOG_DIR="log"
PROG="./philosophers"
LEAKS_CHECK=true

make re


if [ $(uname) = "Linux" ]; then
	LEAKS_CMD="valgrind --leak-check=full --track-fds=yes --show-leak-kinds=all --track-origins=yes --log-file=log/leaks.log" 	  #LEAKS_CMD="$LEAKS_CMD --trace-children=yes"
else
	LEAKS_CMD="leaks -quiet --atExit --"
	LEAKS_CMD=""
fi

norminette_pretty() {
	NORM_ERROR=$(sed -e '/.*: OK!/d' <(norminette $1))
	if [[ $NORM_ERROR == "" ]] ; then
		success "\nNORMINETTE\tOK\n"
	else
		error "\nNORMINETTE\tERROR"
		AWK_SCRIPT='{
			if ($2 == "Error!") {
				filename = $1;
				if (filename == "./src/debug.h:") print "\n[./src/debug.h]\tThe macros bro 🧙🧙🧙"
				else print "";
			} else if (filename != "./src/debug.h:") {
				printf "[%s%d:%d]\t", filename, $4, $6;
				for(i = 7; i <= NF; i++) {
					printf "%s ", $i;
				};
				printf "\n";
			}
		}'
		echo "$NORM_ERROR" | awk "$AWK_SCRIPT"
		echo -e "\n"
	fi
}

