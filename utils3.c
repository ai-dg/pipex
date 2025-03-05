/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:32:26 by dagudelo          #+#    #+#             */
/*   Updated: 2024/04/19 19:05:51 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	joint_str_final_path(char *tmp, char **cmd_args, int len_path_total)
{
	ft_strlcat(tmp, "/", 2);
	ft_strlcat(tmp, cmd_args[0], len_path_total - ft_strlen(tmp));
}

static char	*search_final_path(t_data *data, char **cmd_args)
{
	char	*path_final;
	char	*tmp;
	int		j;
	int		len_path_total;

	path_final = NULL;
	j = 0;
	while (data->paths[j] != NULL)
	{
		len_path_total = ft_strlen(data->paths[j]) + ft_strlen(cmd_args[0]) + 2;
		tmp = (char *)malloc(sizeof(char) * (len_path_total + 1));
		if (tmp == NULL)
			return (free_malloc_split(data->paths), NULL);
		ft_strlcpy(tmp, data->paths[j], len_path_total);
		joint_str_final_path(tmp, cmd_args, len_path_total);
		if (access(tmp, X_OK) == 0)
		{
			path_final = ft_strdup(tmp);
			free(tmp);
			break ;
		}
		free(tmp);
		j++;
	}
	return (path_final);
}

char	*search_path(t_data *data, char **cmd_args)
{
	int		i;
	char	*path_alpha;
	char	*path_final;

	i = 0;
	path_final = NULL;
	while (data->envp[i] != NULL)
	{
		if (ft_strncmp(data->envp[i], "PATH=", 5) == 0)
		{
			path_alpha = ft_strchr(data->envp[i], '=') + 1;
			if (path_alpha != NULL)
			{
				data->paths = ft_split(path_alpha, ':');
				path_final = search_final_path(data, cmd_args);
				free_malloc_split(data->paths);
				data->paths = NULL;
			}
			break ;
		}
		i++;
	}
	return (path_final);
}

void	cmd_execute(char *path_final, char **cmd_args, t_data *data)
{
	if (path_final != NULL)
	{
		if (execve(path_final, cmd_args, data->envp) == -1)
		{
			perror("execve");
			free_malloc_split(cmd_args);
			free(path_final);
			exit(127);
		}
	}
}

void	init_values_data(t_data *data)
{
	data->fds.infile = 0;
	data->fds.outfile = 0;
	data->pipefd[0] = 0;
	data->pipefd[1] = 0;
	data->pid1 = 0;
	data->pid2 = 0;
	data->pid = 0;
	data->pid_current = 0;
	data->ac = 0;
	data->av = NULL;
	data->envp = NULL;
	data->status = 0;
	data->status1 = 0;
	data->status2 = 0;
	data->paths = NULL;
	data->cmd1_found = false;
	data->cmd2_found = false;
	data->open_result = 0;
	data->path = NULL;
	data->first_message = 0;
}
