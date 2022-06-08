/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 19:10:46 by aperol-h          #+#    #+#             */
/*   Updated: 2022/06/08 19:44:31 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*find_key(t_list *lst, char *key)
{
	t_variable	*var;

	if (!lst)
		return (NULL);
	while (lst)
	{
		var = lst->content;
		if (var && var->key
			&& ft_strcmp(var->key, key) == 0)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

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

int	search_builtin(char **args, t_list **var_list)
{
	if (ft_strcmp(args[0], "cd") == 0)
		return (builtin_cd(args[1]));
	if (ft_strcmp(args[0], "echo") == 0)
		return (builtin_echo_parse(args));
	if (ft_strcmp(args[0], "pwd") == 0)
		return (builtin_pwd());
	if (ft_strcmp(args[0], "env") == 0)
		return (builtin_env());
	if (ft_strcmp(args[0], "export") == 0)
		return (builtin_export_parse(var_list, args));
	if (ft_strcmp(args[0], "exit") == 0)
		exit(0);
	return (0);
}

void	expand_args(char **args, t_list **var_list)
{
	int			i;
	t_list		*found;
	t_variable	*var;

	i = 0;
	while (args && args[i])
	{
		if (ft_strlen(args[i]) > 1 && args[i][0] == '$')
		{
			found = find_key(*var_list, args[i] + 1);
			if (found && found->content)
			{
				var = found->content;
				free(args[i]);
				args[i] = ft_strdup(var->value);
			}
			else
				args[i][0] = '\0';
		}
		i++;
	}
}

void	parse(char *cmd, char *path, t_list **var_list)
{
	char	**args;
	char	*executable;
	int		i;

	args = ft_split(cmd, ' ');
	if (!args)
		exit(1);
	i = 0;
	expand_args(args, var_list);
	while (args[i])
	{
		if (i == 0 && !search_builtin(args, var_list))
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
