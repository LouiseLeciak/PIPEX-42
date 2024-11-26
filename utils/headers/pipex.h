/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleciak <lleciak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 08:17:04 by lleciak           #+#    #+#             */
/*   Updated: 2024/03/15 13:43:14 by lleciak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./ft_printf.h"
# include "./get_next_line.h"

# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>

//struct
typedef struct s_env {
	char	*env_path;
	char	**envp;
	int		fd_in;
	int		fd_doc;
	int		i;
	int		doc;
}				t_env;

//utils
char	**ft_split(char *str, char sep);
void	free_tab(char **tab);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strcmp(const char *s1, const char *s2);

//path
char	*final_path(char *argv, char *env_path);
char	*get_path(char **envp);

//exec
int		ft_forkex(char *tab_args[], char *envp[], int fd, int *pip);
int		ft_check_and_exec(char *argv[], t_env new_env, int fd);

//bonus
int		here_doc(char *argv[]);

#endif