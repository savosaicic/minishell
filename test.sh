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
printf "${YELLOW} ============== UNIT TESTS MINISHELL ==============\n${NC}"

printf "${ULINE}Testing for basic COMMANDS\n${NC}"

printf "○ echo /bin/ls ................................... "
string=$(echo "/bin/ls" | ./minishell)
# echo "/bin/ls" | ./minishell
string_expected=$(/bin/ls)
printf "\n${string}\n"
echo "-------------------"
printf "${string_expected}\n"
# printf "\n${string_expected\n}"
if [ *"$string"* == "$string_expected" ]
then
	printf "${GREEN}OK\n${NC}"
else
	printf "${RED}KO\n${NC}"
fi

printf "○ echo -n hello ................................ "
string=$(echo "echo -n hello" | ./minishell)
string_expected=$(echo -n hello)
if [ "$string" == "$string_expected" ]
then
	printf "${GREEN}OK\n${NC}"
else
	printf "${RED}KO\n${NC}"
fi

printf "\n"


printf "${ULINE}Testing for basic BUILTINS\n${NC}"

printf "○ echo hello ................................... "
string=$(echo "echo hello" | ./minishell)
string_expected=$(echo hello)
if [ "$string" == "$string_expected" ]
then
	printf "${GREEN}OK\n${NC}"
else
	printf "${RED}KO\n${NC}"
fi

printf "○ echo -n hello ................................ "
string=$(echo "echo -n hello" | ./minishell)
string_expected=$(echo -n hello)
if [ "$string" == "$string_expected" ]
then
	printf "${GREEN}OK\n${NC}"
else
	printf "${RED}KO\n${NC}"
fi

printf "\n"

# printf "○ cd ../ ................................ "
# printf "○ cd /Users ................................ "

printf "○ pwd .......................................... "
string=$(echo pwd | ./minishell)
string_expected=$(pwd)
if [ $string == $string_expected ]
then
	printf "${GREEN}OK\n${NC}"
else
	printf "${RED}KO\n${NC}"
fi

printf "\n"


printf "○ export ....................................... "
unset VAR
echo export VAR=variable | ./minishell > /dev/null 2>&1
string=$VAR
if [ "$string" == "variable" ]
then
	printf "${GREEN}OK\n${NC}"
	export_is_valid=1
else
	printf "${RED}KO\n${NC}"
	export_is_valid=0
fi

printf "\n"

printf "○ unset ........................................ "
echo unset VAR | ./minishell > /dev/null 2>&1
string=$VAR
if [[ -z "$string" && $export_is_valid -eq 1 ]]
then
	printf "${GREEN}OK\n${NC}"
else
	printf "${RED}KO\n${NC}"
fi

printf "\n"

printf "○ env .......................................... "
string=$(echo "echo env" | ./minishell)
string_expected=$(env)
if [ "$string" == "$string_expected" ]
then
	printf "${GREEN}OK\n${NC}"
else
	printf "${RED}KO\n${NC}"
fi

# printf "○ exit ....................... \n"

