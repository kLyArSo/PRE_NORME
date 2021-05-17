#include "functions_headerfile.h"


void    ft_execution(char        **env, t_format    *ptr)
{
    while   (ptr != NULL)
    {
        purge(env, ptr);//replaces dollarsign and quotes
        //execute(env, ptr); //aymen function
        //print_da(ptr);
        ptr = ptr->next;
    }
}

void		*init_all(t_toolbox   *box)
{
    box->formaptr = malloc(sizeof(t_format));
	if (box->formaptr == NULL)
    {
        free(box->formaptr);
        box->formaptr = NULL;
        return (NULL);
    }
    box->ptr = malloc(sizeof(t_history));
    if (box->ptr == NULL)
    {
        free(box->formaptr);
        box->formaptr = NULL;
        free(box->ptr);
        box->ptr = NULL;
        return (NULL);
    }
    box->str = calloc(1,1);
    if (box->str == NULL)
    {
        free(box->formaptr);
        box->formaptr = NULL;
        free(box->ptr);
        box->ptr = NULL;
        free(box->ptr);
        box->str = NULL;
        return (NULL);
    }
    
    box->ptr->previous = NULL;
	box->ptr->next = NULL;
	box->ptr->line = NULL;
    tcgetattr(0, &box->old);
    tgetent(getenv("TERM"), NULL);
    return ("done");
}
void    put_strings(char    *s1, char   *s2, char   *s3, char   *s4)
{
    if (s1 != NULL)
        write(1, s1, ft_strlen(s1));
    if (s2 != NULL)
        write(1, s2, ft_strlen(s2));
    if (s3 != NULL)
        write(1, s3, ft_strlen(s3));
    if (s4 != NULL)
        write(1, s4, ft_strlen(s4));
}
void		init_lst(t_toolbox   *box)
{
    box->ptr->previous = NULL;
	box->ptr->next = NULL;
	box->ptr->line = NULL;
}

void    printable_key(t_toolbox   *box)
{
	box->str = j_oin(box->str, box->ascii);
	write(1, &box->ascii, 1);//exception
}

void    delete_key(t_toolbox   *box)
{
	if (ft_strlen(box->str) > 0)
	{
		box->str = delete_char(box->str);//deletes last char
		tputs(tgetstr("le",NULL), 1, put_char);//move cursor left
		tputs(tgetstr("dc",NULL), 1, put_char);//delete char
	}
}

void    up_key(t_toolbox   *box)
{
	tputs(tgoto(tgetstr("ch", NULL), 0, 0), 1, put_char);
	tputs(tgetstr("dl",NULL), 1, put_char);
    put_strings("MY_SHELL~",NULL,NULL,NULL);
	if (box->ptr->previous != NULL)
		box->ptr = box->ptr->previous;
	box->str = ft_strdupe(box->ptr->line);
    put_strings(box->str,NULL,NULL,NULL);
}

void    down_key(t_toolbox   *box)
{
	tputs(tgoto(tgetstr("ch", NULL), 0, 0), 1, put_char);
	tputs(tgetstr("dl",NULL), 1, put_char);
    put_strings("MY_SHELL~",NULL,NULL,NULL);
	if (box->ptr->next != NULL)
		box->ptr = box->ptr->next;
	box->str = ft_strdupe(box->ptr->line);
    put_strings(box->str,NULL,NULL,NULL);
}

void    ctrl_d_key(t_toolbox   *box)
{
    tcsetattr(0, TCSANOW, &box->old);
    put_strings("\nexit\n",NULL,NULL,NULL);
	exit(0);
}

void    update_position(t_toolbox   *box)
{
    while (box->ptr->next != NULL)
	    box->ptr = box->ptr->next;
}

void    *full_ws_niet(t_toolbox   *box, char    **env)
{
	box->check = parse(box->str, box->formaptr);
	if (my_strcmp(box->check, "Unmatched_Quotes") == 0
	|| my_strcmp(box->check, "Back_slash_Error") == 0)
	{
        put_strings("\n>",NULL,NULL,NULL);
        return (NULL);
	}
	else if (my_strcmp(box->check, "Redirection_error") == 0
			|| my_strcmp(box->check, "Syntax_error") == 0)
	{
        put_strings("\n",box->check,"\nMY_SHELL~",NULL);
		free(box->str);
		box->str = calloc(1,1);
		box->ptr->line = box->str;
	}
	else
	{
		ft_execution(env, box->formaptr);
		box->ptr->next = malloc(sizeof(t_history));
		box->tmp = box->ptr;
		box->ptr = box->ptr->next;
		box->str = calloc(1,1);
		init_lst(box);
		box->ptr->previous = box->tmp;
        put_strings("\nMY_SHELL~",NULL,NULL,NULL);
	}
    return ("done");
}

void    full_ws_da(t_toolbox   *box)
{
	box->ptr->next = malloc(sizeof(t_history));
	box->tmp = box->ptr;
	box->ptr = box->ptr->next;
	box->str = calloc(1,1);
	init_lst(box);
	box->ptr->previous = box->tmp;
    put_strings("\nMY_SHELL~",NULL,NULL,NULL);
}

void    *enter_key(t_toolbox   *box, char        **env)
{
	if (my_strcmp(box->str, "") != 0)
	{
		box->i = all_sp(box->str);
		if (box->ptr->next != NULL)
            update_position(box);
		box->ptr->line = box->str;
		if (box->i == 0)//isnt full of wh_sp
        {
            if (full_ws_niet(box, env) == NULL)
                return (NULL);
        }
		else//is full of wh_sp
            full_ws_da(box);
	}
	else if(my_strcmp(box->str, "") == 0)
        put_strings("\nMY_SHELL~",NULL,NULL,NULL);
    return ("done");
}

int     main(int    argc, char      **argv, char        **env)
{
    t_toolbox   *box = malloc(sizeof(t_toolbox));

    if (box == NULL || init_all(box) == NULL)
        return (1);
    put_strings("MY_SHELL~",NULL,NULL,NULL);
    while (1)
    {
		box->ascii = fetch_char(&box->old);
		if (box->ascii >= 32 && box->ascii <= 126)//all printable chars
            printable_key(box);
		else if (box->ascii == DELETE_KEY)//delete char
            delete_key(box);
		else if (box->ascii == ENTER_KEY)//enter
        {
            if (enter_key(box, env) == NULL)
                continue ;
        }
		else if (box->ascii == UP_KEY)
            up_key(box);
		else if (box->ascii == DOWN_KEY)
            down_key(box);
		else if (box->ascii == CTRL_D)
            ctrl_d_key(box);
    }
    return (0);
}