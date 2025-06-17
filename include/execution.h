/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:32:01 by lflayeux          #+#    #+#             */
/*   Updated: 2025/06/17 18:57:02 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

// ==============================================
// ===================== LST ====================
// ==============================================

void	ft_lstclear_exec(t_exec *lst);
void	del_node_exec(void *exec_node);
void	ft_lstadd_back_exec(t_exec **token, t_exec *new);
t_exec	*ft_lstlast_exec(t_exec *lst);


void	exec_init(t_exec *node_exec);
void	create_lst_exec(t_shell *shell);

#endif