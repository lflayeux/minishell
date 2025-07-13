/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 00:34:45 by pandemonium       #+#    #+#             */
/*   Updated: 2025/07/13 17:58:51 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

// ==============================================
// ================== INIT ======================
// ==============================================
void	exec_init(t_exec *node_exec);
void	get_pid(t_shell *shell);
void	init_fd(t_shell *shell);
void	init_pipex(t_shell *shell);
void	reset_shell(t_shell *shell);
char	**init_env(t_shell *shell, char **envp);
int		ft_check_env(char **env, char *to_check);
void	init_shell(t_shell *shell, char **envp);
int		task_init(t_exec *exec, t_shell *shell);

// ==============================================
// ================== free(direction) ======================
// ==============================================
void	free_all(t_shell *shell);
void	free_error(t_shell *shell);

#endif