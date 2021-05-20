#include "functions_headerfile.h"

int			check_neg(int n)
{
	if (n < 0)
		return (1);
	else
		return (0);
}

int			ft_counter(int n)
{
	int i;

	i = 1;
	while (n / 10 != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char		*ft_printneg(unsigned int nb, char *s, int k)
{
	if (s == NULL)
		return (NULL);
	s[k] = '\0';
	s[0] = '-';
	nb = nb * -1;
	k--;
	while (k >= 1)
	{
		s[k] = nb % 10 + '0';
		nb = nb / 10;
		k--;
	}
	return (s);
}

char		*ft_print_pos(int nb, char *s, int j)
{
	if (s == NULL)
		return (NULL);
	j--;
	s[j] = '\0';
	while (j > 0)
	{
		j--;
		s[j] = nb % 10 + '0';
		nb = nb / 10;
	}
	return (s);
}

char				*ft_itoa(int n)
{
	unsigned int	i;
	int				k;
	char			*p;

	i = ft_counter(n) + 1;
	if (check_neg(n) == 1)
	{
		k = i + 1;
		p = malloc(k * sizeof(char));
		if (p == NULL)
			return (NULL);
		p[0] = '-';
		return (ft_printneg((unsigned int)n, p, i));
	}
	else
	{
		k = i;
		p = malloc(k * sizeof(char));
		return (ft_print_pos(n, p, i));
	}
}
