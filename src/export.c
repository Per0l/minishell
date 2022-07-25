/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:10:52 by aoteo-be          #+#    #+#             */
/*   Updated: 2022/07/25 18:22:37 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_export(t_list **var_list, char *key, char *value)
{
	t_variable	*var;
	t_list		*current;

	current = find_key(*var_list, key);
	if (current)
	{
		var = current->content;
		free(var->value);
		var->value = ft_strdup(value);
		return ;
	}
	var = malloc(sizeof(t_variable));
	if (var == NULL)
		exit(1);
	var->key = ft_strdup(key);
	var->value = ft_strdup(value);
	if (var_list == NULL)
		*var_list = ft_lstnew(var);
	else
		ft_lstadd_back(var_list, ft_lstnew(var));
}

int	builtin_export_parse(t_list **var_list, char **args)
{
	char	**exp_args;
	char	*joined_args;

	joined_args = ft_strljoin(args + 1);
	if (joined_args == NULL)
		return (1);
	exp_args = ft_split(joined_args, '=');
	if (exp_args == NULL)
		exit(1);
	free(joined_args);
	if (ft_strarrlen(exp_args) >= 2)
		builtin_export(var_list, exp_args[0], exp_args[1]);
	ft_free_char_arr(exp_args);
	return (1);
}

void	init_environ(t_list **var_list)
{
	char	**exp_args;
	int		i;

	i = 0;
	while (__environ[i])
	{
		exp_args = ft_split(__environ[i], '=');
		if (exp_args == NULL)
			exit(1);
		if (ft_strarrlen(exp_args) >= 2)
			builtin_export(var_list, exp_args[0], exp_args[1]);
		ft_free_char_arr(exp_args);
		i++;
	}	
}

char	**gen_environ(t_list *lst)
{
	t_variable	*var;
	char		**res;
	int			i;

	if (!lst)
		return (NULL);
	res = (char **) malloc((ft_lstsize(lst) + 1) * sizeof(char *));
	i = 0;
	while (lst)
	{
		var = lst->content;
		if (var && var->key && ft_strcmp(var->key, "?") != 0 && var->value)
			res[i++] = join_env(var->key, var->value);
		lst = lst->next;
	}
	res[i] = NULL;
	return (res);
}
