/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandemonium <pandemonium@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:58:35 by lflayeux          #+#    #+#             */
/*   Updated: 2025/07/09 23:15:22 by pandemonium      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "expansion.h"

void    exec_unset(t_shell *shell, int i, t_exec *exec);
void    stock_export(t_shell *shell, int i, char *cmd);
void    exec_export(t_shell	*shell, int i, t_exec *exec);
void    check_env(t_shell *shell, int i, char *cmd);
void    exec_env(t_shell *shell, int i, t_exec *exec);
int     is_valid_env(char *exec);
int     ft_get_env(char **env, char *to_check);
char    **unset_env(char *unset_env, char **env);
char    **put_env(t_shell *shell, char **env, char *cmd);
char    **set_env(t_shell *shell, int i, char *split, char **env);
void    expand_env(char **to_expand, t_shell *shell);
void    exec_pwd();
void    exec_cd(char **path, int i, t_shell *shell);
void    exec_echo(t_exec *exec, int i);
int     built_in(t_exec *exec, t_shell *shell, int flag);

#endif
