/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoteo-be <<aoteo-be@student.42.fr> >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 19:11:28 by aperol-h          #+#    #+#             */
/*   Updated: 2022/06/04 20:54:47 by aoteo-be         ###   ########.fr       */
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
	int		key;
	char	*value;
}	t_variable;

int		builtin_cd(char *path);
void	builtin_echo(int fd, int has_n, char *str);
int		builtin_echo_parse(char **args);
int		builtin_env(void);
void	builtin_exit(void);
t_list	*builtin_export(int key, char *value);
int		builtin_pwd(void);
void	builtin_unset(void);
void	parse(char *cmd, char *path);
char	*search_executable(char **path, char *cmd);

#endif
