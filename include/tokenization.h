/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 18:10:25 by lflayeux          #+#    #+#             */
/*   Updated: 2025/07/13 18:01:29 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZATION_H
# define TOKENIZATION_H

# include "struct.h"

// ==============================================
// =================== TOKENS ===================
// ==============================================

t_tok	*ft_lstnew_tok(t_TOK_TYPE type, char *word, t_shell *shell);
t_tok	*ft_lstlast_tok(t_tok *lst);
void	ft_lstadd_back_tok(t_tok **token, t_tok *new);
void	ft_lstclear_tok(t_tok *lst);
int		symbol_token(char *input, t_shell *shell);
int		word_token(char *input, t_shell *shell);
int		tokenize(t_shell *shell);
void	add_word_tok(char *input, t_shell *shell, char *word);
int		len_word_tok(char *input);
int		is_symbol(char c);
int		is_space(char c);

#endif