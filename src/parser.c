/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 19:10:46 by aperol-h          #+#    #+#             */
/*   Updated: 2022/06/03 17:43:11 by aperol-h         ###   ########.fr       */
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
			execve(executable, args, __environ);
		else
			waitpid(pid, NULL, 0);
	}
	else
		chdir(executable);
	free(executable);
}

int	search_builtin(char **args)
{
	if (ft_strncmp(args[0], "cd", ft_strlen(args[0])) == 0)
		return (builtin_cd(args[1]));
	if (ft_strncmp(args[0], "echo", ft_strlen(args[0])) == 0)
		return (builtin_echo_parse(args));
	if (ft_strncmp(args[0], "pwd", ft_strlen(args[0])) == 0)
		return (builtin_pwd());
	if (ft_strncmp(args[0], "env", ft_strlen(args[0])) == 0)
		return (builtin_env());
	if (ft_strncmp(args[0], "exit", ft_strlen(args[0])) == 0)
		exit(0);
	return (0);
}

void	parse(char *cmd, char *path)
{
	char	**args;
	char	*executable;
	int		i;

	args = ft_split(cmd, ' ');
	if (!args)
		exit(1);
	i = 0;
	while (args[i])
	{
		if (i == 0 && !search_builtin(args))
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
