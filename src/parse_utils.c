/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 19:13:00 by aperol-h          #+#    #+#             */
/*   Updated: 2022/08/10 21:45:27 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_env(t_command *command, int i, int *j, t_list **var_list)
{
	char	*key;
	char	*value;
	int		si;

	si = *j;
	while (command->args[i][++*j])
		if (ft_strchr("'\"\t\n\v\f\r <>", command->args[i][*j]))
			break ;
	if (si == *j - 1 && (ft_strchr("\t\n\v\f\r <>", command->args[i][*j])
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

void	interpret_arg(t_command *command, int i, t_list **var_list)
{
	int	j;

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
	free(command->args[i]);
	command->args[i] = ft_strdup(command->cmd);
	if (!command->args[i])
		exit(1);
	command->i = 0;
	command->cmd[command->i] = '\0';
}

int	parse_redir(t_command *command, int *i, t_list **var_list)
{
	if (!command->args[*i + 1] || (ft_strlen(command->args[*i + 1]) <= 2
			&& ft_strchr("<>", command->args[*i + 1][0])))
		return (1);
	interpret_arg(command, *i + 1, var_list);
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
		ft_strerror(strerror(errno), command->args[*i + 1], 1);
	command->args[*i][0] = '\0';
	command->args[*i + 1][0] = '\0';
	*i += 1;
	if (command->error == 0)
		command->error = errno;
	return (0);
}

void	del_empty_args(t_command *command, int len)
{
	char	**res;
	int		i;
	int		c;

	if (len < 2)
		return ;
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

int	parse_args(t_command *command, t_list **var_list)
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
			if (parse_redir(command, &i, var_list))
			{
				ft_strerror("syntax error near unexpected token", NULL, 2);
				return (1);
			}
			continue ;
		}
		interpret_arg(command, i, var_list);
	}
	del_empty_args(command, i);
	return (0);
}
