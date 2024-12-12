/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msiemon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:19:19 by msiemon           #+#    #+#             */
/*   Updated: 2024/12/06 16:19:22 by msiemon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <ctype.h>
# include <stddef.h> 
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

/* *** Structures *** */

typedef struct s_quote_state
{
	bool	in_single_quotes;
	bool	in_double_quotes;
}	t_quote_state;

typedef struct s_command
{
	char				**args;
	int					argc;
	struct s_command	*next;
}	t_command;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_pipeline
{
	t_command	*commands;
	int			count;
}	t_pipeline;

/* *** Extern Variables *** */

extern int			g_last_exit_code;
extern t_env		*g_env_list;

/* *** Function Prototypes *** */

int			builtin_echo(char **args);
int			builtin_pwd(char **args);
int			builtin_cd(char **args);
int			builtin_env(char **args, t_env *env);
int			builtin_export(char **args, t_env **env);
int			builtin_unset(char **args, t_env **env);
int			builtin_exit(char **args);
int			execute_builtin(t_command *cmd, t_env **env);
t_env		*init_env(char **environ);
char		*get_env_value(t_env *env, const char *key);
int			set_env_value(t_env **env, const char *key, const char *value);
int			unset_env_value(t_env **env, const char *key);
void		print_env(t_env *env);
void		free_env(t_env *env);
char		*read_input_line(void);
char		**parse_line(char *line);
void		expand_variables(char **args);
void		free_command(t_command *cmd);
t_command	*create_command(char **args);
t_command	*parse_input_into_commands(const char *input);
void		print_banner(void);
char		**add_token_to_array(char **array, char *token);
char		*add_char_to_token(char *current_token, char c);
char		*get_return_value(void);
const char	*get_env_var_value(const char *var);
char		*allocate_and_concat(char *new_arg, const char *src,
				size_t len, size_t *offset);
char		**split_key_value(const char *str);
int			update_existing_env_value(t_env *current, const char *value);
int			add_new_env_value(t_env **env, const char *key, const char *value);
char		**allocate_key_value_array(void);
char		*extract_key(const char *str, char *equal_pos);
char		*extract_value(char *equal_pos);

#endif
