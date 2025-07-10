/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: pandemonium <pandemonium@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:32:01 by lflayeux          #+#    #+#             */
/*   Updated: 2025/07/10 23:44:50 by pandemonium      ###   ########.fr       */
=======
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:32:01 by lflayeux          #+#    #+#             */
/*   Updated: 2025/07/11 00:04:37 by alex             ###   ########.fr       */
>>>>>>> 10719f067d6424fc263ce33c5051a03e59ef6419
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

# define TYPE init->type
# define N ((*init)->next)
# define ADD_BACK_EXEC ft_lstadd_back_exec
# define NEW_EXEC ft_lstnew_exec
// ==============================================
// ===================== LST ====================
// ==============================================

void	ft_lstclear_exec(t_exec *lst);
void	del_node_exec(void *exec_node);
void	ft_lstadd_back_exec(t_exec **token, t_exec *new);
t_exec	*ft_lstlast_exec(t_exec *lst);

// ==============================================
// ==================== UTILS ===================
// ==============================================
int		word_number(t_tok *init, t_tok *end);
int		if_here_doc(t_exec *node_exec, t_tok **init, t_shell *shell);
int		if_append(t_exec *node_exec, t_tok **init);
int		if_outfile(t_exec *node_exec, t_tok **init, t_shell *shell);
int		if_infile(t_exec *node_exec, t_tok **init);

void	exec_init(t_exec *node_exec);

t_exec	*ft_lstnew_exec(t_tok *init, t_tok *end, t_shell *shell);
int		create_lst_exec(t_shell *shell);

#endif