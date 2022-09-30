/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 23:09:07 by aoteo-be          #+#    #+#             */
/*   Updated: 2022/09/30 21:30:58 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(t_list *lst)
{
	char	*path;

	path = ft_strdup(ft_getenv(lst, "*PWD"));
	if (!path)
		path = getcwd(NULL, MAX_BUF);
	printf("%s\n", path);
	free(path);
	return (0);
}
