#include "minishell.h"

int env(t_list *env_lst)
{
    print_variables(env_lst);
    return (0);
}