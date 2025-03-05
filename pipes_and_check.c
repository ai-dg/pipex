/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_and_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:48:25 by dagudelo          #+#    #+#             */
/*   Updated: 2024/04/19 14:46:21 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_cmd1_arg(char *cmd1, char **cmd_args, t_data *data)
{
	if (cmd1 && *cmd1)
	{
		cmd_args = ft_split(cmd1, ' ');
		data->path = search_path(data, cmd_args);
		if (cmd_args && cmd_args[0] && (access(cmd_args[0], X_OK) == 0
				|| data->path != NULL))
		{
			data->cmd1_found = true;
			free(data->path);
		}
		free_malloc_split(cmd_args);
	}
}

void	check_cmd2_arg(char *cmd2, char **cmd_args, t_data *data)
{
	if (cmd2 && *cmd2)
	{
		cmd_args = ft_split(cmd2, ' ');
		data->path = search_path(data, cmd_args);
		if (cmd_args && cmd_args[0] && (access(cmd_args[0], X_OK) == 0
				|| data->path != NULL))
		{
			data->cmd2_found = true;
			free(data->path);
		}
		free_malloc_split(cmd_args);
	}
}

bool	check_two_args(char *cmd1, char *cmd2, t_data *data)
{
	char	**cmd_args;

	data->path = NULL;
	data->cmd1_found = false;
	data->cmd2_found = false;
	cmd_args = NULL;
	check_cmd1_arg(cmd1, cmd_args, data);
	check_cmd2_arg(cmd2, cmd_args, data);
	return (data->cmd1_found && data->cmd2_found);
}

void	close_pipes_and_files(t_data *data)
{
	if (data->pipefd[0] != -1)
		close(data->pipefd[0]);
	if (data->pipefd[1] != -1)
		close(data->pipefd[1]);
	if (data->fds.infile != -1)
		close(data->fds.infile);
	if (data->fds.outfile != -1)
		close(data->fds.outfile);
}
