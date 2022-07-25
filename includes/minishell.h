/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 19:11:28 by aperol-h          #+#    #+#             */
/*   Updated: 2022/07/25 18:33:29 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include "libft.h"

# ifndef MAX_BUF
#  define MAX_BUF 200
# endif

typedef struct s_variable
{
	char	*key;
	char	*value;
}	t_variable;

typedef struct s_command
{
	char	*cmd;
	char	**args;
	int		fd_stdin;
	int		fd_stdout;
	int		append_mode;
}	t_command;

int		builtin_cd(char *path);
void	builtin_echo(int fd, int has_n, char *str);
int		builtin_echo_parse(char **args);
int		builtin_env(t_list *lst);
void	builtin_exit(void);
void	builtin_export(t_list **var_list, char *key, char *value);
int		builtin_export_parse(t_list **var_list, char **args);
void	init_environ(t_list **var_list);
char	**gen_environ(t_list *lst);
int		builtin_pwd(void);
void	builtin_unset(t_list **var_list, char *key);
int		builtin_unset_parse(t_list **var_list, char **args);
void	parse(char *cmd, char *path, t_list **var_list);
void	del_arg(char **args);
char	*join_env(char *key, char *value);
char	*search_executable(char **path, char *cmd);
size_t	lenm(char *s1, char *s2);
void	free_variable(void *content);
t_list	*find_key(t_list *lst, char *key);

#endif
