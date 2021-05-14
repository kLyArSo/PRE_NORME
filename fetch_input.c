#include "functions_headerfile.h"

ssize_t     ft_strlen(char  *string)
{
    int     i;

    i = 0;
    if (string == NULL)
        return (-1);
    while (string[i] != 0)
        i++;
    return (i);
}

char    *my_calloc(int length)
{
    int     i;
    char    *result;
    
    i = 0;
    result = malloc(length);
    if (result == NULL)
        return (NULL);
    while (i < length)
    {
        result[i] = '\0';
        i++;
    }
    return (result);
}

char    *my_realloc(char    *str, char  c)
{
    ssize_t     length;
    char        *result;
    int         i;

    i = 0;
    if (str == NULL)
        return (NULL);
    length = ft_strlen(str) + 2;
    result = my_calloc(length);
    while (str[i] != 0)
    {
        result[i] = str[i];
        i++;
    }
    result[i] = c;
    free(str);
    str = NULL;
    return (result);
}

int     my_strcmp(char  *s1, char   *s2)
{
    int a;
    int b;
    int i;

    i = 0;
    if (s1 == NULL || s2 == NULL)
        return (-1);

    a = ft_strlen(s1);
    b = ft_strlen(s2);
    if (a != b)
        return (1);
    else
    {
        while (s1[i] != 0 && s2[i] != 0 && s1[i] == s2[i])
            i++;
        if (s1[i] != s2[i])
            return (1);
        else
            return (0);
    }
}

char    *fetch_input()
{
    char    *input;
    char    c;

    input = my_calloc(1 * sizeof(char));
    if (input == NULL)
        return (NULL);
    while (read(1, &c, 1) == 1 && c != '\n')
    {
        input = my_realloc(input, c);
        if (input == NULL)
            return (NULL);    
    }
    return (input);
}