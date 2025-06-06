/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 21:41:38 by pandemonium       #+#    #+#             */
/*   Updated: 2025/06/06 13:58:05 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// ==============================================
// ================== LIBRARIES =================
// ==============================================

# include "../libft/libft.h"
# include "struct.h"
# include <readline/history.h>
# include <readline/readline.h>

// ==============================================
// ================== PROMPT ====================
// ==============================================

# define PROMPT GOLD "🦾 miniboss 🦾 > " RST

// ==============================================
// ================== COLORS ====================
// ==============================================

# define RED "\033[31m"
# define CYAN "\033[36m"
# define RST "\033[0m"
# define YLW "\033[33m"
# define GRN "\033[32m"
# define GOLD "\033[38;5;220m"

// ==============================================
// ==================  ERRORS ===================
// ==============================================

# define MALLOC 0

void    print_error(t_shell *shell, int err);
// ==============================================
// ================== SIGNALS ===================
// ==============================================

void	set_signal(t_signal *signals);
void	parent_signals(t_signal *signals);
void	child_signals(t_signal *signals);
void	reset_signals(t_signal *signals);

// ==============================================
// =================== TOKENS ===================
// ==============================================
# define NEW_TOK ft_lstnew_tok
# define ADD_TOK ft_lstadd_back_tok

t_tok	*ft_lstnew_tok(TOK_TYPE type, char *word, t_shell *shell);
void	ft_lstadd_back_tok(t_tok **token, t_tok *new);
void	ft_lstclear_tok(t_tok *lst);
void    tokenize(t_shell *shell);

// ==============================================
// ==================  UTILS ====================
// ==============================================

void	init_shell(t_shell *shell, char **envp);
void	reset_shell(t_shell *shell);
void	free_all(t_shell *shell);

#endif