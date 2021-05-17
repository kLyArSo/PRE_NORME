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
int     fetch_char(struct termios *old)
{
	char    c;
	int		summ;
	struct	termios term; //, init; //init made to reset to default
	
	tcgetattr(0, &term); //get terminal attributes and store them in in the struct
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
	tcsetattr(0, TCSANOW, old);
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

int		all_sp(char	*str)
{
	int i;

	i = 0;
	while(str[i] != 0 && str[i] == ' ')
		i++;
	if (str[i] == 0)
		return (1);	//if full of white_sp
	return (0);		//if isnt full of white_sp
}