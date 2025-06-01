/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:17:39 by lflayeux          #+#    #+#             */
/*   Updated: 2025/06/01 15:02:26 by alex             ###   ########.fr       */
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
// ================== STRUCT ====================
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

typedef struct s_malloc
{
	char					**tab;
	char					*str;
	struct s_malloc			*next;
}							t_malloc;

typedef struct s_signal
{
	struct sigaction		ctrl_c;
	struct sigaction		ctrl_dump;
}							t_signal;

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

// ==============================================
// ================ MAIN.C ======================
// ==============================================

char						*check_dollar_env(char **token, int *i, char **env);
int							ft_isdelim(char c, char *delim);
char						*get_pid(t_shell **shell);
char						*find_var_spe(char *s, int index, t_shell **shell);
const char					*get_token_name(int type);
char						**init_env(char **envp);

// void	ft_lstclear_malloc(t_malloc *lst);

// ==============================================
// ================== SIGNALS ===================
// ==============================================

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

void						tokenize(char **input, t_tok **token, t_shell *shell);
t_tok						*ft_lstnew_tok(TOK_TYPE type, char *word, t_shell *shell);
// t_tok						*ft_lstnew_tok(TOK_TYPE type, char *word);
t_tok						*ft_lstlast_tok(t_tok *lst);
void						ft_lstadd_back_tok(t_tok **token, t_tok *new);
void						ft_lstclear_tok(t_tok *lst);

// ==============================================
// ================ EXECUTION ===================
// ==============================================

// === PIPE PROCESS ===

void						create_lst_exec(t_shell *shell);

// === LST EXEC ===

void						ft_lstadd_back_exec(t_exec **token, t_exec *new);
t_exec						*ft_lstlast_exec(t_exec *lst);
void						ft_lstclear_exec(t_exec *lst);

// === FREE_ALL ===

void						ft_free_all(t_shell *shell);
void						ft_lstclear_malloc(t_malloc *lst);
void						add_or_free(t_shell *shell, char *str, char **tab_str, int flag);
int						free_exit(t_shell *shell);


// === LST_MALLOC ===

void						ft_lstadd_back_malloc(t_malloc **token, t_malloc *new);
t_malloc					*ft_lstnew_malloc(char **tab_str, char *str, t_shell *shell);

// === PIPEX MODIF ===

typedef struct s_pipex
{
	char					**av;
	int						ac;
	char					**envp;
	pid_t					*child_tab;
	int						fd_infile;
	int						fd_outfile;
}							t_pipex;

int							pipex(t_shell *shell);

char						**ft_split_dif(char const *s, char c);

// int							here_doc_proc(char *delimiter);

int							exec_cmd(char **cmd, t_shell *shell);

// === HERE_DOC ===

int							loop_here_doc(char *delimiter, int *end);

// === TESTS ===

void						test_signals(t_signal signals, char **env);

int							expansion_len(char **token, t_shell **shell);
// === WORD PARSING ===

int							word_identification(t_shell **shell);

// === BUILT_IN ===
void						built_in(t_shell **shell, int *i);

#endif
