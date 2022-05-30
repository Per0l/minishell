/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 19:10:46 by aperol-h          #+#    #+#             */
/*   Updated: 2022/05/30 18:39:17 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execve_fork(char *executable, char **args)
{
	pid_t		pid;
	struct stat	sb;

	stat(executable, &sb);
	if (S_ISREG(sb.st_mode))
	{
		pid = fork();
		if (pid == 0)
			execve(executable, args, NULL);
		else
			waitpid(pid, NULL, 0);
	}
	else
		chdir(executable);
	free(executable);
}

void	parse(char *cmd, char *path)
{
	char	**args;
	char	*executable;
	int		i;

	args = ft_split(cmd, ' ');
	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		if (i == 0)
		{
			executable = search_executable(ft_split(path, ':'), args[i]);
			if (executable)
				execve_fork(executable, args);
		}
		free(args[i]);
		i++;
	}
	free(args);
}
