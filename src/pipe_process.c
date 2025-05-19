/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:34:14 by aherlaud          #+#    #+#             */
/*   Updated: 2025/05/19 17:14:43 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

add_str_tab(char **cmd)
{
}

void	fill_struct(t_tok *init, t_tok *end)
{
	t_exec	*node_exec;

	while (init != end)
	{
		while ()
			if (init->word)
				ft_lstadd_back_exec(lst_exec, node_exec);
	}
}

void	create_lst_exec(t_exec **lst_exec, t_tok **token)
{
	t_tok	*tmp_tok1;
	t_tok	*tmp_tok2;

	tmp_tok1 = *token;
	tmp_tok2 = *token;
	while (tmp_tok1)
	{
		while (tmp_tok1->type != PIPE)
			tmp_tok1 = tmp_tok1->next;
		fill_struct(tmp_tok2, tmp_tok1);
		tmp_tok2 = tmp_tok1;
		if (tmp_tok1->type == PIPE)
			tmp_tok1 = tmp_tok1->next;
	}
}
