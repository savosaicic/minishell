# __________________gdb options_________________

define init_gdb
    set history save on
    set pagination off
    set print pretty on
    set confirm off
    set verbose off

    set prompt \033[34m(gdb) \033[0m
    set output-radix 0x10
    set input-radix 0x10
    set height 0
    set width 0
end

define display_lst_var
    print ((t_variable *)$arg0->content)->name
    print ((t_variable *)$arg0->content)->value
    display ((t_variable *)$arg0->content)->name
    display ((t_variable *)$arg0->content)->value
end

define display_lst_var_next
    print ((t_variable *)((t_list *)((t_variable *)($arg0->next)))->content)->name
    print ((t_variable *)((t_list *)((t_variable *)($arg0->next)))->content)->value
    display ((t_variable *)((t_list *)((t_variable *)($arg0->next)))->content)->name
    display ((t_variable *)((t_list *)((t_variable *)($arg0->next)))->content)->value
end

define print_lst_var
    print ((t_variable *)$arg0->content)->name
    print ((t_variable *)$arg0->content)->value
end

define print_lst_var_next
    print ((t_variable *)((t_list *)((t_variable *)($arg0->next)))->content)->name
    print ((t_variable *)((t_list *)((t_variable *)($arg0->next)))->content)->value
end

init_gdb
set follow-fork-mode child
