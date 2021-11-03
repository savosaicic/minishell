#!/bin/bash

### CONSTANT

## COLOR
NC="\033[0m"
BOLD="\033[1m"
ULINE="\033[4m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
MAGENTA="\033[35m"

# STRING
SEP_S="_______________________"
SEP_XS="........."
SEP_L="........................................."
HEADER="${MAGENTA}\
 ___  ________ _   _ _____ _____ _   _ _____ _     _     
 |  \/  |_   _| \ | /  ___|_   _| | | |  ___| |   | |    
 | .  . | | | |  \| \ \`--.  | | | |_| | |__ | |   | |    
 | |\/| | | | | . \` |\`--. \ | | |  _  |  __|| |   | |    
 | |  | |_| |_| |\  /\__/ /_| |_| | | | |___| |___| |____
 \_|  |_/\___/\_| \_|____/ \___/\_| |_|____/\_____|_____/\n${NC}"

function test_init()
{
    CMD_MINISHELL=""
    CMD_BASH=""
    TESTS_NB=0
    TEST_OUT=0
    MINISHELL=./minishell
    FD_OUT=$PWD/out.txt
    FD_OUTPUT=$PWD/output.txt
    FD_OUTPUT_EXP=$PWD/output_expected.txt

    # rm ./minishell > /dev/null 2>&1
    rm out.txt > /dev/null 2>&1
    touch out.txt > /dev/null
    chmod 777 out.txt > /dev/null
    # make -C ../ > /dev/null 2>&1
    # cp ../minishell . > /dev/null 2>&1
}

function test_end()
{
    rm $MINISHELL

}

function test_output()
{
    printf "${SEP_XS}${SEP_L} Output\n" >> $FD_OUT
    (echo -e "$CMD_MINISHELL" | $MINISHELL) 2>&1 | tee -a $FD_OUT > $FD_OUTPUT 2>&1
    printf "\n" >> $FD_OUT

    printf "$SEP_L Expected output \n" >> $FD_OUT
    (bash -c "$CMD_BASH") 2>&1 | tee -a $FD_OUT > $FD_OUTPUT_EXP 

    if diff $FD_OUTPUT $FD_OUTPUT_EXP > /dev/null ; then
        printf "${GREEN}OUTPUT[OK]${NC}"
        ((TEST_OUT++))
    else
        printf "${RED}OUTPUT[KO]${NC}"
    fi
    printf " | "
}

function test_all()
{
    CMD_MINISHELL="$@"
    CMD_BASH=$(echo -e "$CMD_MINISHELL" | tr '\n' ';' | sed -e 's/.$//g')

    printf "${YELLOW}• \'%s\'${NC}\n" "$CMD_BASH"
    printf "$SEP_S Test: 0%s $SEP_S\n" $TESTS_NB >> out.txt

    test_output

    ((TESTS_NB++))
    printf "\n"
}

test_init 
# ECHO TESTS
# test_all 'echo test tout'
# test_all 'echo test      tout'
# test_all 'echo -n test tout'
# test_all 'echo -n -n -n test tout'

# CD TESTS
# test_all 'cd .. \n pwd \n cd' $PWD
# test_all 'ls'
# test_all 'cd /Users \n pwd' $PWD
# test_all "cd \n pwd"

test_all 'not'
# test_all 'cat test.sh'
