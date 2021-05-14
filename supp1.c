#include "functions_headerfile.h"

t_linedata  *pre_red(char   *input, t_bag   *bag, t_linedata *data)
{
    data->slice = trim_spaces(ft_substr(input, bag->start, bag->i - 1));
    if (my_strcmp(data->slice, "") != 0)
    {
        if (data->redirection_file == 0)
            data->argument = 1;
        if (data->argument == 1 && bag->cmd_check == 0)
        {
            data->command = 1;
            bag->cmd_check = 1;
        }
        data->next = (t_linedata*)malloc(sizeof(t_linedata));
        data = data->next;
        data_init(data);
    }
    else
    {
        free(data->slice);
        data->slice = NULL;
    }
    bag->start = bag->i;
    while (input[bag->i] != 0 && ft_test_char("<>",input[bag->i]) == 1)
        bag->i++;
    return(data);
}

t_linedata  *red(char   *input, t_bag   *bag, t_linedata *data)
{
    data->slice = trim_spaces(ft_substr(input, bag->start, bag->i - 1));
    if (my_strcmp(data->slice, "") != 0)
    {
        data->redirection = 1;
        data->next = (t_linedata*)malloc(sizeof(t_linedata));
        data = data->next;
        data_init(data);
        data->redirection_file = 1;
    }
    else
    {
        free(data->slice);
        data->slice = NULL;
    }
    bag->start = bag->i;
    bag->i--;
    return(data);
}

void    ufo(t_linedata *data)
{
    free(data->slice);
    data->slice = NULL;
}

t_linedata  *w_s(char   *input, t_bag   *bag, t_linedata *data)
{
    data->slice = trim_spaces(ft_substr(input, bag->start, bag->i - 1));
    if (my_strcmp(data->slice, "") != 0)
    {
        if (data->redirection_file == 0)
            data->argument = 1;
        if (data->argument == 1 && bag->cmd_check == 0)
        {
            data->command = 1;
            bag->cmd_check = 1;
        }
        data->next = (t_linedata*)malloc(sizeof(t_linedata));
        data = data->next;
        data_init(data);
    }
    else
        ufo(data);
    while (input[bag->i] != 0 && is_white_space(input[bag->i]) == 1)
        bag->i++;
    bag->start = bag->i;
    bag->i--;
    return (data);
}

void    eof(char   *input, t_bag   *bag, t_linedata *data)
{
    data->slice = trim_spaces(ft_substr(input, bag->start, bag->i - 1));
    if (data->redirection_file == 0)
        data->argument = 1;
    if (data->argument == 1 && bag->cmd_check == 0)
    {
        data->command = 1;
        bag->cmd_check = 1;
    }
    data->next = NULL;
}

t_linedata *fetch_red(char   *input, t_bag   *bag, t_linedata *data)
{
    data = pre_red(input, bag, data);
    data = red(input, bag, data);
    return (data);
}