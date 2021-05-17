#include "functions_headerfile.h"

void    initialise(t_bag       **bag, t_linedata **data, t_linedata  **tmp)
{
    *bag = (t_bag*)malloc(sizeof(t_bag));
    *data = (t_linedata*)malloc(sizeof(t_linedata));
    *tmp = *data;
    data_init(*data);
    data_init0(*bag);
}

t_linedata      *split_id(char   *input)
{
    t_bag       *bag;
    t_linedata *data;
    t_linedata  *tmp;
    
    initialise(&bag, &data, &tmp);
    while (input[bag->i] != 0)
    {
        bag->i = skip_irr(input, bag->i);
        if (ft_test_char("\'\"",input[bag->i]) == 1)
            bag->i = skip_quotes(input, bag->i);
        else if (ft_test_char("<>",input[bag->i]) == 1)
            data = fetch_red(input, bag, data);
        else if (is_white_space(input[bag->i]) == 1)
            data = w_s(input, bag, data);
        if (input[bag->i] != 0)
            bag->i++;
        if (input[bag->i] == 0)
            eof(input, bag, data);
    }
    return (tmp);
}

char     *parse(char *input, t_format    *ptr)
{
    char *str;
    if (ptr == NULL)
        return (NULL);
    if (input == NULL)
        return (NULL);
    if(strcmp(input, "") == 0)
        return (NULL);
    str = error_check(input);
    if (my_strcmp(str, "Unmatched_Quotes") == 0
        ||my_strcmp(str, "Redirection_error") == 0
        || my_strcmp(str, "Syntax_error") == 0
        || my_strcmp(str, "Back_slash_Error") == 0)
        return (str);
    input = last_check(input);
    if (input == NULL)
        return (NULL);
    if (semicolon_split(ptr, input) == NULL
    || pipe_split(ptr) == NULL)
        return (NULL);
    return ("done");
}