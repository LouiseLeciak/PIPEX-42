/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleciak <lleciak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 09:53:57 by lleciak           #+#    #+#             */
/*   Updated: 2024/03/18 15:59:49 by lleciak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./utils/headers/pipex.h"

void	get_fd_in(char ***argv, t_env *all)
{
	if (!ft_strcmp((*argv)[1], "here_doc"))
	{
		all->fd_in = here_doc(*argv);
		all->doc = 1;
	}
	else
	{
		all->fd_in = open((*argv)[1 + all->doc], O_RDONLY);
		if (all->fd_in == -1)
		{
			perror("file ");
			all->fd_in = open("/dev/null", O_RDONLY);
			if (all->fd_in == -1)
				exit(1);
			(*argv)++;
		}
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_env	all;

	all.doc = 0;
	if (argc < 5)
		return (ft_printf(2, "Error.\nInvalid arguments."), 0);
	all.envp = envp;
	all.env_path = get_path(envp);
	if (!all.env_path)
		return (ft_printf(2, "Error.\nInvalid path."), 0);
	get_fd_in(&argv, &all);
	ft_check_and_exec(argv + all.doc, all, all.fd_in);
	all.i = 0;
	while (all.i++ < argc - (2 + all.doc))
		wait(NULL);
	return (close(all.fd_in), 0);
}
