#include "functions_headerfile.h"

void     treat_slash(char *slice, t_tools   *box)
{
    if (slice[box->i] == '\\')
    {
        while(slice[box->i] != '\0' && slice[box->i] == '\\')
        {
            box->i++;
            box->counter++;
        }            
        if (slice[box->i] == '\"')            
            box->i++;
        box->n = box->counter / 2;
        while (box->n > 0)
        {
            box->ret[box->j] = '\\';
            box->j++;
            box->n--;
        }
        box->counter = 0;
    }
    box->ret[box->j] = slice[box->i];
    box->i++;
    box->j++;
}

void     treat_single_quote(char *slice, t_tools   *box)
{
    while (slice[box->i] != 0 && slice[box->i] != '\'')
    {
        box->ret[box->j] = slice[box->i];
        box->i++;
        box->j++;
    }
}

void    double_q_slash(char *slice, t_tools   *box)
{
    while(slice[box->i] != '\0' && slice[box->i] == '\\')
    {
        box->i++;
        box->counter++;
    }
    if (slice[box->i] != '\"')
        box->counter++;
    else
        box->i++;
    box->n = box->counter / 2;
    while (box->n > 0)
    {
        box->ret[box->j] = '\\';
        box->j++;
        box->n--;
    }
    box->counter = 0;
}

void     treat_double_quote(char *slice, t_tools   *box)
{
    while (slice[box->i] != 0
    && (slice[box->i] != '\"'
    || (slice[box->i] == '\"'
    && back_slash_presence(slice, box->i - 1) == 1)))
    {
        if (slice[box->i] == '\\')
            double_q_slash(slice, box);
        box->ret[box->j] = slice[box->i];
        box->i++;
        box->j++;
    }
}
char    *quote_slash(char *slice)//replace t_line data with return value
{
    t_tools     *box;

    box = initialise_box(box, slice);
    while (slice[box->i] != 0)
    {
        while (ft_test_char("\'\"", slice[box->i]) == 1
        && back_slash_presence(slice, box->i - 1) == 0)
        {
            box->c = slice[box->i];
            box->i++;
            if (box->c == '\'')
                treat_single_quote(slice, box);
            if (box->c == '\"')
                treat_double_quote(slice, box);
            box->i++;
        }
        treat_slash(slice, box);
        
    }
    return (box->ret);
}