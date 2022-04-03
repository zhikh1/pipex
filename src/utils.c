/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomargen <nomargen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 13:25:22 by nomargen          #+#    #+#             */
/*   Updated: 2022/04/03 13:28:19 by nomargen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/main.h"

void	free_ptr_mas(char **mas)
{
	int	i;

	i = 0;
	if (mas)
	{
		while (mas[i])
		{
			free(mas[i]);
			i++;
		}
		free(mas);
	}
	return ;
}

int	safe_open(char *file, int flags, int mode, t_pipex *pipex)
{
	int	fd;

	if (mode == 0)
		fd = open(file, flags);
	else
		fd = open(file, flags, mode);
	if (fd < 0)
		perr_exit(file, pipex);
	return (fd);
}

char	**get_path(char const *env[], t_pipex *pipex)
{
	char	**path;

	path = NULL;
	if (env == NULL)
		return (NULL);
	while (*env)
	{
		if (ft_strncmp(*env, "PATH=", 5))
			env++;
		else
		{
			path = ft_split(*env + 5, ':');
			break ;
		}
	}
	if (path == NULL)
		perr_exit("Bad env PATH", pipex);
	return (path);
}

char	*get_cmd_dir(t_pipex *pipex, char const *cmd)
{
	char	*tmp;
	char	*dir;
	int		i;

	i = 0;
	dir = NULL;
	while (pipex->path[i] && dir == NULL)
	{
		tmp = ft_strjoin(pipex->path[i], "/");
		dir = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(dir, 0))
		{
			free (dir);
			dir = NULL;
		}
		i++;
	}
	if (cmd == NULL)
		perr_exit((char *)cmd, pipex);
	return (dir);
}
