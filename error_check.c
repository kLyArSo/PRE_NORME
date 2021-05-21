#include "functions_headerfile.h"

int     quotes_err(char     *input, int i)
{
    char    c;

    c = input[i];
    i++;
    if (c == '\"')
    {
        while(input[i] != 0 && 
        (input[i] != '\"' || (input[i] == '\"' && back_slash_presence(input, i - 1) == 1)))
            i++;
    }
    else if (c == '\'')
    {
        while(input[i] != 0 && input[i] != '\'')
            i++;
    }
    if (input[i] == '\0')
        return (-1);
    return (i);
}

int     da_loop(char    *input, int i)
{
    while(input[i] != 0
    && (ft_test_char("\\<>\'\"|;",input[i]) == 0 || 
    (ft_test_char("\\<>\'\"|;",input[i]) == 1
    && back_slash_presence(input, i - 1) == 1)))
        i++;
    return (i);
}

char        *error_check(char    *input)
{
    int     i;

    i = 0;
    char *str;
    while (input[i] != 0)
    {
        i = da_loop(input, i);
        if (ft_test_char("\'\"|;<>",input[i]) == 1)
        {
            i = tri(input, i, &str);
            if (i == -1)
            {
                if (my_strcmp(str, "Unmatched_Quotes") == 0
                ||my_strcmp(str, "Redirection_error") == 0
                || my_strcmp(str, "Syntax_error") == 0)
                    return (str);
            }
        }
        else if (input[i] == '\\')
        {
            if (input[i + 1] == 0)
                return (ft_strdupe("Back_slash_Error"));
        }
        if (input[i] != 0)
            i++;
    }
    return ("done");
}

int     tri(char    *input, int i, char **str)
{
    if (ft_test_char("\'\"",input[i]) == 1)
    {
        i = quotes_err(input, i);
        if (i == -1)
            *str = ft_strdupe("Unmatched_Quotes");
    }
    else if (ft_test_char("|;",input[i]) == 1)
    {
        i = parse_error_check(input, i);
        if (i == -1)
        {
            *str = ft_strdupe("Syntax_error");
            g_global.ret = 258;
        }
    }
    else if (ft_test_char("<>",input[i]) == 1)
    {
        i = redirection_error_check(input, i);
        if (i == -1)
        {
            *str = ft_strdupe("Redirection_error");
            g_global.ret = 258;
        }
    }
    return (i);
}

int     parse_error_check(char *input, int i)
{
     if (i == 0 || (input[i] == '|' && input[i+1] == '\0'))
        return (-1);
    i++;
    if (ft_test_char(";|", input[i]) == 1)
        return (-1);
    while (input[i] != 0 && is_white_space(input[i]) == 1)
        i++;
    if (ft_test_char(";|", input[i]) == 1)
        return (-1);
    i--;
    return (i);
}

int     redirection_error_check(char *input, int i)
{
    int start;
    int end;
    char *str;
    int counter;

    counter = 0;
    start = i;
    while (input[i] != 0 && ft_test_char("<>", input[i]) == 1) // skips all redirection parts
        i++;
    end = i - 1;
    str = ft_substr(input, start, end);
    if (my_strcmp(">", str) != 0 && my_strcmp(">>", str) != 0 && my_strcmp("<", str) != 0 && my_strcmp("<>", str) != 0)
        return (-1);
    while (input[i] != 0 && is_white_space(input[i]) == 1) // skips all spaces
    {
        i++;
        counter++;
    }
    return (error_suite(counter, input, i, str));   
}

int     error_suite(int counter, char   *input, int i, char *str)
{
    if (counter != 0)
    {
        if (input[i] == '\0' || input[i] == ';' || input[i] == '|' || ft_test_char("<>", input[i]) == 1)
            return (-1);
    }
    else if (counter == 0)
    {
        if (input[i] == ';' || input[i] == '\0' || input[i] == '|')
            return (-1);
        if (input[i] == '|')
        {
            while(input[i] != 0 && is_white_space(input[i]) == 1)
                i++;
            if (input[i] == '\0' || ft_test_char("<>", input[i]) == 1)
                return (-1);
        }
    }
    return (i - 1);
}