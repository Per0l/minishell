/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 19:11:28 by aperol-h          #+#    #+#             */
/*   Updated: 2022/06/03 17:39:41 by aperol-h         ###   ########.fr       */
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

int		builtin_cd(char *path);
void	builtin_echo(int fd, int has_n, char *str);
int		builtin_echo_parse(char **args);
int		builtin_env(void);
void	builtin_exit(void);
void	builtin_export(char *var);
int		builtin_pwd(void);
void	builtin_unset(void);
void	parse(char *cmd, char *path);
char	*search_executable(char **path, char *cmd);

#endif
