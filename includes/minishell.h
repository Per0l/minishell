/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoteo-be <<aoteo-be@student.42.fr> >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 19:11:28 by aperol-h          #+#    #+#             */
/*   Updated: 2022/05/28 17:59:41 by aoteo-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "minishell.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>

# ifndef MAX_BUF
#  define MAX_BUF 200
# endif

void	builtin_cd(char *path);
void	builtin_echo(int fd, int has_n, char *str);
void	builtin_env(int fd, char **envp);
void	builtin_exit(void);
void	builtin_export(char *var);
void	builtin_pwd(void);
void	builtin_unset(void);
void	parse(char *cmd);

#endif
