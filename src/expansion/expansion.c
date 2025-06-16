	/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandemonium <pandemonium@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 18:07:12 by lflayeux          #+#    #+#             */
/*   Updated: 2025/06/07 18:42:01 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	quotes_expand(t_expand *expand, char sep, t_shell *shell);

void	ft_getenv(char **env, char *word, t_expand *expand, t_shell *shell)
{
	int		i = 0;
	int		len = 0;

	if (!env || !shell)
		return ;
	while (ft_isalnum(word[len]) || word[len] == '_')
	{
		len++;
	shell->var = ft_calloc((len + 1), sizeof(char));
	if (!shell->var)
        print_error(shell, MALLOC);
	i = 0;
	while (word[i] && (ft_isalnum(word[len]) || word[len] == '_'))
		shell->var[j++] = word[i++];
}
char	*ft_getenv(char **env, t_shell *shell)
{
	int	i;
	int	len;

	i = 0;
	if (!env || !shell || !shell->var)
		return (NULL);

	len = ft_strlen(shell->var);
	while (env[i])
	{
		if (!ft_strncmp(env[i], word, len) && env[i][len] == '=')
		{
			shell->var = ft_strdup(&env[i][len + 1]);
			if (!shell->var)
				print_error(shell, MALLOC);
		}
		i++;
	}
	return (NULL);
}


int	handle_env_var(const char *word, int *i, t_shell *shell)
{
	char	*val;
	int		start = *i + 1;

	find_var_spe((char *)&word[start], shell);
	*i += ft_strlen(shell->var);

	val = ft_getenv(shell->env, shell);
	if (val)
		return ft_strlen(val);
	return 0;
}

int	len_dollar(char *word, int *i, t_shell *shell)
{
	int	len;
	
	len = 0;
	if (word[*i] == '$' && word[*i + 1] == '$')
	{
		*i += 2;
		len += ft_strlen(shell->pid);
	}
	else if (word[*i] == '$' && word[*i + 1] == '?')
	{
		*i += 2;
		len += ft_intlen(shell->error);
	}
	else if (word[*i] == '$' && (ft_isalnum(word[*i + 1]) || word[*i + 1] == '_'))
			len += handle_env_var(word, i, shell);
	else
	{
		(*i)++;
		len++;
	}
	return (len);
}


void	expand_len(t_tok *tok, t_shell *shell)
{
	int i;
	int	len;
	
	len = 0;
	i = 0;
	while (tok->word[i])
	{
		if (tok->word[i] == '$' && quotes != 1)
				len += len_dollar(tok->word, &i,shell);
		else if (tok->word[i] == '\'' && tok->word[i] == '"')
				quotes = 1;
		else
		{
			i++;
			len++;
		}
	}
	printf("new_len : %d\n", len);
}

void	expand(t_shell *shell)
{
	t_tok		*tmp;
	t_expand	*expand;

	tmp = shell->tok;
	expand = malloc(sizeof(t_expand));
	expand->new = NULL;
	expand->quotes = 0;
	if (!expand)
		print_error(shell, MALLOC);
	while (tmp)
	{
		expand_len(tmp, shell);
		tmp = tmp->next;
	}
}
