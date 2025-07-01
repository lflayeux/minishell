/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 21:46:44 by pandemonium       #+#    #+#             */
/*   Updated: 2025/07/01 12:01:32 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define PIPEX shell->pipex
# define NONE -999


int	pipex(t_shell *shell);
int	task_init(t_exec *exec, t_shell *shell);
int	node_number(t_exec *lst_exec);
int	middle_proc(t_exec *exec, t_shell *shell);
int	end_or_pipe(t_exec *exec, pid_t child, int *end, t_shell *shell);


int	exec_cmd(char **cmd, t_shell *shell);
int	exec_proc(char **cmd_parsed, char **all_paths, t_shell *shell, int i);
int	handle_path_cmd(char **cmd_parsed, char *path, t_shell *shell);
char	**find_path_env(t_shell *shell);

void	close_fd(t_shell *shell, int fd, int to_close);
void	init_fd(t_shell *shell);
int		loop_here_doc(char *delimiter, int *end, t_shell *shell);
int		here_doc_proc(t_shell *shell, t_exec *exec, int *end);
int		ft_is_empty(char *str);

#endif