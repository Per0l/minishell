/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 13:58:39 by aperol-h          #+#    #+#             */
/*   Updated: 2022/09/30 00:05:25 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_ret;

char	*get_prompt(t_list *var_list)
{
	char	*path;
	char	*user;
	char	*prompt;
	int		user_len;
	int		path_len;

	path = ft_strdup(ft_getenv(var_list, "PWD"));
	if (!path)
		path = getcwd(NULL, 0);
	user = ft_getenv(var_list, "USER");
	user_len = ft_strlen(user);
	path_len = ft_strlen(path);
	prompt = (char *)malloc((user_len + path_len + 4) * sizeof(char));
	if (!prompt)
		exit(1);
	ft_memmove(prompt, user, user_len);
	ft_memmove(prompt + user_len, ":", 1);
	ft_memmove(prompt + user_len + 1, path, path_len);
	ft_memmove(prompt + user_len + 1 + path_len, "$ ", 2);
	*(prompt + user_len + path_len + 3) = 0;
	free(path);
	return (prompt);
}

char	*rl_gets(t_list *var_list)
{
	static char	*line_read = (char *) NULL;
	char		*prompt;

	if (line_read)
	{
		free(line_read);
		line_read = (char *) NULL;
	}
	prompt = get_prompt(var_list);
	line_read = readline(prompt);
	free(prompt);
	if (line_read && *line_read)
		add_history (line_read);
	return (line_read);
}

void	sigint_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_ret = 130;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	free_variable(void *content)
{
	t_variable	*var;

	if (!content)
		return ;
	var = (t_variable *)content;
	if (var->key)
		free(var->key);
	if (var->value)
		free(var->value);
	free(content);
}

		//parse(cmd, ft_getenv(var_list, "PATH"), &var_list);
int	main(int argc, char **argv)
{
	char	*cmd;
	t_list	*var_list;
	int		i=0;
	char	**arg_input;

	var_list = NULL;
	g_ret = 0;
	init_environ(&var_list);
	signal(SIGQUIT, SIG_IGN);/* 
	for (int i = 0; i < argc; i++)
	{
		printf("'%s'\n", argv[i]);
	}
	exit(0); */
	if (argc == 3 && ft_strcmp(argv[1], "-c") == 0 && argv[2])
	{
		arg_input = ft_split(argv[2], ';');
		if (!arg_input)
			exit(1);
		i = 0;
		while (arg_input[i])
		{
			if (!ft_isempty(arg_input[i]))
			{
				signal(SIGINT, SIG_IGN);
				parse(&var_list, arg_input[i]);
			}
			i++;
		}
		ft_free_char_arr(arg_input);
		exit(g_ret);
	}
	else
	{
		while (1)
		{
			signal(SIGINT, sigint_handler);
			cmd = rl_gets(var_list);
			if (!cmd)
				break ;
			if (!ft_isempty(cmd))
			{
				signal(SIGINT, SIG_IGN);
				parse(&var_list, cmd);
			}
		}
	}
	ft_lstclear(&var_list, &free_variable);
}
