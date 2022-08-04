/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 17:46:16 by aperol-h          #+#    #+#             */
/*   Updated: 2022/08/04 21:08:55 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*init_command(char *cmd)
{
	t_command	*command;
	int			cmd_len;

	command = malloc(sizeof(t_command));
	if (command == NULL)
		exit(1);
	command->args = NULL;
	command->i = -1;
	command->fd_out = 1;
	command->fd_in = 0;
	command->error = 0;
	cmd_len = ft_strlen(cmd) + (ft_countinset("<>", cmd) * 2) + 1;
	command->cmd = ft_calloc(cmd_len, sizeof(char));
	if (command->cmd == NULL)
		exit(1);
	return (command);
}

void	free_command(void *content)
{
	t_command	*command;

	command = (t_command *)content;
	if (command->cmd)
		free(command->cmd);
	if (command->args && *(command->args))
		ft_free_char_arr(command->args);
	if (command->fd_in > 1)
		close(command->fd_in);
	if (command->fd_out > 1)
		close(command->fd_out);
	free(content);
}

void	split_redir(t_command *command)
{
	int		i;
	int		j;

	i = -1;
	while (command->args && command->args[++i])
	{
		j = -1;
		while (command->args[i][++j])
		{
			if (!ft_strchr("<>", command->args[i][j])
				|| ft_isquoted(command->args[i], j))
				command->cmd[++command->i] = command->args[i][j];
			else
			{
				if (j > 0 && !ft_strchr("<>\t\n\v\f\r ", command->args[i][j - 1]))
					command->cmd[++command->i] = ' ';
				command->cmd[++command->i] = command->args[i][j];
				if (!ft_strchr("<>\t\n\v\f\r ", command->args[i][j + 1]))
					command->cmd[++command->i] = ' ';
			}
		}
		command->cmd[++command->i] = ' ';
	}
	command->cmd[command->i] = '\0';
	ft_free_char_arr(command->args);
}

void	parse(t_list **var_list, char *cmd)
{
	int			i;
	t_list		*cmd_list;
	t_command	*current;
	char		**cmd_split;

	cmd_list = NULL;
	cmd_split = ft_splitcmd(cmd, "|");
	i = -1;
	while (cmd_split && cmd_split[++i])
	{
		current = init_command(cmd);
		current->args = ft_splitcmd(cmd_split[i], "\t\n\v\f\r ");
		split_redir(current);
		if (parse_args(current, var_list))
		{
			free_command(current);
			break ;
		}
		ft_lstadd_back(&cmd_list, ft_lstnew(current));
	}
	if (i == (int)ft_strarrlen(cmd_split))
		executer(cmd_list, var_list);
	ft_free_char_arr(cmd_split);
	ft_lstclear(&cmd_list, &free_command);
}

void	set_redirs(t_command *command, t_list *next, t_command *last)
{
	if (next)
	{
		close(command->fd_pipe[0]);
		dup2(command->fd_pipe[1], STDOUT_FILENO);
		close(command->fd_pipe[1]);
	}
	if (last)
	{
		close(last->fd_pipe[1]);
		dup2(last->fd_pipe[0], STDIN_FILENO);
		close(last->fd_pipe[0]);
	}
}
