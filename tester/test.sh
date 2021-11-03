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
SEP_XL="————————————————————————————————————————————————————-"
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
    # CMD_PRINT=""
    TESTS_NB=0
    TEST_OUT=0
    MINISHELL=./minishell
    FD_OUT=out.txt
    FD_OUTPUT=output.txt
    FD_OUTPUT_EXP=output_expected.txt
    EXIT_ST=0
    EXIT_ST_EXP=0

    clear

    rm ./minishell > /dev/null 2>&1
    rm output.txt output_expected.txt > /dev/null 2>&1
    rm out.txt > /dev/null 2>&1
    
    cp ../minishell . > /dev/null 2>&1
    if [ ! -x $MINISHELL ] ; then
        printf "${RED}tester: ./minishell not found\n${NC}"
        exit 1
    fi
}

function test_end()
{
    printf "${BLUE}%s" $SEP_XL
    printf "\nSummary: %s/%s\n\n${NC}" $TEST_OUT $TESTS_NB
    rm output.txt output_expected.txt \> \< ls lol test test\; > /dev/null 2<&1
}

function test_exit_status()
{
    if [ "$EXIT_ST" == "$EXIT_ST_EXP" ] ; then
        printf "${GREEN}EXIT[OK]${NC}"
    else
        printf "${RED}EXIT[KO]${NC}"
    fi
}

function test_output()
{
    (echo -e "$CMD_MINISHELL" | $MINISHELL) > $FD_OUTPUT 2>&1 ; EXIT_ST=$?
    (bash -c "$CMD_BASH") > $FD_OUTPUT_EXP 2>&1 ; EXIT_ST_EXP=$?

    if [ "$EXIT_ST_EXP" == 0 ] ; then
        if diff $FD_OUTPUT $FD_OUTPUT_EXP > /dev/null ; then
            printf "${GREEN}OUTPUT[OK]${NC}"
            ((TEST_OUT++))
        else
            printf "${RED}OUTPUT[KO]${NC}"
        fi
    elif [ "$EXIT_ST" != 0 ] && [ "$EXIT_ST_EXP" != 0 ] ; then
        printf "${GREEN}OUTPUT[OK]${NC}"
        ((TEST_OUT++))
    else 
        printf "${RED}OUTPUT[KO]${NC}"
    fi
    printf " | "
}

function save_output()
{
    printf "%s\n" $SEP_XL  >> out.txt
    printf "%20s Test: 0$TESTS_NB %20s\n" >> out.txt
    printf "%s\n" $SEP_XL  >> out.txt

    printf "minishell: %s\n" "$CMD_BASH">> $FD_OUT
    (echo -e "$CMD_MINISHELL" | $MINISHELL) >> $FD_OUT 2>&1 ; exit_status=$?
    printf "$%d\n" $exit_status >> $FD_OUT
    printf "_____________________________________________________\n" >> $FD_OUT
    printf "bash: %s\n" "$CMD_BASH" >> $FD_OUT
    (bash -c "$CMD_BASH") >> $FD_OUT 2>&1 ; exit_status=$?
    printf "$%d\n" $exit_status >> $FD_OUT
}

function test_all()
{
    CMD_MINISHELL="$@"
    CMD_BASH=$(echo -e "$CMD_MINISHELL" | tr '\n' ';' | sed -e 's/.$//g')

    printf "${YELLOW}• 0%d: \'%s\'${NC}\n" "$TESTS_NB" "$CMD_BASH"
    save_output
    test_output
    test_exit_status

    ((TESTS_NB++))
    printf "\n"
}

test_init 

# ECHO TESTS
test_all 'echo test tout'
test_all 'echo test      tout'
test_all 'echo -n test tout'
test_all 'echo -n -n -n test tout'
printf "\n"

# CD TESTS
test_all 'cd .. \n pwd'
test_all 'cd /Users \n pwd'
test_all 'cd \n pwd'
printf "\n"


# PIPE TESTS
test_all 'cat assets/jul.txt | grep organisee | cat -e'
# test_all 'echo test | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e| cat -e| cat -e| cat -e| cat -e| cat -e| cat -e| cat -e| cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e'
test_all 'cat /dev/random | head -c 100 | wc -c'
# test_all 'ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls'
printf "\n"

# EXPANSION
TEST="Hasta luego"
test_all 'echo $TEST'
test_all 'echo "$TEST"'
test_all "echo '$TEST'"
test_all 'echo "$TEST$TEST$TEST"'
test_all 'echo "$TEST$TEST=lol$TEST"'
test_all 'echo "   $TEST lol $TEST"'
test_all 'echo $TEST$TEST$TEST'
test_all 'echo $TEST$TEST=lol$TEST""lol'
test_all 'echo    $TEST lol $TEST'
test_all 'echo test "" test "" test'
test_all 'echo "$=TEST"'
test_all 'echo "$"'
test_all 'echo "$?TEST"'
test_all 'echo $TEST $TEST'
test_all 'echo "$1TEST"'
test_all 'echo "$T1TEST"'
printf "\n"

# REDIRECTIONS
test_all 'echo test > ls \n cat ls'
test_all 'cat jul.txt > minishell_out \n cat minishell_out \n rm minishell_out'
test_all 'echo test > ls >> ls >> ls \n echo test >> ls\n cat ls'
test_all '> lol echo test lol \n cat lol'
test_all '>lol echo > test>lol>test>>lol>test mdr >lol test >test\n cat test'
test_all 'cat < ls'
test_all 'cat < ls > ls'

# ENV EXPANSIONS 
# ...
#

# EXIT
test_all "exit 42"
test_all "exit 42 53 68"
test_all "exit 259"
test_all "exit 9223372036854775807"
test_all "exit -9223372036854775808"
test_all "exit 9223372036854775808"
test_all "exit -9223372036854775810"
test_all "exit -4"
test_all "exit wrong"
test_all "exit wrong_command"
test_all "gdagadgag"
test_all "ls -Z"
test_all "cd gdhahahad"
test_all "ls -la | wtf"
printf "\n"

# GOINFRE
test_all 'echo testing multi \n echo "test 1 \n | and 2" \n cat assets/jul.txt | grep organisee'
test_all '\n\n test'
test_all 'not a command'
test_all '| test'
test_all 'echo > <'
test_all 'echo | |'
test_all '<'
printf "\n"


test_end