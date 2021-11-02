#!/bin/bash

NC="\033[0m"
BOLD="\033[1m"
ULINE="\033[4m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
MAGENTA="\033[35m"

SEP_S="_______________________"
SEP_XS="---------"
SEP_L="-----------------------------------------"

printf "${RED}.........................................................\n"
printf "${MAGENTA}\
 ___  ________ _   _ _____ _____ _   _ _____ _     _     
 |  \/  |_   _| \ | /  ___|_   _| | | |  ___| |   | |    
 | .  . | | | |  \| \ \`--.  | | | |_| | |__ | |   | |    
 | |\/| | | | | . \` |\`--. \ | | |  _  |  __|| |   | |    
 | |  | |_| |_| |\  /\__/ /_| |_| | | | |___| |___| |____
 \_|  |_/\___/\_| \_|____/ \___/\_| |_|____/\_____|_____/\n"
printf "${RED}.........................................................\n${NC}"

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

    # rm ./minishell > /dev/null 2>&1
    rm out.txt > /dev/null 2>&1
    touch out.txt > /dev/null
    chmod 777 out.txt > /dev/null
    # make -C ../ > /dev/null 2>&1
    # cp ../minishell . > /dev/null 2>&1

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
    printf "%s%s Output\n" $SEP_XS $SEP_L >> out.txt
    echo $@ | $MINISHELL >> out.txt 2>&1
    printf "\$\n" >> out.txt 
    printf "%s Expected output \n" $SEP_L >> out.txt
    $@ >> out.txt 2>&1    
    printf "\$\n" >> out.txt 
}

function test_all()
{
    display_command $@
    printf "$SEP_S Test: 0$TESTS_NB  $SEP_S\n" >> out.txt
    test_output $@
    let "TESTS_NB++"

}

test_init

# ECHO TESTS
test_all 'echo test tout'
test_all 'echo test      tout'
test_all 'echo -n test tout'
test_all 'echo -n -n -n test tout'
