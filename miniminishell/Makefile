CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude -Ilibft
SRCS_DIR = src
SHELL_CORE_DIR = shell_core

SRCS = $(SRCS_DIR)/main.c \
       $(SRCS_DIR)/parser.c \
       $(SRCS_DIR)/command.c \
       $(SRCS_DIR)/expand.c \
       $(SRCS_DIR)/env.c \
       $(SRCS_DIR)/builtins.c \
       $(SRCS_DIR)/print_banner.c \
       $(SRCS_DIR)/ft_add.c \
       $(SRCS_DIR)/ft_get.c \
       $(SRCS_DIR)/env_util.c \
       $(SRCS_DIR)/ft_pwd.c \
       $(SRCS_DIR)/ft_cd.c \
       $(SRCS_DIR)/ft_exit.c \
       $(SRCS_DIR)/ft_echo.c \
       $(SRCS_DIR)/ft_export.c \
       $(SRCS_DIR)/extrac.c \
       $(SRCS_DIR)/exec.c \
       $(SRCS_DIR)/util.c \
       $(SHELL_CORE_DIR)/DoubleQuotes_handling.c \
       $(SHELL_CORE_DIR)/handle_dollarsign.c \
       $(SHELL_CORE_DIR)/Quote_handling.c \
       $(SHELL_CORE_DIR)/redirections.c

OBJS = $(SRCS:.c=.o)
NAME = minishell

all: $(NAME)

$(NAME): $(OBJS)
	@make -C ./libft
	$(CC) $(CFLAGS) $(OBJS) -L./libft -lft -lreadline -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make clean -C ./libft
	rm -f $(OBJS)

fclean: clean
	@make fclean -C ./libft
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
