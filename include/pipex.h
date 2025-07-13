/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 21:46:44 by pandemonium       #+#    #+#             */
/*   Updated: 2025/07/13 15:19:26 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define PIPEX shell->pipex
# define NONE -999


// ==============================================
// ================= PIPEX MAIN =================
// ==============================================

int		pipex(t_shell *shell);

// ==============================================
// ================= PIPEX UTILS ================
// ==============================================

int     outfile_management(t_exec *exec, int *end, t_shell *shell);
int		pipe_outfile(t_shell *shell, t_exec *exec, int *fd_outfile);
void	check_status(int status, t_shell *shell);
void	next_pipe(t_shell *shell, pid_t child, int *end);
int		node_number(t_exec *lst_exec);

// ==============================================
// ================= EXEC =======================
// ==============================================
int		exec_cmd(char **cmd, t_shell *shell);
int		exec_proc(char **cmd_parsed, char **all_paths, t_shell *shell, int i);
int		handle_path_cmd(char **cmd_parsed, char *path, t_shell *shell);
char	**find_path_env(t_shell *shell);

// ==============================================
// ================ HERE_DOC ====================
// ==============================================
char	**loop_here_doc(char *delimiter, t_shell *shell);
int		here_doc_pipe(t_exec *exec, t_shell *shell);
int		ft_is_empty(char *str);
void	close_fd(t_shell *shell, int fd, int to_close);

#endif