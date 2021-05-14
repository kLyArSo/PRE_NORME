#include "functions_headerfile.h"

int     ft_test_char(char   *str, char c)
{
    int i;

    i = 0;
    if (str == NULL)
        return (0);
    while (str[i] != 0)
    {
        if (str[i] == c)
            return(1);
        i++;
    }
    return (0);
}

int     is_white_space(char c)
{
    if ((c >= 9 && c <= 13) || c == 32)
        return (1);
    return (0);
}


int     back_slash_presence(char *input, int i)
{
    int counter = 0;
    while(i >= 0 && input[i] == '\\')
    {
        i--;
        counter++;
    }
    return (counter % 2);
}

char    *ft_substr(char *str, int start, int end)
{
    int i;
    char    *result;

    i = 0;
    if (str == NULL)
        return (NULL);
    result = my_calloc(end - start + 2);
    while (start <= end)
    {
        result[i] = str[start];
        start++;
        i++;
    }
    return (result);
}

char    *ft_error(char *str)
{
    write(1, str, ft_strlen(str));
    return (NULL);
}

char    *ft_strjoin(char *s1, char *s2)
{
    int i = 0;
    int j = 0;
    char *result = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
    while (s1[i] != 0)
    {
        result[i] = s1[i];
        i++;
    }
    while (s2[j] != 0)
    {
        result[i] = s2[j];
        i++;
        j++;
    }
    result[i] = 0;
    return(result);
}