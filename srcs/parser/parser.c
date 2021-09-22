#include "minishell.h"


// ${VAR} == $VAR <----- access var
// $(VAR) == VAR  <----- execute cmd


// static  *t_lst
char *clean_command_line(char *line_buff)
{
    char *line_clean;
    t_list *var_lst;
    t_var  *var;

    // var = malloc(sizeof(*var));
    // if (!var)
        // return (NULL);
    // var_lst = malloc(sizeof(*var_lst));
    // var_lst->next = NULL;
    int i;

    i = 0;
    while (is_space(line_buff[i]))
        i++;
    while (line_buff[i])
    {
        if (line_buff[i] == '$' && line_buff[i] == '(')
            ft_lstadd_back(&cmd_lst, ft_lstnew((void *)cmd));

    }
    printf("VAR line %s\n", line_buff + i);

    printf("VAR len %ld\n", ft_strlen(line_buff));
    exit(0);
    return (line_clean);
}