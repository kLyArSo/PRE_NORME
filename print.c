#include "functions_headerfile.h"

void    print_args(t_arguments   *ptr)//DONT NORM IT
{
    if (ptr != NULL)
    {
        printf("ARGS->");
        while (ptr->next != NULL)
        {
            printf("%s||",ptr->arg);
            ptr = ptr->next;
        }
        printf("%s\n",ptr->arg);
    }
}

void    print_redirections(t_redirections   *ptr)//DONT NORM IT
{
    if (ptr != NULL)
    {
        printf("REDS->");
        while (ptr->next != NULL)
        {
            printf("'%s'--",ptr->redirection_type);
            printf("%s||",ptr->redirection_file);
            ptr = ptr->next;
        }
        printf("'%s'--",ptr->redirection_type);
        printf("%s||\n",ptr->redirection_file);
    }
}

void    print_pipes(t_pipes *ptr)//DONT NORM IT
{
    if (ptr != NULL)
    {
        printf("||||||||||||||||||||||||||||||||\n");
        printf("PIPE START\n");
        while(ptr != NULL)
        {
            printf("\n");
            printf("LINE = %s\n", ptr->line);
            if (ptr->command != NULL)
            printf("CMD = %s\n", ptr->command);
            print_args(ptr->arguments);
            print_redirections(ptr->redirections);
            ptr = ptr->next;
            printf("||||||||||||||||||||||||||||||||\n");
        }
        printf("PIPE END\n");
    }
}

void    print_da(t_format    *ptr)//DONT NORM IT
{
    while (ptr != NULL)
    {
        if (ptr->pipes != NULL)
            print_pipes(ptr->pipes);
        else if (ptr->pipes == NULL)
        {
            printf("\n");
            printf("LINE = %s\n", ptr->pre_pipe_line);
            printf("CMD = %s\n", ptr->command);
            print_args(ptr->arguments);
            print_redirections(ptr->redirections);
        }
        printf("-------------------------------\n");
        ptr = ptr->next;
    }
}