#include "functions_headerfile.h"

int     pipe_presence(char *input)
{
    int     i;
    char    c;

    i = 0;
    while (input[i] != 0)
    {
        while (input[i] != 0
        && (ft_test_char("\'\"|", input[i]) == 0
        || (ft_test_char("\'\"|", input[i]) == 1
        && back_slash_presence(input, i - 1) == 1)))
            i++;
        if (input[i] == '|')
            return (1);
        else if (ft_test_char("\'\"", input[i]) == 1)
            i = skip_quotes(input, i);
        if (input[i] != 0)
            i++;
    }
    return (0);
}

char    *fetch_command(t_linedata *data)
{
    while(data->next != NULL)
    {
        if (data->command == 1)
            return (data->slice);
        data = data->next;
    }
    if (data->command == 1)
        return (data->slice);
    return (NULL);
}
t_arguments     *f_16(t_arguments     *ptr, t_linedata *data)
{
    ptr->next = malloc(sizeof(t_arguments));
    ptr = ptr->next;
    ptr->arg = data->slice;
    ptr->next = NULL;
    return (ptr);
}

t_arguments    *fetch_arguments(t_linedata *data, t_arguments *ret, int counter)
{
    t_arguments     *ptr;

    while(1)
    {
        if (data->command == 0 && data->argument == 1)
        {
            if (counter == 0)
            {
                counter++;
                ptr = malloc(sizeof(t_arguments));
                ret = ptr;
                ptr->arg = data->slice;
                ptr->next = NULL;
            }
            else if (counter == 1)
                ptr = f_16(ptr, data);
        }
        data = data->next;
        if (data == NULL)
            break ;
    }
    return (ret);
}

t_linedata      *a_s(t_linedata *data, t_redirections     *ptr)
{

    ptr->redirection_type = data->slice;
    data = data->next;
    ptr->redirection_file = data->slice;
    ptr->next = NULL;
    return (data);
}

t_redirections    *fetch_redirection(t_linedata *data, t_redirections *ret, int counter)
{
    t_redirections     *ptr;

    while(1)
    {
        if(data->redirection == 1)
        {
            if (counter == 0)
            {
                counter = 1;
                ptr = malloc(sizeof(t_redirections));
                ret = ptr;
                data = a_s(data, ptr);
            }
            else if (counter == 1)
            {
                ptr->next = malloc(sizeof(t_redirections));
                ptr = ptr->next;
                data = a_s(data, ptr);
            }
        }
        data = data->next;
        if (data == NULL)
            break   ;
    }
    return (ret);
}

t_pipes    *f2(t_format    *ptr, int *start, int i)
{
    ptr->pipes->line = trim_spaces(ft_substr(ptr->line, *start, i - 1));
    ptr->pipes->sliced_line = split_id(ptr->pipes->line);
    ptr->pipes->command = fetch_command(ptr->pipes->sliced_line);
    ptr->pipes->redirections = fetch_redirection(ptr->pipes->sliced_line, NULL, 0);
    ptr->pipes->arguments = fetch_arguments(ptr->pipes->sliced_line, NULL, 0);
    ptr->pipes->next = malloc(sizeof(t_pipes));
    *start = i + 1;
    return(ptr->pipes->next);
}

void    f3(t_format    *ptr, int start, int i)
{
    ptr->pipes->line = trim_spaces(ft_substr(ptr->line, start, i - 1));
    ptr->pipes->sliced_line = split_id(ptr->pipes->line);
    ptr->pipes->command = fetch_command(ptr->pipes->sliced_line);
    ptr->pipes->redirections = fetch_redirection(ptr->pipes->sliced_line, NULL, 0);
    ptr->pipes->arguments = fetch_arguments(ptr->pipes->sliced_line, NULL, 0);
    ptr->pipes->next = NULL;
}

int     skips(t_format    *ptr, int i)
{
    while (ptr->line[i] != 0
    && (ft_test_char("\'\"|", ptr->line[i]) == 0
    || (ft_test_char("\'\"|", ptr->line[i]) == 1
    && back_slash_presence(ptr->line, i - 1) == 1)))
        i++;
    if (ft_test_char("\'\"", ptr->line[i]) == 1)
        i = skip_quotes(ptr->line, i);
    return (i);
}

void    ft_end(t_format    *ptr, int *i, int start)
{
    int j;
    
    j = *i;
    if (ptr->line[j] != 0)
        j++;
    if (ptr->line[j] == 0)
        f3(ptr, start, j);
    *i = j;
}

void    *fetch_pipes(t_format    *ptr, int start, int i)
{
    t_pipes *tmp;
    ptr->pipes = malloc(sizeof(t_pipes));
    tmp = ptr->pipes;
    while (ptr->line[i] != 0)
    {
        i = skips(ptr, i);
        if (ptr->line[i] == '|')
        {
            ptr->pipes = f2(ptr, &start, i);
            if (ptr->pipes == NULL)
                return (NULL);
        }
        ft_end(ptr, &i, start);
    }
    ptr->pipes = tmp;
    return ("done");
}

void    assignments(t_format    *ptr)
{
    ptr->pre_pipe_line = ptr->line;
    ptr->sliced_line = split_id(ptr->pre_pipe_line);
    ptr->command = fetch_command(ptr->sliced_line);
    ptr->redirections = fetch_redirection(ptr->sliced_line, NULL, 0);
    ptr->arguments = fetch_arguments(ptr->sliced_line, NULL, 0);
    ptr->pipes = NULL;
}

void        *pipe_split(t_format    *ptr)
{
    while (1)
    {
        ptr->pipe_presence = pipe_presence(ptr->line);
        if (ptr->pipe_presence == 0)
            assignments(ptr);
        else
        {
            ptr->pre_pipe_line = NULL;
            if (fetch_pipes(ptr, 0, 0) == NULL)
                return (NULL);
        }
        ptr = ptr->next;
        if (ptr == NULL)
            break ;
    }
    return ("done");
}
