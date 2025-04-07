/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:17:39 by lflayeux          #+#    #+#             */
/*   Updated: 2025/04/07 15:06:10 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		MINISHELL_H
# define	MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include "./libft/libft.h"

// PROMPT
# define	PROMPT GOLD "🦾 miniboss 🦾 > " RST

// COLORS
# define RED     "\033[31m"
# define CYAN    "\033[36m"
# define RST   "\033[0m"
# define YLW  "\033[33m"
# define GRN   "\033[32m"
#define GOLD    "\033[38;5;220m"

#endif
