/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_find.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 17:43:46 by aperol-h          #+#    #+#             */
/*   Updated: 2022/06/08 19:32:03 by aperol-h         ###   ########.fr       */
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
		exit(1);
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
			if (ft_strcmp(cmd, dirp->d_name) == 0)
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

char	*file_error_handler(char *res, char *cmd_bck, char *is_path)
{
	struct stat	sb;
	int			stat_e;

	if (res == NULL && !is_path)
	{
		ft_putstr_fd("minishell: Command not found: ", 2);
		ft_putendl_fd(cmd_bck, 2);
		return (NULL);
	}
	stat_e = stat(res, &sb);
	if (stat_e == -1 || (S_IEXEC & sb.st_mode) == 0)
	{
		if (stat_e != -1)
			errno = EACCES;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(res, 2);
		if (!is_path)
			free(res);
		return (NULL);
	}
	if (is_path)
		res = ft_strdup(res);
	return (res);
}

char	*search_executable(char **path, char *cmd)
{
	int		i;
	char	*res;
	char	*is_path;
	char	*cmd_bck;

	i = 0;
	res = NULL;
	is_path = ft_strchr(cmd, '/');
	while (path && path[i])
	{
		if (res == NULL && !is_path)
			res = search_folder(path[i], cmd);
		free(path[i]);
		i++;
	}
	if (path)
		free(path);
	cmd_bck = cmd;
	if (!is_path)
		cmd = res;
	return (file_error_handler(cmd, cmd_bck, is_path));
}
