/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:58:35 by lflayeux          #+#    #+#             */
/*   Updated: 2025/07/10 20:25:50 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "expansion.h"

# define FREE free(direction)

void    exec_unset(t_shell *shell, int i, t_exec *exec);
void    stock_export(t_shell *shell, char *cmd);
void    exec_export(t_shell	*shell, int i, t_exec *exec);
void    check_env(t_shell *shell, char *cmd, char ***tmp);
int		exec_env(t_shell *shell, int i, t_exec *exec);
int     is_valid_env(char *exec);
int     ft_get_env(char **env, char *to_check);
char    **unset_env(char *unset_env, char **env);
char    **put_env(t_shell *shell, char **env, char *cmd);
char    **set_env(char *split, char **env, char *cmd);
void	expand_env(char **to_expand, t_shell *shell);

// ==============================================
// ===================== PWD ====================
// ==============================================
int		exec_pwd();
// ==============================================
// ===================== CD =====================
// ==============================================
int		exec_cd(char **path, int i, t_shell *shell);
// ==============================================
// ==================== ECHO ====================
// ==============================================
int     exec_echo(t_exec *exec, int i);
int     built_in(t_exec *exec, t_shell *shell, int flag);

#endif
