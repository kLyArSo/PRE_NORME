#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <termios.h>
#include <term.h>
# include <termios.h>
# include <termcap.h>
# define UP_KEY 183
# define DOWN_KEY 184
# define ENTER_KEY 10
# define DELETE_KEY 127
# define CTRL_D 4

typedef struct  s_history
{
    struct  s_history   *previous;
    char    *line;
    struct  s_history   *next;
}   t_history;
typedef struct  s_bag
{
    int                 i;
    int                 start;
    int                 cmd_check;
}   t_bag;

typedef struct  s_env
{
    char    *var_name;
    char    *var_content;
    struct s_env  *next;
}   t_env;

typedef struct  s_linedata
{
    char                *slice;
    int                 command;
    int                 argument;
    int                 redirection;
    int                 redirection_file;
    struct s_linedata  *next;
}   t_linedata;

typedef struct  s_redirections
{
    char                    *redirection_type;
    char                    *redirection_file;
    struct  s_redirections  *next;
}   t_redirections;

typedef struct  s_arguments
{
    char                *arg;
    struct  s_arguments *next;
}   t_arguments;

typedef struct  s_pipes
{
    char                *line;
    t_linedata         *sliced_line;
    char                *command;
    t_arguments         *arguments;
    t_redirections      *redirections;
    struct  s_pipes    *next;
}   t_pipes;

typedef struct  s_format
{
    char                *line;
    int                 pipe_presence;

    t_linedata         *sliced_line;
    char                *pre_pipe_line;
    char                *command;
    t_arguments         *arguments;
    t_redirections      *redirections;
    
    t_pipes             *pipes;
    struct  s_format    *next;
}   t_format;

typedef     struct  s_var_rep
{
    int     dollar_position;
    char    *slice;
    char    *variable_content;
    char    *variable_name;
} t_var_rep;

typedef     struct  s_tools
{
    char    c;
    int     i;
    int     j;
    int     n;
    int     len;
    int     counter;
    char    *ret;
} t_tools;

typedef     struct  s_toolbox
{
    t_format        *formaptr;;
	t_history	    *ptr;
	t_history 	    *tmp;
    int             ascii;
	char	        *str;
	struct termios  old;
	int             i;
	char            *check;
}   t_toolbox;

//--------dollar_treatment.c---------//
int     test_c(char c)
ssize_t     find_valid_dollar(char *slice)
char    *fetch_var_name(char *slice, int i)
char    *var_replacement(t_var_rep *data)
ssize_t     equal_sign(char     *str)
t_env       *fetch_all_variables(char **env)
char    *ft_strdup(char     *str)
char    *fetch_wanted_var(char    *name, t_env   *ptr)
void    print_k(t_env   *ptr)
char    *fetch_variable_content(char **env, char    *name)
char    *dollar_treatment(char  **env, char *slice)
//--------dollar_treatment.c---------//

//------------error_check.c----------//
int     quotes_err(char     *input, int i);
int     da_loop(char    *input, int i);
int     tri(char    *input, int i, char **str);
char        *error_check(char    *input);
int     parse_error_check(char *input, int i);
int     redirection_error_check(char *input, int i);
int     error_suite(int counter, char   *input, int i, char *str);
//------------error_check.c----------//


