/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:17:39 by lflayeux          #+#    #+#             */
/*   Updated: 2025/05/22 18:52:30 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// ==============================================
// ================== LIBRARIES =================
// ==============================================

# include "../libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

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
// ================ MAIN.C ======================
// ==============================================

char						*check_dollar_env(char **token, int *i, char **env);
int							expansion_len(char **token, char **env);
char						*get_pid(void);
char						*find_var_spe(char *s, int index);

// ==============================================
// ================== SIGNALS ===================
// ==============================================

typedef struct s_signal
{
	struct sigaction		ctrl_c;
	struct sigaction		ctrl_dump;
}							t_signal;

void						set_signal(t_signal *signals);
void						parent_signals(t_signal *signals);
void						child_signals(t_signal *signals);
void						reset_signals(t_signal *signals);
void						handle_ctrl_c_interactive(int signal);
void						handle_ctrl_c_action(int signal);
void						handle_ctrl_dump(int signal);

// ==============================================
// ================ TOKENISATION ================
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

void						tokenize(char **input, t_tok **token);
t_tok						*ft_lstnew_tok(TOK_TYPE type, char *word);
t_tok						*ft_lstlast_tok(t_tok *lst);
void						ft_lstadd_back_tok(t_tok **token, t_tok *new);

// ==============================================
// ================ EXECUTION ===================
// ==============================================

typedef struct s_exec_pipeline
{
	char					**cmd;
	char					*infile;
	char					*outfile;
	bool					if_infile;
	bool					if_outfile;
	struct s_exec_pipeline	*pipe_to;
}							t_exec;

// === WORD PARSING ===

int							word_identification(t_tok **token, char **env);

// === PIPE PROCESS ===

void						create_lst_exec(t_exec **lst_exec, t_tok **token);

// === LST EXEC ===

void						ft_lstadd_back_exec(t_exec **token, t_exec *new);
t_exec						*ft_lstlast_exec(t_exec *lst);

// === TESTS ===

void						test_signals(t_signal signals, char **env);

void    built_in(t_exec **exec, int *i);
#endif
