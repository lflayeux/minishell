/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:17:39 by lflayeux          #+#    #+#             */
/*   Updated: 2025/04/16 18:48:18 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		MINISHELL_H
# define	MINISHELL_H

# include "../libft/libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

// PROMPT
# define	PROMPT GOLD "🦾 miniboss 🦾 > " RST

// COLORS
# define RED     "\033[31m"
# define CYAN    "\033[36m"
# define RST   "\033[0m"
# define YLW  "\033[33m"
# define GRN   "\033[32m"
# define GOLD    "\033[38;5;220m"

// STRUCT SIGNALS
typedef	struct s_signal
{
	struct	sigaction	ctrl_c;
	struct	sigaction	ctrl_dump;
}			t_signal;

// SIGNALS
void	set_signal(t_signal *signals);
void	parent_signals(t_signal *signals);
void	child_signals(t_signal *signals);
void	reset_signals(t_signal *signals);
void	handle_ctrl_c_interactive(int signal);
void	handle_ctrl_c_action(int signal);
void	handle_ctrl_dump(int signal);

// TESTS
void	test_signals(t_signal signals, char **env);

#endif
