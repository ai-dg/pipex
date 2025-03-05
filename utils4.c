/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 19:09:51 by dagudelo          #+#    #+#             */
/*   Updated: 2024/04/19 13:20:25 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_fd_and_pipes(t_data *data)
{
	errno = 0;
	data->fds.infile = open(data->av[1], O_RDONLY);
	if (data->fds.infile < 0)
	{
		write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
		write(STDERR_FILENO, "\n", 1);
		data->fds.infile = -1;
		errno = 0;
	}
	if (data->fds.infile != -1)
	{
		if (pipe(data->pipefd) == -1)
		{
			perror("pipe");
			if (data->fds.infile != -1)
				close(data->fds.infile);
			if (data->fds.outfile != -1)
				close(data->fds.outfile);
			exit(EXIT_FAILURE);
		}
	}
}

void	setup_child_process(t_fds fds, char *cmd, t_data *data)
{
	if (fds.infile != -1)
	{
		dup2(fds.infile, STDIN_FILENO);
		close(fds.infile);
	}
	if (fds.outfile != -1)
	{
		dup2(fds.outfile, STDOUT_FILENO);
		close(fds.outfile);
	}
	if (data->pipefd[0] != -1)
		close(data->pipefd[0]);
	if (data->pipefd[1] != -1)
		close(data->pipefd[1]);
	execute_cmd(cmd, data);
}

pid_t	create_child_process(t_fds fds, char *cmd, t_data *data)
{
	pid_t	pid;

	pid = fork();
	data->pid = pid;
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
		setup_child_process(fds, cmd, data);
	if (fds.infile != -1)
		close(fds.infile);
	if (fds.outfile != -1)
		close(fds.outfile);
	return (pid);
}

bool	can_execute(const char *filepath)
{
	return (access(filepath, X_OK) == 0);
}

int	open_files(t_data *data)
{
	errno = 0;
	data->fds.outfile = open(data->av[data->ac - 1],
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->fds.outfile < 0)
	{
		write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
		write(STDERR_FILENO, "\n", 1);
		errno = 0;
		return (1);
	}
	return (0);
}
