#!/bin/bash
#https://linuxize.com/post/bash-check-if-file-exists/
	# echo ${#d_prev[@]}
	# echo ${d_prev[@]}

#for MAC_OS: stat -f "%m" -t "%Y" $file

NC="\033[0m"
BOLD="\033[1m"
ULINE="\033[4m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
MAGENTA="\033[35m"

compile_and_execute()
{
	status=$?
	if [ $status -eq 0 ]
	then
		clear
		# printf "${GREEN}Compilation $exec_name success\nRun ${exec_name}\n${NC}"
		echo $arguments | ./$exec_name
	else
		printf "${RED}Compilation minishell failure\n${NC}"
	fi
}

get_timestamps()
{
	for file in ${files[@]}
	do
		# timestamp=$(stat -c %Y $file)
		timestamp=$(stat -f "%m" -t "%Y" $file)
		timestamp_prev+=($timestamp)
	done
}

files_path()
{
	directory=$1
	directory+="/*"
	for direct_child in $directory
	do
		if [ -f $direct_child ]
		then
			files+=($direct_child)
		else
			direct_child+="/*.*"
			for indirect_child in $direct_child
			do
				if [ -f $indirect_child ]
				then
					files+=($indirect_child)
				fi
			done
		fi
	done
}

if [ $# -lt 4 ]
then
	printf "autocompile: invalid option\n"
	printf "	${BOLD}autocompile${NC}  [Make path] [Executable Name] [arguments] [Directory(ies) to watch]...\n"
	exit
fi

clear
exec_name=$2
working_directory=$1
watching_directory=$4
arguments=$3

files_path $watching_directory # >>> files[]
get_timestamps # >>> timestamp_p

# if -z ${#files[@]} ] || [ -z $timestamp ]
# then
# 	printf "autocompile: No file to watch\n"
# 	exit
# fi

while true
do

	timestamp_act=$(stat -f "%m" -t "%Y" test.sh)
	if [ $timestamp_act -gt ${timestamp_prev[i]} ]
	then
		pkill -9 $exec_name
		timestamp_prev[i]=$timestamp_act
		compile_and_execute
	fi
	sleep 1
done
