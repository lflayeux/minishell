/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandemonium <pandemonium@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 22:48:23 by pandemonium       #+#    #+#             */
/*   Updated: 2025/06/01 22:56:58 by pandemonium      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <sys/types.h>
# include <stdbool.h>
# include <signal.h>

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
}							t_tok;

// ==============================================
// ================== EXEC ======================
// ==============================================

typedef struct s_exec_pipeline
{
	char					**cmd;
	char					*infile;
	char					*outfile;
	char					*delimiter;
	bool					if_infile;
	bool					if_outfile;
	bool					if_append;
	bool					if_here_doc;
	struct s_exec_pipeline	*pipe_to;
}							t_exec;

// ==============================================
// ===================== PIPEX ==================
// ==============================================

typedef struct s_pipex
{
	char					**av;
	int						ac;
	char					**envp;
	pid_t					*child_tab;
	int						fd_infile;
	int						fd_outfile;
}							t_pipex;

// ==============================================
// =================== MALLOC ===================
// ==============================================

typedef struct s_malloc
{
	char					**tab;
	char					*str;
	struct s_malloc			*next;
}							t_malloc;

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
	char					**env;
	char					**secret;
	t_malloc				*malloc;
	int						error;
	pid_t					*child_tab;
	int						child_index;
	int						prev_fd;
}							t_shell;

# endif