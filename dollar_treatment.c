#include "functions_headerfile.h"

int     test_c(char c)
{
    if ((c >= 'a' && c <= 'z')
    || (c >= 'A' && c <= 'Z')
    || (c >= '0' && c <= '9')
    || (c == '_'))
        return (1);
    return (0);
}

ssize_t     find_valid_dollar(char *slice)// returns index of the first valid dollar sign
{
    int i;
    char c;

    i = 0;
    while (slice[i] != 0)
    {
       while (slice[i] != 0
        && ((ft_test_char("\'\"$", slice[i]) == 0)
        || (ft_test_char("\'\"$", slice[i]) == 1 && back_slash_presence(slice, i - 1) == 1)))
            i++;
        if (ft_test_char("\'\"", slice[i]) == 1)
            i = skip_quotes(slice, i) + 1;
        if (slice[i] == '$' && back_slash_presence(slice, i - 1) == 0)
            return (i);
        if (slice[i] != 0)
            i++;
    }
    return (-1);
}

char    *fetch_var_name(char *slice, int i) //return the variable name
{
    int start;
    int end;
    char *result;

    start  = i;
    while (slice[i] != 0 && test_c(slice[i]) == 1)
        i++;
    end = i - 1;
    result = ft_substr(slice, start, end);
    return (result);
}

char    *ft_strjoin_dollar_sign(char *s1, char *s2)
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
    free(s1);
    free(s2);
    s1 = NULL;
    s2 = NULL;
    return(result);
}

char    *var_replacement(t_var_rep *data, char  *slice)//replaces the dollar + variable name with the latters content
{
    char *tmp_1;
    char *tmp_2;

    tmp_1 = ft_substr(slice, 0, data->dollar_position - 1);
    tmp_2 = ft_substr(slice, data->dollar_position + ft_strlen(data->variable_name) + 1, ft_strlen(slice));
    tmp_1 = ft_strjoin_dollar_sign(tmp_1, ft_strdup(data->variable_content));
    tmp_1 = ft_strjoin_dollar_sign(tmp_1, tmp_2);
    return(tmp_1);
}

ssize_t     equal_sign(char     *str)
{
    int i;

    i = 0;
    while(str[i] != 0)
    {
        if (str[i] == '=')
            return (i);
        i++;
    }
    return(-1);
}

t_env       *fetch_all_variables(char **env)
{
    int i;
    int init;
    int equ;
    t_env   *ptr;
    t_env   *ret;

    i = 0;
    init = -1;
    ptr = malloc(sizeof(t_env));
    ret = ptr;
    while (env[i] != NULL)
    {
        equ = equal_sign(env[i]);
        if (equ != -1)
        {
            ptr->var_name = ft_substr(env[i], 0, equ - 1);
            ptr->var_content = ft_substr(env[i], equ + 1, ft_strlen(env[i]));
        }
        else if (equ == -1)
        {
             ptr->var_name = ft_strdup(env[i]);
             ptr->var_content = ft_strdup("");
        }
        if (env[++i] != NULL)
        {
            ptr->next = malloc(sizeof(t_env));
            ptr = ptr->next;
        }
    }
    return (ret);
}

char    *ft_strdup(char     *str)
{
    char *ret;
    int i;

    if (str == NULL)
        return(NULL);
    i = ft_strlen(str) + 1;
    ret = my_calloc(i);
    if (ret == NULL)
        return (NULL);
    i = 0;
    while (str[i] != 0)
    {
        ret[i] = str[i];
        i++;
    }
    return(ret);
}

char    *fetch_wanted_var(char    *name, t_env   *ptr)
{
    while (ptr != NULL)
    {
        if (strcmp(name, ptr->var_name) == 0)
            return (ft_strdup(ptr->var_content));
        ptr = ptr->next;
    }
    return (NULL);
}


void    print_k(t_env   *ptr)
{
    while(ptr != NULL)
    {
        printf("%s|=|%s\n",ptr->var_name, ptr->var_content);
        ptr = ptr->next;
    }
}

char    *fetch_variable_content(char **env, char    *name)
{
    t_env   *ptr;
    char    *ret;

    ptr = fetch_all_variables(env);
    ret = fetch_wanted_var(name, ptr);
    return (ret);
}

char    *dollar_treatment(char  **env, char *slice)
{
    int i = 0;
    t_var_rep *data;
    
    data = malloc(sizeof(t_var_rep));
    if (data == NULL)
        return (NULL);
    while (slice[i] != 0)
    {
        i = find_valid_dollar(slice);
        if (i == -1)
            break ;
        data->dollar_position = i++;
        if (slice[i] == '?')
        {
            data->variable_name = ft_strdup("?");
            data->variable_content = ft_itoa(g_global.ret);
        }
        else
        {
            data->variable_name = fetch_var_name(slice, i);
            data->variable_content = fetch_variable_content(env, data->variable_name);
        }
        if (data->variable_content == NULL)
            data->variable_content = ft_strdup("");
        slice = var_replacement(data, slice);
        free(data->variable_name);
        data->variable_name = NULL;
        free(data->variable_content);
        data->variable_content = NULL;
    }
    free(data);
    data =  NULL;
    return (slice);
}