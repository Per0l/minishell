/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_find.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 17:43:46 by aperol-h          #+#    #+#             */
/*   Updated: 2022/05/29 18:13:31 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	lenm(char *s1, char *s2)
{
	size_t	t1;
	size_t	t2;

	t1 = ft_strlen(s1);
	t2 = ft_strlen(s2);
	if (t1 > t2)
		return (t1);
	return (t2);
}

char	*ft_pathjoin(char *folder, char *file)
{
	char	*res;
	size_t	sfolder;
	size_t	sfile;

	sfolder = ft_strlen(folder);
	sfile = ft_strlen(file);
	res = (char *)malloc((sfolder + sfile + 2) * sizeof(char));
	if (!res)
		return (NULL);
	ft_memmove(res, folder, sfolder);
	res[sfolder] = '/';
	ft_memmove(res + sfolder + 1, file, sfile);
	res[sfolder + sfile + 1] = '\0';
	return (res);
}

char	*search_folder(char *folder, char *cmd)
{
	DIR				*dp;
	struct dirent	*dirp;
	char			*res;

	res = NULL;
	dp = opendir(folder);
	if (dp)
	{
		while (1)
		{
			dirp = readdir(dp);
			if (dirp == NULL)
				break ;
			if (ft_strncmp(cmd, dirp->d_name, lenm(dirp->d_name, cmd)) == 0)
			{
				res = ft_pathjoin(folder, dirp->d_name);
				break ;
			}
		}
		if (closedir(dp) == -1)
			perror("closedir");
	}
	return (res);
}

char	*search_executable(char **path, char *cmd)
{
	int		i;
	char	*res;

	i = 0;
	res = NULL;
	if (ft_strchr(cmd, '/') && open(cmd, __O_PATH) != -1)
		res = ft_strdup(cmd);
	while (path && path[i])
	{
		if (!res)
			res = search_folder(path[i], cmd);
		free(path[i]);
		i++;
	}
	if (path)
		free(path);
	return (res);
}
