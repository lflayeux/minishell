/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:19:08 by lflayeux          #+#    #+#             */
/*   Updated: 2025/05/07 15:56:18 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
// ==============================================
// ================= TEST DOLLAR ================
// ==============================================
int	ft_isdelim(char c, char *delim)
{
	int	i;

	i = 0;
	while (delim[i])
	{
		if (delim[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*find_var(char *s, int index)
{
	int		i;
	char	*var;
	int		len;

	len = 0;
	while (s[index + len])
	{
		if (ft_isdelim(s[index + len], "|<> \'\"") == 1)
			break ;
		len++;
	}
	var = malloc((len + 1) * sizeof(char));
	if (!var)
		return (NULL);
	i = 0;
	while (s[index])
	{
		if (ft_isdelim(s[index], "|<> \'\"") == 1)
			break ;
		var[i++] = s[index++];
	}
	return (var);
}

int	wordlen_var_env(char **envp, char *var_env)
{
	int		i;
	size_t	len;
	char	*var_str;
	char	*full_var;

	full_var = ft_strjoin(var_env, "=");
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(full_var, envp[i], ft_strlen(full_var)) == 0)
			break ;
		i++;
	}
	len = ft_strlen(envp[i]);
	var_str = ft_substr(envp[i], ft_strlen(full_var), len
			- ft_strlen(full_var));
	if (!var_str)
		return (0);
	return (ft_strlen(var_str));
}

int	wordlen_quotes(char *s, int index, char **envp)
{
	int		len;
	int i;
	char	temp;
	char	*var_env;

	len = 0;
	temp = s[index++];
	i = 0;
	while (s[index + i] && s[index + i] != temp)
	{
		if (temp == '"' && s[index + i] == '$')
		{
			i++;
			var_env = find_var(s, index + i);
			i += ft_strlen(var_env);
			len += wordlen_var_env(envp, var_env);
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

// here check j when quotes with $ bad movement
int		ft_wordlen(char *s, char *delim, char **envp)
{
	int	i;
	int	j;
	int	len;

	j = 0;
	while (ft_isdelim(s[j], delim) == 1)
		j++;
	len = 0;
	while (s[j])
	{
		if (s[j] == '\'' || s[j] == '\"')
		{
			len += wordlen_quotes(s, j, envp);
			j += wordlen_quotes(s, j, envp) + 1;
		}
		else
		{
			i = 0;
			while (delim[i])
			{
				if (s[j] == delim[i])
					return (len);
				i++;
			}
			len++;
		}
		j++;

	}
	return (len);
}

void	dollar_behavior(char **prompt, char **word, int *i, char **envp)
{
	int		l;
	char	*var_env;
	char	*var_str;
	char	*full_var;

	(*prompt)++;
	var_env = find_var(*prompt, 0);
	(*prompt) = (*prompt) + ft_strlen(var_env);
	full_var = ft_strjoin(var_env, "=");
	l = 0;
	while (envp[l] != NULL)
	{
		if (ft_strncmp(full_var, envp[l], ft_strlen(full_var)) == 0)
			break ;
		l++;
	}
	if (!(envp[l]))
		return ;
	var_str = ft_substr(envp[l], ft_strlen(full_var), ft_strlen(envp[l])
			- ft_strlen(full_var));
	l = 0;
	while(var_str[l])
		(*word)[(*i)++] = var_str[l++]; 
	return (free(var_env), free(full_var));
}
*/

// ==============================================
// ================= LST_TOKEN ==================
// ==============================================

// CREER UN NVEAU MAILLON
t_tok	*ft_lstnew_tok(TOK_TYPE type, char *word)
{
	t_tok	*new;

	new = malloc(sizeof(t_tok));
	if (new == NULL)
		return (0);
	new->type = type;
	new->word = word;
	new->next = NULL;
	return (new);
}

