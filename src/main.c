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

void	word_check_token(char **word, char **input)
{
	int		i;

	i = 0;
	while (**input != '\0')
	{
		while (**input != ' ' && **input != '>' && **input != '<' &&
			**input != '|' && **input != '\'' && **input != '"' &&
			**input != '\0')
				(*word)[i++] = *(*input)++;
		if (**input == '\'')
		{
				(*word)[i++] = *(*input)++;
				while (**input != '\'' && **input != '\0')
						(*word)[i++] = *(*input)++;
		}
		else if (**input == '"')
		{
				(*word)[i++] = *(*input)++;
				while (**input != '"' && **input != '\0')
						(*word)[i++] = *(*input)++;
		}
		else if (**input == ' ' || **input == '>' || **input == '<' || **input == '|' || **input == '\0')
			break ;
		(*word)[i++] = *(*input)++;
	}
}

// AJOUTE UN MAILLON AVEC QUOTE ADEQUAT SI NECESSAIRE
void	word_token(char **input, t_tok **token)
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
	word_check_token(&word, input);
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
void    tokenize(char **input, t_tok **token)
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
		word_token(input, token);
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
    	tokenize(&input, &token);
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
