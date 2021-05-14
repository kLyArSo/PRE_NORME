#include <unistd.h>
#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
#include <term.h>
#include <string.h>
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