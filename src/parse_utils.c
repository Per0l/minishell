/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 19:13:00 by aperol-h          #+#    #+#             */
/*   Updated: 2022/10/03 19:12:45 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	del_cmd_arg(t_command *command, int idx)
{
	char	**res;
	int		i;
	int		c;
	int		len;

	len = (int) ft_strarrlen(command->args);
	if (len - 1 <= 0)
	{
		ft_free_char_arr(&command->args);
		command->args = NULL;
		return (0);
	}
	res = (char **)malloc((len) * sizeof(char *));
	if (!res)
		exit(1);
	res[len - 1] = NULL;
	i = -1;
	c = -1;
	while (++i < len)
		if (i != idx)
			res[++c] = ft_strdup(command->args[i]);
	ft_free_char_arr(&command->args);
	command->args = res;
	return (0);
}

void	expand_env(t_command *command, int i, int *j, t_list **var_list)
{
	char	*key;
	char	*value;
	int		si;

	si = *j;
	while (command->args[i][++*j])
		if (!ft_isalnum(command->args[i][*j])
			&& !ft_strchr("_?", command->args[i][*j]))
			break ;
	if (si == *j - 1 && (ft_strchr("\t\n\v\f\r <>0123456789abcdefghijklmnopqrs\
				tvwxyzABCDEFGHIJKLMNOPQRSTVWXYZ", command->args[i][*j])
		|| ft_isquoted(command->args[i], si)))
		command->cmd[command->i++] = '$';
	*j -= 1;
	if (si == *j)
		return ;
	key = malloc((*j - si + 1) * sizeof(char));
	if (!key)
		exit(1);
	ft_strlcpy(key, command->args[i] + si + 1, *j - si + 1);
	value = ft_getenv(*var_list, key);
	free(key);
	if (!value)
		return ;
	ft_strcpy(command->cmd + command->i, value);
	command->i += ft_strlen(value);
}

int	interpret_arg(t_command *command, int *p_i, t_list **var_list, int d)
{
	int	j;
	int	i;

	i = *p_i;
	if (d == 0)
		i++;
	j = -1;
	while (command->args[i][++j])
	{
		if (command->args[i][j] == '$'
			&& !(ft_isquoted(command->args[i], j) & 1))
			expand_env(command, i, &j, var_list);
		else if (!ft_strchr("'\"", command->args[i][j])
			|| ft_isquoted(command->args[i], j))
			command->cmd[command->i++] = command->args[i][j];
		command->cmd[command->i] = '\0';
	}
	if (d == 1 && ft_strlen(command->cmd) == 0
		&& ft_countinset("\"'", command->args[i]) == 0)
		return (del_cmd_arg(command, i) & (*p_i)--);
	if (ft_countinset("\"'", command->args[i]) < 2)
		ft_command_subsplit(command, i);
	free(command->args[i]);
	command->args[i] = ft_strdup(command->cmd);
	return (0);
}

int	parse_redir(t_command *command, int *i, t_list **var_list)
{
	if (!command->args[*i + 1] || (ft_strlen(command->args[*i + 1]) <= 2
			&& ft_strchr("<>", command->args[*i + 1][0])))
		return (1);
	interpret_arg(command, i, var_list, 0);
	if (command->args[*i][0] == '>' && command->error == 0)
	{
		if (ft_strlen(command->args[*i]) == 2 && command->args[*i][1] == '>')
			command->fd_out = open(command->args[*i + 1],
					O_CREAT | O_WRONLY | O_APPEND, 0666);
		else
			command->fd_out = open(command->args[*i + 1],
					O_CREAT | O_WRONLY | O_TRUNC, 0666);
	}
	else if (ft_strlen(command->args[*i]) == 1 && command->error == 0)
		command->fd_in = open(command->args[*i + 1], O_RDONLY);
	if ((command->fd_out == -1 || command->fd_in == -1) && command->error == 0)
	{
		ft_strerror(strerror(errno), command->args[*i + 1], 1);
		command->error = errno;
	}
	del_cmd_arg(command, *i);
	del_cmd_arg(command, *i);
	*i -= 1;
	return (0);
}

int	parse_args(t_command *command, t_list **var_list)
{
	int		i;

	command->args = ft_splitcmd(command->cmd, "\t\n\v\f\r ");
	if (!command->args)
		exit(1);
	i = -1;
	while (command->args && command->args[++i])
	{
		command->i = 0;
		command->cmd[command->i] = '\0';
		if (command->args[i][0] != '\0'
			&& ft_strchr("<>", command->args[i][0]))
		{
			if (ft_strlen(command->args[i]) > 2
				|| parse_redir(command, &i, var_list))
				return (1);
			continue ;
		}
		command->i = 0;
		command->cmd[command->i] = '\0';
		interpret_arg(command, &i, var_list, 1);
	}
	return (0);
}
