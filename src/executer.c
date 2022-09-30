/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 19:10:46 by aperol-h          #+#    #+#             */
/*   Updated: 2022/09/30 23:08:06 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*find_key(t_list *lst, char *key)
{
	t_variable	*var;

	if (!lst || !key)
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
	char		**environ_str;

	environ_str = gen_environ(lst);
	if (environ_str == NULL)
		exit(1);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	execve(executable, command->args, environ_str);
	ft_strerror(strerror(errno), "execve", 1);
	ft_free_char_arr(environ_str);
	free(executable);
	exit(1);
}

int	search_builtin(char **args, t_list **var_list, int is_parent)
{
	if (!args || !args[0])
		return (1);
	if (ft_strcmp(args[0], "cd") == 0)
		g_ret = (builtin_cd(*var_list, args));
	else if (ft_strcmp(args[0], "export") == 0)
		g_ret = (builtin_export_parse(var_list, args));
	else if (ft_strcmp(args[0], "unset") == 0)
		g_ret = (builtin_unset_parse(var_list, args));
	else if (ft_strcmp(args[0], "exit") == 0)
		g_ret = (builtin_exit(args));
	else if (is_parent)
		return (-1);
	else if (ft_strcmp(args[0], "echo") == 0)
		g_ret = (builtin_echo_parse(args));
	else if (ft_strcmp(args[0], "pwd") == 0)
		g_ret = (builtin_pwd(*var_list));
	else if (ft_strcmp(args[0], "env") == 0)
		g_ret = (builtin_env(*var_list, 0));
	else
		return (0);
	return (1);
}

pid_t	execute(t_command *command, t_list **var_list,
	t_command *last, t_list *next)
{
	char	*executable;
	pid_t	pid;

	if (!last && !next && search_builtin(command->args, var_list, 1) != -1)
		return (0);
	pid = fork();
	if (pid != 0)
		return (pid);
	set_redirs(command, next, last);
	if (!search_builtin(command->args, var_list, 0))
	{
		executable = search_executable(ft_split(ft_getenv(*var_list,
						"PATH"), ':'), command->args[0]);
		if (executable)
			execve_fork(*var_list, executable, command);
	}
	exit(g_ret);
}

void	executer(t_list *cmd_list, t_list **var_list, int n)
{
	t_command	*last;
	pid_t		pid;

	last = NULL;
	while (cmd_list)
	{
		if (cmd_list->next)
			pipe(((t_command *)cmd_list->content)->fd_pipe);
		pid = execute(cmd_list->content, var_list, last, cmd_list->next);
		if (n == 1 && pid == 0)
			return ;
		if (last)
		{
			close(last->fd_pipe[0]);
			close(last->fd_pipe[1]);
		}
		if (pid == -1)
			ft_strerror(strerror(EAGAIN), "pipe", 254);
		last = cmd_list->content;
		cmd_list = cmd_list->next;
	}
	waitpid(pid, &g_ret, 0);
	g_ret = WEXITSTATUS(g_ret);
	while (wait(NULL) > 0)
		continue ;
}
