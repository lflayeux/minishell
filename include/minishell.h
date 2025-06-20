/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 21:41:38 by pandemonium       #+#    #+#             */
/*   Updated: 2025/06/20 11:10:22 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// ==============================================
// ================== LIBRARIES =================
// ==============================================

// ============ LIBRARIES ============
# include <readline/history.h>
# include <readline/readline.h>
# include <fcntl.h>
# include "../libft/libft.h"

// ============ INTERNAL HEADERS ============
# include "struct.h"
# include "error.h"
# include "signals.h"
# include "tokenization.h"
# include "expansion.h"
# include "execution.h"
# include "pipex.h"

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



# define FALSE 0
# define TRUE 1
# define ERROR -1

// ==============================================
// =================  EXPAND ====================
// ==============================================

void	expand(t_shell *shell);

// ==============================================
// ==================  UTILS ====================
// ==============================================

void	init_pipex(t_shell *shell);
void	init_shell(t_shell *shell, char **envp);
void	reset_shell(t_shell *shell);
void	free_all(t_shell *shell);

#endif