/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:11:08 by dagudelo          #+#    #+#             */
/*   Updated: 2024/04/19 19:13:58 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_file_descriptors
{
	int		infile;
	int		outfile;
}			t_fds;

typedef struct s_data
{
	t_fds	fds;
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;
	pid_t	pid;
	pid_t	pid_current;
	int		ac;
	char	**av;
	char	**envp;
	int		status;
	int		status1;
	int		status2;
	char	**paths;
	bool	cmd1_found;
	bool	cmd2_found;
	int		open_result;
	char	*path;
	int		first_message;
}			t_data;

char		**ft_split(const char *s, char c);
void		free_malloc_split(char **dest);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strchr(const char *s, int c);
int			ft_strlen(const char *s);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
char		*ft_strdup(const char *src);
char		*search_path(t_data *data, char **cmd_args);
void		cmd_execute(char *path_final, char **cmd_args, t_data *data);
int			open_files(t_data *data);
void		init_values_data(t_data *data);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		open_fd_and_pipes(t_data *data);
void		setup_child_process(t_fds fds, char *cmd, t_data *data);
pid_t		create_child_process(t_fds fds, char *cmd, t_data *data);
bool		can_execute(const char *filepath);
int			open_files(t_data *data);
void		execute_cmd(char *cmd, t_data *data);
void		print_error(const char *var, const char *msg);
void		check_cmd_args(char **cmd_args, t_data *data);
void		error_execve_check(char **cmd_args);
void		check_cmd_access_final_path(char **cmd_args, char *path_final,
				t_data *data);
void		check_cmd_args(char **cmd_args, t_data *data);
void		print_error(const char *var, const char *msg);
void		close_pipes_and_files(t_data *data);
bool		check_two_args(char *cmd1, char *cmd2, t_data *data);
void		check_cmd2_arg(char *cmd2, char **cmd_args, t_data *data);
void		check_cmd1_arg(char *cmd1, char **cmd_args, t_data *data);
char		*ft_strstr(char *str, char *to_find);
void		path_final_execution(t_data *data, char *path_final,
				char **cmd_args, int null_fd);
void		print_messages_error(char **cmd_args, t_data *data);

#endif