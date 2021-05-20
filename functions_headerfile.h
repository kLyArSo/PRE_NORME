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

typedef struct s_global
{
    int ret;
}               t_global;

t_global g_global;

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
int                 test_c(char c);
ssize_t             find_valid_dollar(char *slice);
char                *fetch_var_name(char *slice, int i);
char                *var_replacement(t_var_rep *data, char  *slice);
ssize_t             equal_sign(char     *str);
t_env               *fetch_all_variables(char **env);
char                *ft_strdup(char     *str);
char                *fetch_wanted_var(char    *name, t_env   *ptr);
void                print_k(t_env   *ptr);
char                *fetch_variable_content(char **env, char    *name);
char                *dollar_treatment(char  **env, char *slice);
//--------dollar_treatment.c---------//

//------------error_check.c----------//
int                 quotes_err(char     *input, int i);
int                 da_loop(char    *input, int i);
int                 tri(char    *input, int i, char **str);
char                *error_check(char    *input);
int                 parse_error_check(char *input, int i);
int                 redirection_error_check(char *input, int i);
int                 error_suite(int counter, char   *input, int i, char *str);
//------------error_check.c----------//

//------------fetch_input.c----------//
ssize_t             ft_strlen(char  *string);
char                *my_calloc(int length);
char                *my_realloc(char    *str, char  c);
int                 my_strcmp(char  *s1, char   *s2);
char                *fetch_input();
//------------fetch_input.c----------//

//-------------main.c----------------//
void                ft_execution(char        **env, t_format    *ptr);
void	   	        *init_all(t_toolbox   *box);
void                put_strings(char    *s1, char   *s2, char   *s3, char   *s4);
void		        init_lst(t_toolbox   *box);
void                printable_key(t_toolbox   *box);
void                delete_key(t_toolbox   *box);
void                up_key(t_toolbox   *box);
void                down_key(t_toolbox   *box);
void                ctrl_d_key(t_toolbox   *box);
void                update_position(t_toolbox   *box);
void                *full_ws_niet(t_toolbox   *box, char    **env);
void                full_ws_da(t_toolbox   *box);
void                *enter_key(t_toolbox   *box, char        **env);
//-------------main.c----------------//

//--------------parse.c--------------//
void                initialise(t_bag       **bag, t_linedata **data, t_linedata  **tmp);
t_linedata          *split_id(char   *input);
char                *parse(char *input, t_format    *ptr);
//--------------parse.c--------------//

//--------------pipes.c---------------//
int                 pipe_presence(char *input);
char                *fetch_command(t_linedata *data);
t_arguments         *f_16(t_arguments     *ptr, t_linedata *data);
t_arguments         *fetch_arguments(t_linedata *data, t_arguments *ret, int counter);
t_linedata          *a_s(t_linedata *data, t_redirections     *ptr);
t_redirections      *fetch_redirection(t_linedata *data, t_redirections *ret, int counter);
t_pipes             *f2(t_format    *ptr, int *start, int i);
void                f3(t_format    *ptr, int start, int i);
int                 skips(t_format    *ptr, int i);
void                ft_end(t_format    *ptr, int *i, int start);
void                *fetch_pipes(t_format    *ptr, int start, int i);
void                assignments(t_format    *ptr);
void                *pipe_split(t_format    *ptr);
//--------------pipes.c---------------//
void                print_da(t_format    *ptr);//DONT NORM IT

//---------------purge.c--------------//
void                purge(char        **env, t_format    *ptr);
void                cleanse_no_pipes(char        **env, t_format    *ptr);
void                cleanse_yes_pipes(char        **env, t_format    *ptr);
//---------------purge.c--------------//

//---------quote_backslash.c-----------//
void                treat_slash(char *slice, t_tools   *box);
void                treat_single_quote(char *slice, t_tools   *box);
void                double_q_slash(char *slice, t_tools   *box);
void                treat_double_quote(char *slice, t_tools   *box);
char                *quote_slash(char *slice);
//---------quote_backslash.c-----------//

//-------------semi_split.c-------------//
int                 skip_quotes(char    *input, int i);
char                *trim_spaces(char *input);
void                skip_un(char    *input, int i, int *a);
t_format            *fetch(t_format    *ptr, char   *input, int    *start, int i);
void                *semicolon_split(t_format    *ptr, char     *input);
void                printf_individual_lines(t_format    *ptr);
char                *last_check(char *input);
//-------------semi_split.c-------------//


//-------------------supp1.c-------------//
t_linedata          *pre_red(char   *input, t_bag   *bag, t_linedata *data);
t_linedata          *red(char   *input, t_bag   *bag, t_linedata *data);
void                ufo(t_linedata *data);
t_linedata          *w_s(char   *input, t_bag   *bag, t_linedata *data);
void                eof(char   *input, t_bag   *bag, t_linedata *data);
t_linedata          *fetch_red(char   *input, t_bag   *bag, t_linedata *data);
//-------------------supp1.c-------------//

//-------------------supp2.c-------------//
void                data_init(t_linedata *data);
int                 skip_irr(char   *input, int i);
void                data_init0(t_bag *data);
t_tools             *initialise_box(t_tools     *box, char *slice);
//-------------------supp2.c-------------//

//-----------------term.c----------------//
char                *j_oin(char *s, char c);
int                 fetch_char(struct termios *old);
char	            *ft_strdupe(char	*str);
int                 put_char(int c);
char	            *delete_char(char	*str);
int		            all_sp(char	*str);
//-----------------term.c----------------//

//------------------utils.c--------------//
int                 ft_test_char(char   *str, char c);
int                 is_white_space(char c);
int                 back_slash_presence(char *input, int i);
char                *ft_substr(char *str, int start, int end);
char                *ft_error(char *str);
char                *ft_strjoin(char *s1, char *s2);
//------------------utils.c--------------//

//---------------------ft_itoa.c----------//
char				*ft_itoa(int n);
static	char		*ft_print_pos(int nb, char *s, int j);
static	char		*ft_printneg(unsigned int nb, char *s, int k);
static	int			ft_counter(int n);
static	int			check_neg(int n);
//---------------------ft_itoa.c----------//