/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 21:41:38 by pandemonium       #+#    #+#             */
/*   Updated: 2025/07/27 19:14:45 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// ==============================================
// ================== LIBRARIES =================
// ==============================================

# include <readline/history.h>
# include <readline/readline.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include "../libft/libft.h"

// ==============================================
// ================== HEADERS ===================
// ==============================================
# include "struct.h"
# include "error.h"
# include "signals.h"
# include "tokenization.h"
# include "expansion.h"
# include "execution.h"
# include "pipex.h"
# include "built_in.h"
# include "utils.h"

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
// ================== DEFINES ===================
// ==============================================

# define FALSE 0
# define TRUE 1
# define ERROR -1

extern int	g_signal_global;

// ==============================================
// =================  EXPAND ====================
// ==============================================

int			expand(t_shell *shell);

// ==============================================
// ==================  A SUPPR ==================
// ==============================================

const char	*get_token_name(int type);

#endif