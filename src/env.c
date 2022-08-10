/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:57:37 by aoteo-be          #+#    #+#             */
/*   Updated: 2022/08/10 21:33:32 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_list *lst)
{
	t_variable	*var;

	if (!lst)
		return (0);
	while (lst)
	{
		var = lst->content;
		if (var && var->key && ft_strcmp(var->key, "?") != 0)
			printf("%s=%s\n", var->key, var->value);
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
