/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandemonium <pandemonium@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 21:51:06 by pandemonium       #+#    #+#             */
/*   Updated: 2025/06/07 00:36:34 by pandemonium      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# define _POSIX_C_SOURCE 200809L
# include <signal.h>

// ==============================================
// ================== SIGNALS ===================
// ==============================================

typedef struct s_signal
{
	struct sigaction		ctrl_c;
	struct sigaction		ctrl_dump;
}							t_signal;

// ==============================================
// ================== TOKEN =====================
// ==============================================

typedef enum e_tok_type
{
	PIPE,
	INFILE,
	OUTFILE,
	HERE_DOC,
	APPEND,
	WORD,
}							TOK_TYPE;

typedef struct s_tok
{
	TOK_TYPE				type;
	char					*word;
	struct s_tok			*next;
}			t_tok;

// ==============================================
// ============== GLOBAL STRUCT =================
// ==============================================

typedef struct s_shell
{
	t_signal				*signals;
	t_tok					*tok;
	char					*input;
	char					*pid;
	int						error;
	char					*var;
}							t_shell;
#endif