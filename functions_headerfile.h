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
//# define KEY_LEFT  186
//# define KEY_RIGHT 185
//# define TAB_KEY 9
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

char            *fetch_input();
int             my_strcmp(char  *s1, char   *s2);
char            *my_realloc(char    *str, char  c);
char            *my_calloc(int length);
ssize_t         ft_strlen(char  *string);
char            *error_check(char    *input);
int             parse_error_check(char *input, int i);
int             redirection_error_check(char *input, int i);
int             ft_test_char(char   *str, char c);
int             is_white_space(char c);
char            *ft_error(char  *message);
int             back_slash_presence(char *input, int i);
char            *ft_substr(char *str, int start, int end);
int             tri(char    *input, int i);
int             quotes_err(char     *input, int i);
int             da_loop(char    *input, int i);
int             error_suite(int counter, char   *input, int i, char *str);
int             skip_quotes(char    *input, int i);
char            *trim_spaces(char *input);
void            *semicolon_split(t_format    *ptr, char *input);
void            printf_individual_lines(t_format    *ptr);
char            *last_check(char *input);
int             pipe_presence(char *input);
void            *fetch_pipes(t_format    *ptr, int start, int i);
void            *pipe_split(t_format    *ptr);
void            print_formatted(t_format    *ptr);
void            print_da(t_format    *ptr);
void            data_init(t_linedata *data);
int             skip_irr(char   *input, int i);
void            data_init0(t_bag *data);
t_linedata      *pre_red(char   *input, t_bag   *bag, t_linedata *data);
t_linedata      *red(char   *input, t_bag   *bag, t_linedata *data);
t_linedata      *w_s(char   *input, t_bag   *bag, t_linedata *data);
void            eof(char   *input, t_bag   *bag, t_linedata *data);
t_linedata      *fetch_red(char   *input, t_bag   *bag, t_linedata *data);
t_linedata      *split_id(char   *input);
void            free_tpipes_nodes(t_pipes    *ptr);
void            free_tred_nodes(t_redirections    *ptr);
void            free_targs_nodes(t_arguments    *ptr);
void            free_sliced_line_nodes(t_linedata *data);
void            free_sliced_line_strings(t_linedata *data);
void            free_tpipes_contents(t_pipes    *ptr);
void            ft_freedom(t_format *ptr);
void            free_tformat_nodes(t_format    *ptr);
void            free_tformat_contents(t_format *ptr);
void            free_nodes(void *ptr);
t_redirections    *fetch_redirection(t_linedata *data, t_redirections     *ret, int counter);
char            *parse(char *input, t_format    *ptr);
char            *quote_slash(char *slice);
t_tools         *initialise_box(t_tools     *box, char *slice);
char            *ft_strjoin(char *s1, char *s2);
char            *dollar_treatment(char  **env, char *slice);
void            purge(char        **env, t_format    *ptr);
void            cleanse_no_pipes(char        **env, t_format    *ptr);
void            cleanse_yes_pipes(char        **env, t_format    *ptr);
void            *termcaps(t_format    *formaptr, char        **env);
void    ft_execution(char        **env, t_format    *ptr);