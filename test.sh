#!/bin/bash

NC="\033[0m"
BOLD="\033[1m"
ULINE="\033[4m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
MAGENTA="\033[35m"

clear
count_tests=0
count_valid_test=0
printf "${YELLOW}=========== INTEGRATION TESTS MINISHELL ===========\n\n${NC}"



printf "${ULINE}${BOLD}Testing for basic COMMANDS\n${NC}" ################################

printf "○ ls ........................................... "
let "count_tests=count_tests+1"
string=$(echo "ls" | ./minishell)
string_expected=$(ls)
if [[ "$string" == *"$string_expected"* ]]
then
	printf "${GREEN}OK\n${NC}"
	let "count_valid_test=count_valid_test+1"
else
	printf "${RED}KO\n${NC}"
fi

printf "○ ls -l ........................................ "
let "count_tests=count_tests+1"
string=$(echo "ls -l" | ./minishell)
string_expected=$(ls -l)
if [[ "$string" == *"$string_expected"* ]]
then
	printf "${GREEN}OK\n${NC}"
	let "count_valid_test=count_valid_test+1"
else
	printf "${RED}KO\n${NC}"
fi



printf "○ ls -la Makefile .............................. "
let "count_tests=count_tests+1"
string=$(echo "ls -la Makefile" | ./minishell >/dev/null)
string_expected=$(ls -la Makefile >/dev/null)
if [[ "$string" == *"$string_expected"* ]]
then
	printf "${GREEN}OK\n${NC}"
	let "count_valid_test=count_valid_test+1"
else
	printf "${RED}KO\n${NC}"
fi

printf "○ ls -la donotexit ............................. "
let "count_tests=count_tests+1"
string=$(echo "ls -la donotexit" | ./minishell 2>/dev/null)
string_expected=$(ls -la donotexit 2>/dev/null)
if [[ "$string" == *"$string_expected"* ]]
then
	printf "${GREEN}OK\n${NC}"
	let "count_valid_test=count_valid_test+1"
else
	printf "${RED}KO\n${NC}"
fi

printf "\n"


printf "${ULINE}${BOLD}Testing for basic BUILTINS\n${NC}" ################################

printf "○ echo hello ................................... "
let "count_tests=count_tests+1"
string=$(echo "echo hello" | ./minishell)
string_expected=$(echo hello)
if [ "$string" == "$string_expected" ]
then
	printf "${GREEN}OK\n${NC}"
	let "count_valid_test=count_valid_test+1"
else
	printf "${RED}KO\n${NC}"
fi

printf "○ echo -n hello ................................ "
let "count_tests=count_tests+1"
string=$(echo "echo -n hello" | ./minishell)
string_expected=$(echo -n hello)
if [ "$string" == "$string_expected" ]
then
	printf "${GREEN}OK\n${NC}"
	let "count_valid_test=count_valid_test+1"
else
	printf "${RED}KO\n${NC}"
fi

# printf "○ cd ../ ................................ "
# printf "○ cd /Users ................................ "

printf "○ pwd .......................................... "
let "count_tests=count_tests+1"
string=$(echo pwd | ./minishell)
string_expected=$(pwd)
if [ "$string" == "$string_expected" ]
then
	printf "${GREEN}OK\n${NC}"
	let "count_valid_test=count_valid_test+1"
else
	printf "${RED}KO\n${NC}"
fi

printf "○ export ....................................... "
let "count_tests=count_tests+1"
unset VAR
echo export VAR=variable | ./minishell > /dev/null 2>&1
string=$VAR
if [ "$string" == "variable" ]
then
	printf "${GREEN}OK\n${NC}"
	let "count_valid_test=count_valid_test+1"
	export_is_valid=1
else
	printf "${RED}KO\n${NC}"
	export_is_valid=0
fi

printf "○ unset ........................................ "
let "count_tests=count_tests+1"
echo unset VAR | ./minishell > /dev/null 2>&1
string=$VAR
if [[ -z "$string" && $export_is_valid -eq 1 ]]
then
	printf "${GREEN}OK\n${NC}"
	let "count_valid_test=count_valid_test+1"
else
	printf "${RED}KO\n${NC}"
fi

printf "○ env .......................................... "
let "count_tests=count_tests+1"
string=$(echo "echo env" | ./minishell)
string_expected=$(env)
if [ "$string" == "$string_expected" ]
then
	printf "${GREEN}OK\n${NC}"
	let "count_valid_test=count_valid_test+1"
else
	printf "${RED}KO\n${NC}"
fi

# printf "○ exit ....................... \n"

printf "\n\n${BOLD}${ULINE}${RED}TOTAL: ${count_valid_test}/${count_tests}\n${NC}"