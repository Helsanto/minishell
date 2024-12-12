# Makefile

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I.
SRCS = main.c \
       parser.c \
       command.c \
       expand.c \
       env.c \
       builtins.c \
       print_banner.c \
       ft_add.c \
       ft_get.c \
       env_util.c \
       ft_pwd.c \
       ft_cd.c \
       ft_exit.c \
       ft_echo.c \
       ft_export.c \
       extrac.c \

OBJS = $(SRCS:.c=.o)
NAME = minishell

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

