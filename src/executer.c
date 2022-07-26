/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 19:10:46 by aperol-h          #+#    #+#             */
/*   Updated: 2022/07/26 21:21:00 by aperol-h         ###   ########.fr       */
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

void	execve_fork(t_list *lst, char *executable, t_command *command)
{
	pid_t		pid;
	char		**environ_str;
	int			waitstatus;

	environ_str = gen_environ(lst);
	if (environ_str == NULL)
		exit(1);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		execve(executable, command->args, environ_str);
	}
	else
	{
		waitpid(pid, &waitstatus, 0);
		errno = WEXITSTATUS(waitstatus);
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

void	execute(t_command *command, t_list **var_list)
{
	char	*executable;
	char	*status_code;

	command->args = ft_split(command->cmd, ' ');
	if (!command->args)
		exit(1);
	if (!search_builtin(command->args, var_list))
	{
		executable = search_executable(ft_split(ft_getenv(*var_list,
						"PATH"), ':'), command->args[0]);
		if (executable)
			execve_fork(*var_list, executable, command);
	}
	status_code = ft_itoa(errno);
	builtin_export(var_list, "?", status_code);
	free(status_code);
	errno = 0;
}
