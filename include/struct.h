/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 21:51:06 by pandemonium       #+#    #+#             */
/*   Updated: 2025/08/01 16:15:24 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# define _POSIX_C_SOURCE 200809L
# include <signal.h>
# include <stdbool.h>
# include <stddef.h>

typedef struct s_pipex
{
	pid_t					*child_tab;
	int						child_index;
	int						prev_fd;
	int						end[2];
}							t_pipex;

// ==============================================
// ================== EXEC ======================
// ==============================================

typedef struct s_exec_pipeline
{
	char					**cmd;
	char					*infile;
	char					*outfile;
	int						end[2];
	bool					if_infile;
	bool					if_outfile;
	bool					if_append;
	bool					if_here_doc;
	bool					if_quit;
	struct s_exec_pipeline	*pipe_to;
}							t_exec;

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
}							t_TOK_TYPE;

typedef struct s_tok
{
	t_TOK_TYPE				type;
	char					*word;
	struct s_tok			*next;
}							t_tok;

// ==============================================
// ================== SIGNALS ===================
// ==============================================

typedef struct s_signal
{
	struct sigaction		ctrl_c;
	struct sigaction		ctrl_dump;
}							t_signal;

// ==============================================
// ============== GLOBAL STRUCT =================
// ==============================================

typedef struct s_shell
{
	t_signal				*signals;
	t_tok					*tok;
	t_exec					*exec;
	t_pipex					*pipex;
	char					*input;
	char					*pid;
	char					*var;
	char					**env;
	char					**secret;
	int						error;
}							t_shell;
#endif