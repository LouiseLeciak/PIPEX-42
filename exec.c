/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleciak <lleciak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:41:31 by lleciak           #+#    #+#             */
/*   Updated: 2024/03/18 11:11:50 by lleciak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./utils/headers/pipex.h"

int	ft_forkex(char *tab_args[], char *envp[], int fd, int *pip)
{
	int	id;

	id = fork();
	if (id < 0)
		return (1);
	else if (id == 0)
	{
		dup2(fd, 0);
		dup2(pip[1], 1);
		close(fd);
		close(pip[1]);
		close(pip[0]);
		execve(tab_args[0], tab_args, envp);
		exit(1);
	}
	return (0);
}

int	ft_exec(char *argv, int fd, int *pip, t_env env)
{
	char	*path_cmd;
	char	**tab_args;
	int		i;

	i = 2;
	tab_args = NULL;
	path_cmd = NULL;
	tab_args = ft_split(argv, ' ');
	path_cmd = final_path(tab_args[0], env.env_path);
	if (path_cmd)
	{
		free(tab_args[0]);
		tab_args[0] = path_cmd;
		ft_forkex(tab_args, env.envp, fd, pip);
	}
	else if (!path_cmd)
		return (ft_printf(2, "Error.\nCommand not found. %s\n", tab_args[0]),
			free_tab(tab_args), 1);
	free_tab(tab_args);
	return (1);
}

int	ft_check_and_exec(char *argv[], t_env new_env, int fd)
{
	int		i;
	int		fd_out[2];
	int		pip[2];

	i = 2;
	while (argv[i + 1] && argv[i + 2] != NULL)
	{
		pipe(pip);
		ft_exec(argv[i++], fd, pip, new_env);
		dup2(pip[0], fd);
		close(pip[0]);
		close(pip[1]);
	}
	unlink(argv[i + 1]);
	fd_out[1] = open(argv[i + 1], O_WRONLY | O_CREAT, 0666);
	fd_out[0] = 42;
	ft_exec(argv[i], fd, fd_out, new_env);
	return (close(fd_out[1]), close(fd_out[0]), 0);
}
