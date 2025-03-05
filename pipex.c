/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:31:31 by dagudelo          #+#    #+#             */
/*   Updated: 2024/04/19 14:49:08 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_exit_status1(int *exit_status1, t_data *data)
{
	if (WIFEXITED(data->status1))
	{
		*exit_status1 = WEXITSTATUS(data->status1);
		if (*exit_status1 == 141)
			*exit_status1 = 0;
		if (data->fds.infile == -1 && data->fds.outfile != -1)
			*exit_status1 = 0;
	}
	else if (WIFSIGNALED(data->status1))
	{
		*exit_status1 = 128 + WTERMSIG(data->status1);
		if (*exit_status1 == 141)
			*exit_status1 = 0;
		if (data->fds.infile == -1 && data->fds.outfile != -1)
			*exit_status1 = 0;
	}
	else
	{
		if (check_two_args(data->av[2], data->av[3], data) == false)
			*exit_status1 = 127;
		else
			*exit_status1 = 0;
	}
}

void	handle_exit_status2(int *exit_status2, t_data *data)
{
	if (WIFEXITED(data->status2))
	{
		*exit_status2 = WEXITSTATUS(data->status2);
		if (*exit_status2 == 141)
			*exit_status2 = 0;
		if (data->fds.infile == -1 && data->fds.outfile != -1)
			*exit_status2 = 0;
	}
	else if (WIFSIGNALED(data->status2))
	{
		*exit_status2 = 128 + WTERMSIG(data->status2);
		if (*exit_status2 == 141)
			*exit_status2 = 0;
		if (data->fds.infile == -1 && data->fds.outfile != -1)
			*exit_status2 = 0;
	}
}

void	handle_exit(int *exit_status1, int *exit_status2, t_data *data)
{
	data->pid_current = waitpid(-1, &data->status, 0);
	while (data->pid_current > 0)
	{
		if (data->pid_current == data->pid1)
			data->status1 = data->status;
		else if (data->pid_current == data->pid2)
			data->status2 = data->status;
		data->pid_current = waitpid(-1, &data->status, 0);
	}
	handle_exit_status1(exit_status1, data);
	handle_exit_status2(exit_status2, data);
}

void	create_pid_process(t_data *data)
{
	if (data->fds.infile != -1)
	{
		data->pid1 = create_child_process((t_fds){data->fds.infile,
				data->pipefd[1]}, data->av[2], data);
		if (data->pid1 == -1)
		{
			perror("fork");
			close_pipes_and_files(data);
			exit(EXIT_FAILURE);
		}
	}
	data->open_result = open_files(data);
	if (data->fds.infile != -1)
		data->pid2 = create_child_process((t_fds){data->pipefd[0],
				data->fds.outfile}, data->av[3], data);
	else
		data->pid2 = create_child_process((t_fds){data->fds.infile,
				data->fds.outfile}, data->av[3], data);
	if (data->pid2 == -1)
	{
		perror("fork");
		close_pipes_and_files(data);
		exit(EXIT_FAILURE);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	int		exit_status1;
	int		exit_status2;

	init_values_data(&data);
	data.ac = ac;
	data.av = av;
	if (data.ac != 5)
		return (1);
	data.envp = envp;
	open_fd_and_pipes(&data);
	create_pid_process(&data);
	if (data.open_result)
		return (data.open_result);
	if (!can_execute(data.av[3]) && ft_strstr(data.av[3], "./") != NULL)
		return (print_error(data.av[3], ": Permission denied\n"), 126);
	handle_exit(&exit_status1, &exit_status2, &data);
	if (exit_status1 != 0)
		return (exit_status1);
	else if (exit_status2 != 0)
		return (exit_status2);
}
