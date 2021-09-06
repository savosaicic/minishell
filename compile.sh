NC="\033[0m"
BOLD="\033[1m"
ULINE="\033[4m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
MAGENTA="\033[35m"

make 
status=$?

if [ $status -eq 0 ]
then
	printf "${GREEN}Run minishell =======================================\n${NC}"
	./minishell
	# echo $status
else
	printf "${RED}ERROR during compilation ============================\n${NC}"
fi