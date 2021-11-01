#!/bin/bash

NC="\033[0m"
BOLD="\033[1m"
ULINE="\033[4m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
MAGENTA="\033[35m"

SEP_SMALL="_______________________"
SEP_BIG="-----------------------------------------"

function display_command()
{
    printf "${YELLOW}• \'$@\'${NC}\n"
}

function red()
{
    printf "${RED}$@${NC}"
}

function test_init()
{
    TESTS_NB=0
	TESTS_OK=0
	TESTS_KO=0
	TESTS_LK=0
    MINISHELL="./minishell"
    OUTPUT=
    INPUT=

    rm ./minishell > /dev/null 2>&1
    rm out.txt > /dev/null 2>&1
    touch out.txt > /dev/null
    chmod 777 out.txt > /dev/null
    make -C ../ > /dev/null 2>&1
    cp ../minishell . > /dev/null 2>&1

    if [ "$1" == "1" ]; then
        printf "tester:" red "Error" "\n"
        exit 1
    fi
}

function test_end()
{
    rm $MINISHELL

}

function test_output()
{
    printf "Outpupt -------$SEP_BIG\n" >> out.txt
    echo $@ | $MINISHELL >> out.txt 2>&1
    printf "\nExpected output $SEP_BIG\n" >> out.txt
    $@ >> out.txt 2>&1    
}

function test_all()
{
    display_command $@
    printf "$SEP_SMALL Test: 0$TESTS_NB  $SEP_SMALL\n " >> out.txt
    test_output $@
    let "TESTS_NB++"

}

test_init

# ECHO TESTS
# test_all 'echo test tout'
# test_all 'pwd'
./command.sh