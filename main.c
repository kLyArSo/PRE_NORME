#include "functions_headerfile.h"


void    ft_execution(char        **env, t_format    *ptr)
{
    while   (ptr != NULL)
    {
        purge(env, ptr);//replaces dollarsign and quotes
        //execute(env, ptr); //aymen function
        ptr = ptr->next;
    }
}

int     main(int    argc, char      **argv, char        **env)
{
    char        *input;
    t_format    *ptr;

    while (1)
    {
        ptr = malloc(sizeof(t_format));
        if (termcaps(ptr, env) == NULL)//formatted data is now stored in ptr
            continue ;
    }
}