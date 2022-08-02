/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 19:13:00 by aperol-h          #+#    #+#             */
/*   Updated: 2022/08/02 20:51:39 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_quotes(t_command *command, int i)
{
	int	j;

	j = -1;
	while (command->args[i][++j])
	{
		if (!ft_strchr("'\"", command->args[i][j])
			|| ft_isquoted(command->args[i], j))
			command->cmd[command->i++] = command->args[i][j];
		command->cmd[command->i] = '\0';
	}
	free(command->args[i]);
	command->args[i] = ft_strdup(command->cmd);
	command->i = 0;
	command->cmd[command->i] = '\0';
}

int	parse_redir(t_command *command, int *i)
{
	if (!command->args[*i + 1] || (ft_strlen(command->args[*i + 1]) <= 2
			&& ft_strchr("<>", command->args[*i + 1][0])))
		return (1);
	clear_quotes(command, *i + 1);
	if (command->args[*i][0] == '>')
	{
		if (ft_strlen(command->args[*i]) == 2 && command->args[*i][1] == '>')
			command->fd_out = open(command->args[*i + 1],
					O_CREAT | O_WRONLY | O_APPEND, 0666);
		else
			command->fd_out = open(command->args[*i + 1],
					O_CREAT | O_WRONLY | O_TRUNC, 0666);
	}
	else if (ft_strlen(command->args[*i]) == 1)
		command->fd_in = open(command->args[*i + 1], O_RDONLY);
	if (command->fd_out == -1 || command->fd_in == -1)
		command->error = errno;
	command->args[*i][0] = '\0';
	command->args[*i + 1][0] = '\0';
	*i += 1;
	return (0);
}

void	del_empty_args(t_command *command, int len)
{
	char	**res;
	int		i;
	int		c;

	i = -1;
	c = 0;
	while (++i < len)
		if (!command->args[i][0])
			c++;
	res = (char **)malloc((len - c + 1) * sizeof(char *));
	if (!res)
		exit(1);
	res[len - c] = NULL;
	i = -1;
	c = -1;
	while (++i < len)
		if (command->args[i][0])
			res[++c] = ft_strdup(command->args[i]);
	ft_free_char_arr(command->args);
	command->args = res;
}

int	parse_args(t_command *command)
{
	int		i;

	command->args = ft_splitcmd(command->cmd, "\t\n\v\f\r ");
	if (!command->args)
		exit(1);
	i = -1;
	command->i = 0;
	command->cmd[command->i] = '\0';
	while (command->args[++i])
	{
		if (ft_strlen(command->args[i]) <= 2
			&& ft_strchr("<>", command->args[i][0]))
		{
			if (parse_redir(command, &i))
				return (1);
			continue ;
		}
		clear_quotes(command, i);
	}
	del_empty_args(command, i);
	return (0);
}
