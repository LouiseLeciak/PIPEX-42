/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleciak <lleciak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:39:12 by lleciak           #+#    #+#             */
/*   Updated: 2024/03/18 15:41:58 by lleciak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./utils/headers/pipex.h"

char	*get_path(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A' && envp[i][2] == 'T'
			&& envp[i][3] == 'H' && envp[i][4] == '=')
			return (envp[i]);
		else
			i++;
	}
	return (NULL);
}

char	*final_path(char *argv, char *env_path)
{
	int		i;
	char	*cmd;
	char	*path_cmd;
	char	**path;

	if (!access(argv, F_OK | X_OK))
		return (ft_strdup(argv));
	path = ft_split(env_path + 5, ':');
	i = 0;
	cmd = ft_strjoin("/", argv);
	while (path[i])
	{
		path_cmd = ft_strjoin(path[i], cmd);
		if (access(path_cmd, F_OK | X_OK) == 0)
		{
			free(cmd);
			free_tab(path);
			return (path_cmd);
		}
		free(path_cmd);
		i++;
	}
	free(cmd);
	free_tab(path);
	return (NULL);
}