t_tok	*ft_lstlast_tok(t_tok *lst)
{
	if (!lst)
		return (0);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

// AJOUTE LE NVEAU MAILLON A LA FIN DE LA LISTE
void	ft_lstadd_back_tok(t_tok **token, t_tok *new)
{
	t_tok	*last;

	if (token == NULL)
		return ;
	if (*token == NULL)
	{
		*token = new;
		return ;
	}
	last = ft_lstlast_tok(*token);
	last->next = new;
}


// ==============================================
// =============== TOKENISATION =================
// ==============================================

void	check_quotes(char **input, t_quotes *quotes)
{
	if (**input == '\'' && quotes->s_quotes == false)
		quotes->s_quotes = true;
	else if (**input == '"' && quotes->d_quotes == false)
		quotes->d_quotes = true;
	else if (**input == '\'' && quotes->s_quotes == true)
		quotes->s_quotes = false;
	else if (**input == '"' && quotes->s_quotes == true)
		quotes->s_quotes = false;
}

void	word_check_token(char **word, char **input, char **env)
{
	int		i;
	t_quotes	quotes;

	(void)env;
	quotes.s_quotes = false;
	quotes.d_quotes = false;
	i = 0;
	while (**input != '\0')
	{
		check_quotes(input, &quotes);
		if ((**input == ' ' || **input == '>' || **input == '<' ||
			**input == '|' || **input == '\0') && quotes.s_quotes == false &&
			quotes.d_quotes == false)
				break;
//		if (**input == '$' && (quotes.d_quotes == true ||
//			(quotes.d_quotes == false && quotes.s_quotes == false)))
//			dollar_behavior(input, word, &i, env);
//		if ((*word)[i + 1] != '\0' && *(*input) + 1 != '\0')
		(*word)[i++] = *(*input)++;
	}
}

// AJOUTE UN MAILLON AVEC QUOTE ADEQUAT SI NECESSAIRE
void	word_token(char **input, t_tok **token, char **env)
{
	char	*word;
	int		len;

	len = 0;
	while ((*input)[len] != ' ' && (*input)[len] != '>' && (*input)[len] != '<' && (*input)[len] != '|' && (*input)[len] != '\0')
		len++;
	word = ft_calloc(len + 1, sizeof(char));
// TROUVER LA RETOUR A METTRE
	if (word == NULL)
		return ;
	word_check_token(&word, input, env);
	ft_lstadd_back_tok(token, ft_lstnew_tok(WORD, word));
}

// AJOUTE UN MAILLON AVEC REDIREC ADEQUAT
void	redir_token(char **input, t_tok **token, char redir)
{
	if ((*input)[1] && (*input)[1] == redir)
	{
		if (redir == '<')
			ft_lstadd_back_tok(token, ft_lstnew_tok(HERE_DOC, NULL));
		else
			ft_lstadd_back_tok(token, ft_lstnew_tok(APPEND, NULL));
		(*input)++;
	}
	else
	{
		if (redir == '<')
			ft_lstadd_back_tok(token, ft_lstnew_tok(INFILE, NULL));
		else
			ft_lstadd_back_tok(token, ft_lstnew_tok(OUTFILE, NULL));
	}
	(*input)++;
}

// CREER LA LISTE CHAINEE AVEC LE BON TYPE DE TOKEN
void    tokenize(char **input, t_tok **token, char **env)
{
	while (**input == ' ' && **input != '\0')
		(*input)++;
	if (**input == '|')
	{
		ft_lstadd_back_tok(token, ft_lstnew_tok(PIPE, NULL));
		(*input)++;
	}
	else if (**input == '<')
		redir_token(input, token, '<');
	else if (**input == '>')
		redir_token(input, token, '>');
	else
		word_token(input, token, env);
}
// ==============================================
// =================== TESTS ====================
// ==============================================

const char *get_token_name(int type)
{
	if (type == 0)
		return ("|");
	if (type == 1)
		return ("<");
	if (type == 2)
		return (">");
	if (type == 3)
		return ("<<");
	if (type == 4)
		return (">>");
	if (type == 5)
		return ("WORD");
	return ("error");
}

// ==============================================
// ================= FIN TESTS ==================
// ==============================================
void    execute_input(char *input, char **env)
{
    t_tok *token;

	(void)env;
	token = NULL;
	while (*input != '\0')
	{
    	tokenize(&input, &token, env);
	}
	//pour test
	int i;
    t_tok *tmp = token;
	i = 0;
	while (tmp != NULL)
	{
		printf("token num %d\n", i++);
		printf("\ttype: %s\n", get_token_name(tmp->type));
		printf("\tword: %s\n", tmp->word);
		tmp = tmp->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	char *input;
	t_signal	signals;

	(void)argc;
	(void)argv;
	(void)env;
	set_signal(&signals);
	while (1)
	{
		input = readline(PROMPT);
		if (input == NULL || ft_strcmp(input, "exit") == 0)
			return (printf("exit"),0);
		if (*input)
		{
			add_history(input);
//			test_signals(signals, env);
            execute_input(input, env);
		}
		reset_signals(&signals);
	}
}
// ==============================================
// =================== TESTS ====================
// ==============================================

void	test_signals(t_signal signals, char **env)
{
	pid_t	pid;
	char *caca[] = {"../fdfdemerde/fdf", "../test_fdf/test_maps/julia.fdf", NULL};
	int	status;
//	char *caca[] = {"/bin/bash", NULL};

	pid = fork();
	if (pid == 0)
	{
		child_signals(&signals);
		execve(caca[0], caca, env);
	}
	else
	{
		parent_signals(&signals);
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
		{
			if (WCOREDUMP(status))
				printf("Core dump fdp\n");
		}
		status = 0;
	}
}
