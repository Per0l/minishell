/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 17:46:16 by aperol-h          #+#    #+#             */
/*   Updated: 2022/07/26 21:16:43 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*init_command(int cmd_len)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (command == NULL)
		exit(1);
	command->args = NULL;
	command->i = 0;
	command->cmd = ft_calloc(cmd_len, sizeof(char));
	if (command->cmd == NULL)
		exit(1);
	command->redirect = malloc(sizeof(t_redirect));
	if (command->redirect == NULL)
		exit(1);
	command->red_i = 1;
	command->redirect[0].fd = -1;
	command->redirect[0].mode = -1;
	command->redirect[0].word = NULL;
	return (command);
}

void	free_command(void *content)
{
	t_command	*command;
	int			i;

	command = (t_command *)content;
	i = -1;
	while (++i < command->red_i)
	{
		if (command->redirect[i].word)
			free(command->redirect[i].word);
	}
	free(command->redirect);
	if (command->cmd)
		free(command->cmd);
	if (command->args && *(command->args))
		ft_free_char_arr(command->args);
	free(content);
}

void	parse_env(char *cmd, int *i, t_list **var_list, t_command *current)
{
	int		j;
	char	*key;
	char	*value;

	j = 1;
	while (cmd && cmd[++(*i)])
	{
		if (cmd[*i] == '|' || cmd[*i] == ' ' || cmd[*i] == '$')
			break ;
		j++;
	}
	key = malloc(j * sizeof(char));
	if (key == NULL)
		exit(1);
	ft_strlcpy(key, cmd + *i - j + 1, j);
	value = ft_getenv(*var_list, key);
	free(key);
	if (value == NULL)
		return ;
	if ((int)ft_strlen(value) > j)
		current->cmd = ft_realloc(current->cmd, ft_strlen(current->cmd),
				ft_strlen(current->cmd) + ft_strlen(cmd) + j);
	ft_strcpy(current->cmd + current->i, value);
	current->i += ft_strlen(value);
}

t_command	*core(char *cmd, int *i, t_list **var_list, t_list **cmd_list)
{
	t_command	*current;

	current = ft_lstlast(*cmd_list)->content;
	if (cmd[*i] == '|')
	{
		ft_lstadd_back(cmd_list, ft_lstnew(init_command(ft_strlen(cmd) + 1)));
		return (NULL);
	}
	while (cmd[*i] == '$')
		parse_env(cmd, i, var_list, current);
	return (current);
}

void	parse(t_list **var_list, char *cmd)
{
	int			i;
	t_list		*cmd_list;
	t_command	*current;
	t_list		*lst;

	cmd_list = NULL;
	ft_lstadd_back(&cmd_list, ft_lstnew(init_command(ft_strlen(cmd) + 1)));
	i = -1;
	while (cmd && i < (int)ft_strlen(cmd) && cmd[++i])
	{
		current = core(cmd, &i, var_list, &cmd_list);
		if (current && cmd[i])
			current->cmd[current->i++] = cmd[i];
	}
	lst = cmd_list;
	while (lst)
	{
		execute(lst->content, var_list);
		lst = lst->next;
	}
	ft_lstclear(&cmd_list, &free_command);
}
