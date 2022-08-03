/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 19:11:28 by aperol-h          #+#    #+#             */
/*   Updated: 2022/08/03 19:19:12 by aperol-h         ###   ########.fr       */
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
# include <sys/ioctl.h>
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
	char		*cmd;
	char		**args;
	int			i;
	int			fd_out;
	int			fd_in;
	int			error;
}	t_command;

extern int	g_ret;

int		builtin_cd(char *path);
void	builtin_echo(int fd, int has_n, char *str);
int		builtin_echo_parse(char **args);
int		builtin_env(t_list *lst);
void	builtin_exit(void);
void	builtin_export(t_list **var_list, char *key, char *value);
int		builtin_export_parse(t_list **var_list, char **args);
void	init_environ(t_list **var_list);
char	**gen_environ(t_list *lst);
char	*ft_getenv(t_list *lst, char *key);
int		builtin_pwd(void);
void	builtin_unset(t_list **var_list, char *key);
int		builtin_unset_parse(t_list **var_list, char **args);
void	execute(t_command *command, t_list **var_list);
void	executer(t_list *cmd_list, t_list **var_list);
void	parse(t_list **var_list, char *cmd);
void	del_arg(char **args);
char	*join_env(char *key, char *value);
char	*search_executable(char **path, char *cmd);
size_t	lenm(char *s1, char *s2);
void	free_variable(void *content);
t_list	*find_key(t_list *lst, char *key);
void	magic(t_list **var_list, char *cmd);
void	ft_strerror(char *error, char *sufix);
int		ft_isempty(char *str);
int		parse_args(t_command *command, t_list **var_list);
int		ft_countinset(char *set, char *str);

#endif
