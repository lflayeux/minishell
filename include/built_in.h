/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:58:35 by lflayeux          #+#    #+#             */
/*   Updated: 2025/06/26 18:07:43 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

void    exec_unset(t_shell *shell, int i);
void    stock_export(t_shell *shell, int i);
void    exec_export(t_shell	*shell, int i);
void    check_env(t_shell *shell, int i);
void    exec_env(t_shell *shell, int i);
int     is_valid_env(char *exec);
int     ft_get_env(char **env, char *to_check);
char    **unset_env(char *unset_env, char **env);
char    **put_env(t_shell *shell, int i, char **env);
char    **set_env(t_shell *shell, int i, char *split, char **env);
void    exec_pwd();
void    exec_cd(char **path, int i);
void    exec_echo(t_exec *exec, int i);
int     built_in(t_exec *exec, t_shell *shell);

#endif
