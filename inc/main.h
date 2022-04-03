/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomargen <nomargen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 21:21:45 by nomargen          #+#    #+#             */
/*   Updated: 2022/04/03 13:37:21 by nomargen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MAIN_H
# define MAIN_H

# include <stddef.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include <errno.h>
# include "../lib/libft/libft.h"

typedef struct s_pipex
{
	char		**path;
	char const	**env;
	int			in_fd;
	int			out_fd;
	int			pipe_fd[2];
}	t_pipex;

void	free_ptr_mas(char **mas);
int		safe_open(char *file, int flags, int mode, t_pipex *pipex);
char	**get_path(char const *env[], t_pipex *pipex);
char	*get_cmd_dir(t_pipex *pipex, char const *cmd);
void	perr_exit(char *err_str, t_pipex *pipex);
void	close_free(t_pipex *pipex);

#endif
