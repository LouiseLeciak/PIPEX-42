/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleciak <lleciak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 07:29:44 by lleciak           #+#    #+#             */
/*   Updated: 2024/03/18 15:55:35 by lleciak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./utils/headers/pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	int		fd_in;
	t_env	new_env;
	int		check_error;

	if (argc != 5)
		return (ft_printf(2, "Error.\nInvalid arguments."), 0);
	new_env.envp = envp;
	new_env.env_path = get_path(envp);
	if (!new_env.env_path)
		return (ft_printf(2, "Error.\nInvalid path."), 0);
	fd_in = open(argv[1], O_RDONLY);
	if (fd_in == -1)
	{
		perror("file ");
		fd_in = open("/dev/null", O_RDONLY);
		if (fd_in == -1)
			exit(1);
		argv++;
	}
	check_error = ft_check_and_exec(argv, new_env, fd_in);
	wait(NULL);
	wait(NULL);
	close(fd_in);
	return (check_error);
}
