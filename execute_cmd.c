/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 19:13:16 by dagudelo          #+#    #+#             */
/*   Updated: 2024/04/19 19:15:02 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error(const char *var, const char *msg)
{
	size_t	var_len;
	size_t	msg_len;
	size_t	total_len;
	char	*error_msg;

	var_len = ft_strlen(var);
	msg_len = ft_strlen(msg);
	total_len = var_len + msg_len;
	error_msg = (char *)malloc(sizeof(char) * total_len + 1);
	ft_memcpy(error_msg, var, var_len);
	ft_memcpy(error_msg + var_len, msg, msg_len);
	error_msg[total_len] = '\0';
	write(STDERR_FILENO, error_msg, total_len);
	free(error_msg);
}

void	check_cmd_args(char **cmd_args, t_data *data)
{
	int	i;

	if (cmd_args == NULL || cmd_args[0] == NULL)
	{
		write(STDERR_FILENO, "Command not found\n", 18);
		free_malloc_split(cmd_args);
		if (data->pid == data->pid1)
			exit(0);
		else
			exit(127);
	}
	i = 0;
	while (cmd_args[i] != NULL)
	{
		if (ft_strchr(cmd_args[i], '/') != NULL
			&& access(cmd_args[i], F_OK) == -1)
		{
			data->first_message = 1;
			print_error(cmd_args[i], ": No such file or directory\n");
		}
		i++;
	}
}

void	error_execve_check(char **cmd_args)
{
	print_error(cmd_args[0], ": Permission denied\n");
	if (errno == EACCES)
		exit(126);
	else
		exit(1);
}

void	check_cmd_access_final_path(char **cmd_args, char *path_final,
		t_data *data)
{
	int	null_fd;

	if (data->fds.infile == -1)
	{
		null_fd = open("/dev/null", O_CREAT);
		dup2(null_fd, STDERR_FILENO);
		close(null_fd);
	}
	if (access(cmd_args[0], X_OK) == 0)
	{
		if (execve(cmd_args[0], cmd_args, data->envp) == -1)
			error_execve_check(cmd_args);
	}
	else
		path_final_execution(data, path_final, cmd_args, null_fd);
}

void	execute_cmd(char *cmd, t_data *data)
{
	char	**cmd_args;
	char	*path_final;

	path_final = NULL;
	if (cmd != NULL && ft_strncmp(cmd, "", 1) != 0)
	{
		cmd_args = ft_split(cmd, ' ');
		check_cmd_args(cmd_args, data);
		check_cmd_access_final_path(cmd_args, path_final, data);
		print_messages_error(cmd_args, data);
		free_malloc_split(cmd_args);
		data->first_message = 0;
		if (path_final != NULL)
			free(path_final);
		if (data->pid == data->pid1)
			exit(0);
		else
			exit(127);
	}
}
