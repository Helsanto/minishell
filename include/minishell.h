#ifndef MINISHELL_H
#define MINISHELL_H


# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>




void single_quotes(char *symbol);
void handle_dollarsign(char *symbol, int *i, int len);
void double_quotes(char *symbol);
int redirect_input(const char *filename);


#endif