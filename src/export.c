/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:10:52 by aoteo-be          #+#    #+#             */
/*   Updated: 2022/08/10 18:52:36 by aperol-h         ###   ########.fr       */
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
		if (var->value)
			free(var->value);
		var->value = ft_strdup(value);
		return ;
	}
	var = malloc(sizeof(t_variable));
	if (var == NULL)
		exit(1);
	var->key = ft_strdup(key);
	var->value = ft_strdup(value);
	ft_lstadd_back(var_list, ft_lstnew(var));
}

int	builtin_export_parse(t_list **var_list, char **args)
{
	char	*equal;
	int		idx;

	if (!args || !*args || !args[1] || ft_strlen(args[1]) <= 1)
		return (0);
	equal = ft_strchr(args[1], '=');
	if (equal == NULL || equal == args[1])
		return (0);
	idx = args[1][ft_strlen(args[1]) - 1] != '=';
	*equal = '\0';
	builtin_export(var_list, args[1], equal + idx);
	return (0);
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

char	*ft_getenv(t_list *lst, char *key)
{
	t_variable	*var;
	t_list		*current;
	char		*status;

	if (!lst || !key)
		return (NULL);
	status = ft_itoa(g_ret % 256);
	if (!status)
		return (NULL);
	if (ft_strcmp(key, "?") == 0)
		builtin_export(&lst, "?", status);
	free(status);
	current = find_key(lst, key);
	if (current)
	{
		var = current->content;
		return (var->value);
	}
	return (NULL);
}
