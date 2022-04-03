/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomargen <nomargen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 21:21:51 by nomargen          #+#    #+#             */
/*   Updated: 2022/04/03 13:33:07 by nomargen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/main.h"

void	close_free(t_pipex *pipex)
{
	if (pipex == NULL)
		return ;
	if (pipex->in_fd >= 0)
		close(pipex->in_fd);
	if (pipex->out_fd >= 0)
		close(pipex->out_fd);
	free_ptr_mas(pipex->path);
	if (pipex->pipe_fd)
	{
		if (pipex->pipe_fd[0] >= 0)
			close(pipex->pipe_fd[0]);
		if (pipex->pipe_fd[1] >= 0)
			close(pipex->pipe_fd[1]);
	}
}

void	perr_exit(char *err_str, t_pipex *pipex)
{
	close_free(pipex);
	perror(err_str);
	exit(EXIT_FAILURE);
}

void	child(char const *cmd_str, int in_fd, int out_fd, t_pipex *pipex)
{
	char	*cmd_dir;
	char	**cmd_w_args;

	cmd_w_args = ft_split(cmd_str, ' ');
	cmd_dir = get_cmd_dir(pipex, cmd_w_args[0]);
	dup2(in_fd, 0);
	dup2(out_fd, 1);
	close_free(pipex);
	execve(cmd_dir, cmd_w_args, (char **)pipex->env);
	if (cmd_dir)
		free(cmd_dir);
	free_ptr_mas(cmd_w_args);
	perr_exit(cmd_dir, NULL);
}

void	init_pipex(t_pipex *pipex, char const *argv[], char const *env[])
{
	if (pipex == NULL)
		perr_exit("Bad pipex ptr", NULL);
	pipex->path = get_path(env, pipex);
	pipex->in_fd = safe_open((char *)argv[1], O_RDONLY, 0, pipex);
	pipex->out_fd = safe_open((char *)argv[4],
			O_WRONLY | O_CREAT | O_TRUNC, 0664, pipex);
	pipex->env = env;
	if (pipe(pipex->pipe_fd) != 0)
		perr_exit("Cannot to create a pipe!", pipex);
}

int	main(int argc, char const *argv[], char const *env[])
{
	t_pipex	pipex;
	int		pid[2];
	int		status;

	if (argc != 5)
		perr_exit("Bad argument cnt!", NULL);
	init_pipex(&pipex, argv, env);
	pid[0] = fork();
	if (pid[0] == 0)
		child(argv[2], pipex.in_fd, pipex.pipe_fd[1], &pipex);
	else if (pid[0] < 0)
		perr_exit("Cannot to create a fork 1!", &pipex);
	pid[1] = fork();
	if (pid[1] == 0)
		child(argv[3], pipex.pipe_fd[0], pipex.out_fd, &pipex);
	else if (pid[1] < 0)
		perr_exit("Cannot to create a fork 2!", &pipex);
	close_free(&pipex);
	wait(NULL);
	wait(&status);
	return (status);
}
