# Variables
NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS =	main.c \
		executor.c \
		signal.c \
		parsing/parser.c \
		builtin/ft_cd.c \
		builtin/ft_echo.c \
		builtin/ft_env.c \
		builtin/ft_exit.c \
		builtin/ft_export.c \
		builtin/ft_pwd.c \
		builtin/ft_unset.c

OBJS = $(SRCS:.c=.o)

# Règles
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean
	@echo "fclean reussi"

re: fclean all

.PHONY: all clean fclean re
