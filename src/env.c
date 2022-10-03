/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:57:37 by aoteo-be          #+#    #+#             */
/*   Updated: 2022/10/03 18:38:52 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_list *lst, int is_export)
{
	t_variable	*var;

	if (!lst)
		return (0);
	while (lst)
	{
		var = lst->content;
		if (var && var->key && !ft_strchr("?*", var->key[0]))
		{
			if (!is_export)
				printf("%s=%s\n", var->key, var->value);
			else
				printf("declare -x %s=\"%s\"\n", var->key, var->value);
		}
		lst = lst->next;
	}
	return (0);
}

int	max_envlen(t_list *lst)
{
	t_variable	*var;
	size_t		res;
	size_t		tmp;

	if (!lst)
		return (0);
	res = 0;
	tmp = 0;
	while (lst)
	{
		var = lst->content;
		if (var && var->value)
			tmp = ft_strlen(var->value);
		if (tmp > res)
			res = tmp;
		lst = lst->next;
	}
	return ((int)res);
}

void	init_environ(t_list **var_list)
{
	char	**exp_args;
	char	*tmp;
	int		i;

	i = 0;
	while (__environ[i])
	{
		exp_args = ft_split(__environ[i], '=');
		if (exp_args == NULL)
			exit(1);
		if (ft_strarrlen(exp_args) >= 2)
			builtin_export(var_list, exp_args[0],
				ft_strljoin(exp_args + 1, "="));
		else
		{
			tmp = malloc(1 * sizeof(char));
			tmp[0] = '\0';
			builtin_export(var_list, exp_args[0], tmp);
		}
		ft_free_char_arr(&exp_args);
		i++;
	}
	export_default(var_list);
}

char	**gen_environ(t_list *lst)
{
	t_variable	*var;
	char		**res;
	int			i;

	if (!lst)
	{
		res = (char **) malloc(sizeof(char *));
		res[0] = NULL;
		return (res);
	}
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
		builtin_export(&lst, "?", ft_strdup(status));
	free(status);
	current = find_key(lst, key);
	if (current)
	{
		var = current->content;
		return (var->value);
	}
	return (NULL);
}
