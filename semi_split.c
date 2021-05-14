#include "functions_headerfile.h"

int     skip_quotes(char    *input, int i)
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
    return (i);//position of closing quote
}

char    *trim_spaces(char *input)
{
    int     start;
    int     end;
    char    *result;

    start = 0;
    if (input == NULL)
        return (NULL);
    while(input[start] != 0
    && is_white_space(input[start]) == 1)
        start++;
    end = ft_strlen(input) - 1;
    while (end >= 0
    && is_white_space(input[end]) == 1
    && back_slash_presence(input, end - 1) == 0)
        end--;
    result = ft_substr(input, start, end);
    return(result);
}

void    skip_un(char    *input, int i, int *a)
{
    while(input[i] != 0
    && (ft_test_char("\'\";", input[i]) == 0
    || (ft_test_char("\'\";", input[i]) == 1 && back_slash_presence(input, i - 1) == 1)))
        i++;
    if (ft_test_char("\'\"", input[i]) == 1)
        i = skip_quotes(input, i);
    *a = i;
}

t_format    *fetch(t_format    *ptr, char   *input, int    *start, int i)
{
    ptr->line = trim_spaces(ft_substr(input, *start, i - 1));
    ptr->next = malloc(sizeof(t_format));
    if (ptr->line == NULL || ptr->next == NULL)
        return(NULL);
    ptr = ptr->next;
    *start = i + 1;
    return (ptr);
}

void    *semicolon_split(t_format    *ptr, char     *input)
{
    int     i;
    int start;

    start = 0;
    i = 0;
    while (input[i] != 0)
    {
        skip_un(input, i, &i);
        if (input[i] == ';')
            ptr = fetch(ptr, input, &start, i);
        if (input[i] != 0)
            i++;
        if (input[i] == 0)
        {
            ptr->line = trim_spaces(ft_substr(input, start, i - 1));
            if (ptr->line == NULL)
                return(NULL);
            ptr->next = NULL;
        }
    }
    return ("done");
}

void    printf_individual_lines(t_format    *ptr)
{
    while(ptr->next != NULL)
    {
        printf("<%s>\n", ptr->line);
        ptr = ptr->next;
    }
    printf("<%s>\n", ptr->line);
}

char    *last_check(char *input)
{
    int     start;
    int     end;
    char    *result;

    start = 0;
    if (input == NULL)
        return(NULL);
    while(input[start] != 0
    && is_white_space(input[start]) == 1)
        start++;
    end = ft_strlen(input) - 1;
    while (end >= 0
    && is_white_space(input[end]) == 1
    && back_slash_presence(input, end - 1) == 0)
        end--;
    if (input[end] == ';'
    && back_slash_presence(input, end - 1) == 0)
        end--;
    result = ft_substr(input, start, end);
    return(result);
}