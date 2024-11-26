/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleciak <lleciak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 09:15:36 by lleciak           #+#    #+#             */
/*   Updated: 2024/03/20 18:25:51 by lleciak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./utils/headers/pipex.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	if (fd < 0)
		return ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

int	here_doc(char *argv[])
{
	char	*cmp;
	char	*limiter;
	int		pip_doc[2];

	limiter = ft_strjoin(argv[2], "\n");
	cmp = NULL;
	pipe(pip_doc);
	while (ft_strcmp(cmp, limiter) != 0)
	{
		if (cmp)
			free(cmp);
		ft_printf(1, "here_doc > ");
		cmp = get_next_line(0);
		if (ft_strcmp(cmp, limiter) != 0)
			ft_putstr_fd(cmp, pip_doc[1]);
	}
	if (cmp)
		free(cmp);
	close(pip_doc[1]);
	free(limiter);
	return (pip_doc[0]);
}
