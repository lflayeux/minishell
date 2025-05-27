/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:34:14 by aherlaud          #+#    #+#             */
/*   Updated: 2025/05/27 14:56:18 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// INITIALISE LA STRUCTURE EN FONCTION DE LA PRECEDENTE SI ELLE EXISTE
void	exec_init(t_exec *node_exec)
{
	node_exec->cmd = NULL;
	node_exec->infile = NULL;
	node_exec->outfile = NULL;
	node_exec->delimiter = NULL;
	node_exec->if_infile = 0;
	node_exec->if_outfile = 0;
	node_exec->if_append = 0;
	node_exec->if_here_doc = 0;
	node_exec->pipe_to = NULL;
}

int	if_here_doc(t_exec *node_exec, t_tok **init)
{
	node_exec->delimiter = ((*init)->next)->word;
	node_exec->if_here_doc = 1;
	node_exec->if_infile = 0;
	(*init) = ((*init)->next);
	return (1);
}

int	if_append(t_exec *node_exec, t_tok **init)
{
	node_exec->outfile = ((*init)->next)->word;
	node_exec->if_append = 1;
	node_exec->if_outfile = 0;
	(*init) = ((*init)->next);
	return (1);
}

int	if_outfile(t_exec *node_exec, t_tok **init)
{
	int	temp_fd;

	temp_fd = open(((*init)->next)->word, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (temp_fd == -1)
		return (0);
	close(temp_fd);
	node_exec->outfile = ((*init)->next)->word;
	node_exec->if_outfile = 1;
	node_exec->if_append = 0;
	(*init) = ((*init)->next);
	return (1);
}

int	if_infile(t_exec *node_exec, t_tok **init)
{
	node_exec->infile = ((*init)->next)->word;
	node_exec->if_infile = 1;
	(*init) = ((*init)->next);
	return (1);
}

int	if_word(t_exec *node_exec, t_tok *init, t_tok *end, char **cmd)
{
	(void)node_exec;
	(void)end;
	if (!(*cmd))
		*cmd = ft_strdup("");
	else
		*cmd = ft_strjoin(*cmd, ft_strdup(" "));
	*cmd = ft_strjoin(*cmd, init->word);
	// if (!(init->next) || init->next == end)
	// {
	// if (*cmd)
	// 	node_exec->cmd = ft_split(*cmd, ' ');
	// else
	// 	node_exec->cmd = NULL;
	// }
	return (1);
}

// CREATE STRUCT AND JOIN&SPLIT COMMAND APPEND AND HERE_DOC MISSING
t_exec	*ft_lstnew_exec(t_tok *init, t_tok *end)
{
	t_exec	*node_exec;
	char	*cmd;

	cmd = NULL;
	node_exec = malloc(sizeof(t_exec));
	exec_init(node_exec);
	while (init && init != end)
	{
		if (init->type == WORD)
			if_word(node_exec, init, end, &cmd);
		if (init->type == INFILE && (init->next)->type == WORD && init->next)
			if_infile(node_exec, &init);
		if (init->type == OUTFILE && (init->next)->type == WORD && init->next)
			if_outfile(node_exec, &init);
		if (init->type == APPEND && (init->next)->type == WORD && init->next)
			if_append(node_exec, &init);
		if (init->type == HERE_DOC && (init->next)->type == WORD && init->next)
			if_here_doc(node_exec, &init);
		init = init->next;
	}
	if (cmd)
		node_exec->cmd = ft_split(cmd, ' ');
	else
		node_exec->cmd = NULL;
	return (node_exec);
}

int	error_management(t_tok **token)
{
	t_tok	*tmp_tok;

	// char	*tmp;
	tmp_tok = *token;
	while (tmp_tok)
	{
		if (tmp_tok->type != WORD && (tmp_tok->next)->type != WORD)
		{
			ft_printf("syntax error near unexpected token '%s'\n",
				get_token_name((tmp_tok->next)->type));
			handle_ctrl_c_interactive(SIGINT);
			return (0);
		}
		tmp_tok = tmp_tok->next;
	}
	return (1);
}

// CREATE THE LIST OF ALL EXEC TO MAKE
void	create_lst_exec(t_exec **lst_exec, t_tok **token)
{
	t_tok	*tmp_tok1;
	t_tok	*tmp_tok2;

	if (error_management(token) == 0)
		return ;
	tmp_tok1 = *token;
	tmp_tok2 = *token;
	while (tmp_tok1)
	{
		while (tmp_tok1 && tmp_tok1->type != PIPE)
			tmp_tok1 = tmp_tok1->next;
		ft_lstadd_back_exec(lst_exec, ft_lstnew_exec(tmp_tok2, tmp_tok1));
		if (tmp_tok1 && tmp_tok1->type == PIPE)
			tmp_tok1 = tmp_tok1->next;
		// printf("\t\t\t\t\t\t\tTEST\n");
		tmp_tok2 = tmp_tok1;
	}
}
