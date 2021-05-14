#include "functions_headerfile.h"

void    data_init(t_linedata *data)
{
    data->command = 0;
    data->argument = 0;
    data->redirection = 0;
    data->redirection_file = 0;
}

int     skip_irr(char   *input, int i)
{
    while(input[i] != 0
        && ((ft_test_char("<>\'\"|;",input[i]) == 0 && is_white_space(input[i]) == 0)
        || ((ft_test_char("<>\'\"|;",input[i]) == 1 || is_white_space(input[i]) == 1)
        && back_slash_presence(input, i - 1) == 1)))
            i++;
    return (i);
}

void    data_init0(t_bag *data)
{
    data->i = 0;
    data->start = 0;
    data->cmd_check = 0;
}

t_tools     *initialise_box(t_tools     *box, char *slice)
{
    box = malloc(sizeof(t_tools));
    box->i = 0;
    box->j = 0;
    box->n = 0;
    box->counter = 0;
    box->len = ft_strlen(slice) + 1;
    box->ret = my_calloc(box->len);
    return (box);
} 