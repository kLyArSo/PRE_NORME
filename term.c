#include "functions_headerfile.h"

char    *j_oin(char *s, char c)
{
	int        i;
	char    *ret;
	i = 0;
	if(s == NULL)
	{
		ret = (char *)malloc(2);
		if (ret == NULL)
			return (NULL);
		ret[0] = c;
		ret[1] = '\0';
		return (ret);
	}
	ret = (char *)malloc(ft_strlen(s) + 2);
	if (ret == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = c;
	ret[i + 1] = '\0';
	free(s);
	s = NULL;
	return (ret);
}
int     fetch_char()
{
	char    c;
	int		summ;
	struct termios old;
	struct	termios term; //, init; //init made to reset to default
	
	tcgetattr(0, &old); //get terminal attributes and store them in in the struct
	term = old;
	term.c_lflag &= ~(ICANON|ECHO); //Set to Non Canonical, Reads instantly without waiting for "ENTER" key, Maximum length is 4096
	term.c_cc[VMIN] = 1;  // VMIN   Minimum number of characters for noncanonical read (MIN).
	term.c_cc[VTIME] = 0;  //VTIME Timeout in deciseconds for noncanonical read (TIME).
	tcsetattr(0, TCSANOW, &term); //Set Atrributes of termios (Update Changes)
	
	summ = 0;
	read(0, &c, 1);
	if (c != 27)
		return (c);
	else if (c == 27 && (read(0, &c, 1) != 0 && c == '['))
	{
		summ = 27;
		summ = summ + c;
		read(0, &c, 1);
		summ = summ + c;
	}
	tcsetattr(0, TCSANOW, &old);
	return (summ);
}

char	*ft_strdupe(char	*str)
{
	int i;
	char	*ret;

	i = 0;
	if (str == NULL)
		return (NULL);
	ret = calloc((ft_strlen(str) + 1),sizeof(char));
	if (ret == NULL)
		return (NULL);
	while (str[i] != 0)
	{
		ret[i] = str[i];
		i++;
	}
	return(ret);
}

void		init_lst(t_history	*ptr)
{
	ptr->previous = NULL;
	ptr->next = NULL;
	ptr->line = calloc(1,1);
}

int put_char(int c)
{
	return (write(1,&c,1));
}

char	*delete_char(char	*str)
{
	int i;
	char	*ret;

	if (ft_strlen(str) <= 0)
		return(str);
	ret = malloc(ft_strlen(str));
	i = 0;
	while (str[i] != 0)
	{
		ret[i] = str[i];
		i++;
	}
	ret[i - 1] = 0;
	free(str);
	str = NULL;
	return (ret);
}

void            *termcaps(t_format    *formaptr, char        **env)
{
    int     ascii;
	t_history	*head = malloc(sizeof(t_history));
	t_history	*ptr = head;
	t_history 	*tmp;
	char	*str = calloc(1,1);
	init_lst(ptr);
	char *check;
	int ret = tgetent(getenv("TERM"), NULL);
	write(1, "MY_SHELL~", ft_strlen("MY_SHELL~"));
    while (1)
    {
		ascii = fetch_char();
		if (ascii >= 32 && ascii <= 126)//all printable chars
		{
			str = j_oin(str, ascii);
			write(1, &ascii, 1);
		}
		else if (ascii == DELETE_KEY)//delete char
		{
			if (ft_strlen(str) > 0)
			{
				str = delete_char(str);//deletes last char
				tputs(tgetstr("le",NULL), 1, put_char);//move cursor left
				tputs(tgetstr("dc",NULL), 1, put_char);//delete char
			}
		}
		else if (ascii == ENTER_KEY)//enter
		{
			if (my_strcmp(str, "") != 0)
			{
				if (ptr->next != NULL)
				{
					while (ptr->next != NULL)
						ptr = ptr->next;
				}
				ptr->line = str;
				check = parse(str, formaptr);
				if (my_strcmp(check, "Unmatched_Quotes") == 0
				|| my_strcmp(check, "Back_slash_Error") == 0)
				{
					write(1,"\n>",2);
					continue ;
				}
				else if (my_strcmp(check, "Redirection_error") == 0
        				|| my_strcmp(check, "Parse_error") == 0)
				{
					write(1,"\n",1);
					write(1, check, ft_strlen(check));
					write(1, "\nMY_SHELL~", ft_strlen("\nMY_SHELL~"));
					free(str);
					str = calloc(1,1);
					ptr->line = str;
				}
				else
				{
        			ft_execution(env, formaptr);
					ptr->next = malloc(sizeof(t_history));
					tmp = ptr;
					ptr = ptr->next;
					str = calloc(1,1);
					init_lst(ptr);
					ptr->previous = tmp;
					write(1,"\n",1);
					write(1, "MY_SHELL~", ft_strlen("MY_SHELL~"));
				}
			}
		}
		else if (ascii == UP_KEY)
		{
			tputs(tgoto(tgetstr("ch", NULL), 0, 0), 1, put_char);
			tputs(tgetstr("dl",NULL), 1, put_char);
			write(1, "MY_SHELL~", ft_strlen("MY_SHELL~"));
			if (ptr->previous != NULL)
				ptr = ptr->previous;
			str = ft_strdupe(ptr->line);
			write(1,str, ft_strlen(str));
		}
		else if (ascii == DOWN_KEY)
		{
			tputs(tgoto(tgetstr("ch", NULL), 0, 0), 1, put_char);
			tputs(tgetstr("dl",NULL), 1, put_char);
			
			write(1, "MY_SHELL~", ft_strlen("MY_SHELL~"));
			if (ptr->next != NULL)
				ptr = ptr->next;
			str = ft_strdupe(ptr->line);
			write(1,str, ft_strlen(str));

		}
		/*if (ascii == CTRL_D)
		{
			restore_def_values();
			write(1, "exit\n", ft_strlen("exit\n"));
			exit(0);
		}*/
    }
	return("done");
}