#include "minishell.h"

void test_readline()
{
	char *str;

	str = malloc(50);
	str = readline( "bash$ " );
	printf("result %s", str);
}
