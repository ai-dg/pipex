/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:02:03 by dagudelo          #+#    #+#             */
/*   Updated: 2024/04/19 19:15:21 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const unsigned char	*source;
	unsigned char		*destination;
	size_t				i;

	destination = dest;
	source = src;
	i = 0;
	if (!src && !dest)
		return (NULL);
	while (i < n)
	{
		destination[i] = source[i];
		i++;
	}
	return (destination);
}

char	*ft_strstr(char *str, char *to_find)
{
	int	str_pos;
	int	to_find_pos;

	str_pos = 0;
	to_find_pos = 0;
	if (to_find[0] == '\0')
		return ((char *)str);
	while (str[str_pos])
	{
		to_find_pos = 0;
		if (str[str_pos] && to_find[to_find_pos])
		{
			while (str[str_pos + to_find_pos] == to_find[to_find_pos])
			{
				to_find_pos++;
				if (!to_find[to_find_pos])
					return (&str[str_pos]);
			}
		}
		str_pos++;
	}
	return (0);
}

void	path_final_execution(t_data *data, char *path_final, char **cmd_args,
		int null_fd)
{
	path_final = search_path(data, cmd_args);
	if (path_final != NULL && access(path_final, X_OK) == 0)
	{
		if (execve(path_final, cmd_args, data->envp) == -1)
		{
			if (data->fds.infile == -1)
			{
				dup2(STDERR_FILENO, null_fd);
				close(null_fd);
			}
			error_execve_check(cmd_args);
		}
	}
}

void	print_messages_error(char **cmd_args, t_data *data)
{
	if (ft_strchr(cmd_args[0], '/') != NULL && access(cmd_args[0], F_OK) == -1
		&& data->first_message != 1)
		print_error(cmd_args[0], ": No such file or directory\n");
	else if (ft_strchr(cmd_args[0], '/') == NULL
		&& access(cmd_args[0], F_OK) == -1 && data->first_message != 1)
		print_error(cmd_args[0], ": Command not found\n");
}
