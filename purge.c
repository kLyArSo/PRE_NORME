#include "functions_headerfile.h"


void    cleanse_yes_pipes(char        **env, t_format    *ptr)
{
    t_pipes         *tmp_pipes;
    t_arguments     *tmp_args;
    t_redirections  *tmp_redirections;

    tmp_pipes = ptr->pipes;
    while(tmp_pipes != NULL)
    {
        tmp_pipes->command = dollar_treatment(env, tmp_pipes->command);
        tmp_pipes->command = quote_slash(tmp_pipes->command);
        tmp_args = tmp_pipes->arguments;
        while (tmp_args != NULL)
        {
            tmp_args->arg = dollar_treatment(env,  tmp_args->arg);
            tmp_args->arg = quote_slash( tmp_args->arg);
            tmp_args = tmp_args->next;
        }
        tmp_redirections = tmp_pipes->redirections;
        while (tmp_redirections != NULL)
        {
            tmp_redirections->redirection_type = dollar_treatment(env, tmp_redirections->redirection_type);
            tmp_redirections->redirection_type = quote_slash(tmp_redirections->redirection_type);
            tmp_redirections->redirection_file = dollar_treatment(env, tmp_redirections->redirection_file);
            tmp_redirections->redirection_file = quote_slash(tmp_redirections->redirection_file);
            tmp_redirections = tmp_redirections->next;
        }
        tmp_pipes = tmp_pipes->next;
    }
}

void    cleanse_no_pipes(char        **env, t_format    *ptr)
{
    t_arguments     *tmp_args;
    t_redirections  *tmp_redirections;
    
    ptr->command = dollar_treatment(env, ptr->command);
    ptr->command = quote_slash(ptr->command);
    tmp_args = ptr->arguments;
    while (tmp_args != NULL)
    {
        tmp_args->arg = dollar_treatment(env,  tmp_args->arg);
        tmp_args->arg = quote_slash( tmp_args->arg);
        tmp_args = tmp_args->next;
    }
    tmp_redirections = ptr->redirections;
    while (tmp_redirections != NULL)
    {
        tmp_redirections->redirection_type = dollar_treatment(env,  tmp_redirections->redirection_type);
        tmp_redirections->redirection_type = quote_slash( tmp_redirections->redirection_type);
        tmp_redirections->redirection_file = dollar_treatment(env,  tmp_redirections->redirection_file);
        tmp_redirections->redirection_file = quote_slash( tmp_redirections->redirection_file);
        tmp_redirections = tmp_redirections->next;
    }
}

void    purge(char        **env, t_format    *ptr)
{
    if (ptr->pipes == NULL)//no pipes
        cleanse_no_pipes(env, ptr);
    else if (ptr->pipes != NULL)//yes pipes
        cleanse_yes_pipes(env, ptr);
}