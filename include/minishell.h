/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:17:39 by lflayeux          #+#    #+#             */
/*   Updated: 2025/06/03 11:48:55 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// ==============================================
// ================== LIBRARIES =================
// ==============================================

# include "../libft/libft.h"
# include "struct.h" 
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
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

char	**init_env(char **envp);

char	**init_env(char **envp);
void	init_shell(t_shell **shell, char **envp);
// ==========TEST=============
const char	*get_token_name(int type);
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

t_tok						*ft_lstnew_tok(TOK_TYPE type, char *word, t_shell *shell);
void						tokenize(char **input, t_tok **token, t_shell *shell);
void						ft_lstadd_back_tok(t_tok **token, t_tok *new);
void						ft_lstclear_tok(t_tok *lst);

// ==============================================
// ================ EXPANSION ===================
// ==============================================


char	*get_pid(t_shell **shell);
int	expansion_len(char **token, t_shell **shell);
int	word_identification(t_shell **shell);
char	*find_var_spe(char *s, int index, t_shell **shell);
int	ft_isdelim(char c, char *delim);
int	add_dollar_env(char **word, char **new_word, int *i, int *j, t_shell **shell);

// ==============================================
// ================ BUILT_IN ===================
// ==============================================

void    exec_export(t_shell	**shell, int *i);
void exec_env(t_shell **shell, int *i);
void    exec_unset(t_shell **shell, int *i);
char    **unset_env(char *unset_env, char **env);
char **put_env(t_shell **shell, int *i, char **env);
char **set_env(t_shell **shell, int *i, char *split, char **env);
int ft_get_env(char **env, char *to_check);
int is_valid_env(char *exec);

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
