/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 19:10:46 by aperol-h          #+#    #+#             */
/*   Updated: 2022/07/25 19:12:38 by user             ###   ########.fr       */
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

void	execve_fork(t_list *lst, char *executable, char **args)
{
	pid_t		pid;
	char		**environ_str;
	int			waitstatus;
	char		*status_code;

	environ_str = gen_environ(lst);
	if (environ_str == NULL)
		exit(1);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		execve(executable, args, environ_str);
	}
	else
	{
		waitpid(pid, &waitstatus, 0);
		status_code = ft_itoa(WEXITSTATUS(waitstatus));
		builtin_export(&lst, "?", status_code);
		free(status_code);
	}
	ft_free_char_arr(environ_str);
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
		return (builtin_env(*var_list));
	if (ft_strcmp(args[0], "export") == 0)
		return (builtin_export_parse(var_list, args));
	if (ft_strcmp(args[0], "unset") == 0)
		return (builtin_unset_parse(var_list, args));
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
				del_arg(args + i--);
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
				execve_fork(*var_list, executable, args);
			else
				builtin_export(var_list, "?", ft_itoa(errno));
		}
		else if (i == 0)
			builtin_export(var_list, "?", ft_itoa(errno));
		free(args[i]);
		i++;
	}
	free(args);
}
