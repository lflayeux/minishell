/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 20:20:21 by pandemonium       #+#    #+#             */
/*   Updated: 2025/07/10 17:32:03 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int is_valid_env(char *exec)
{
    int i = 0;

    if (!exec || (!ft_isalpha(exec[0]) && exec[0] != '_'))
        return (0);
    while (exec[i] && exec[i] != '=')
    {
        if (!ft_isalnum(exec[i]) && exec[i] != '_')
            return (0);
        i++;
    }
    return (1);
}
int ft_get_env(char **env, char *to_check)
{
    int i;

    i = 0;
    while (env[i])
    {
        if (ft_strncmp(env[i], to_check, ft_strlen(to_check)) == 0)
            return (1);
        i++;
    }
    return (0);
}
// ========================
// ======= UNSET ENV ======
// ========================
char    **unset_env(char *unset_env, char **env)
{
    char **new_env;
    char **split;
    int len;
    int i;
    int j;

    i = 0;
    j = 0;
    len = 0;
    while (env[len])
        len++;
    new_env = ft_calloc(len, sizeof(char *));
    if (new_env == NULL)
        return (NULL);
    while (env[i])
    {
        split = ft_split(env[i], '=');
        if (ft_strncmp(split[0], unset_env, ft_strlen(split[0])))
            new_env[j++] = ft_strdup(env[i]);
        ft_free_tab((void **)split);
        i++;
    }
    ft_free_tab((void **)env);
    return (new_env);
}

void expand_env(char **to_expand, t_shell *shell)
{
	t_expand	*expand;
    int i;

    i = 0;
	expand = malloc(sizeof(t_expand));
	expand->new = NULL;
	expand->quotes = 0;
	if (!expand)
		print_error("malloc", NULL, shell, GEN_ERR);
    while (to_expand[i])
    {
	    expand->word = to_expand[i];
	    expanded_one(expand, shell);
	    if (expand->new)
	    {
	    	free(expand->word);
	    	to_expand[i] = ft_strdup(expand->new);
	    	free(expand->new);
	    }
        i++;
    }
	free(expand);
}
char **put_env(t_shell *shell, char **env, char *cmd)
{
    int len;
    int j;
    char **new_env;

    len = 0;
    j = 0;
    while (env[len])
        len++;
    new_env = malloc((len + 2) * sizeof(char *));
    if (!new_env)
        return (NULL);
    while (env[j])
    {
        new_env[j] = ft_strdup(env[j]);
        j++;
    }
    new_env[j] = ft_strdup(cmd);
    new_env[j + 1] = NULL;
	expand_env(new_env, shell);
    ft_free_tab((void **)(env));
    return (new_env);
}
// ========================
// ======= RESET ENV ======
// ========================
char **set_env(char *split, char **env, char *cmd)
{
    int j;
    char **new_env;

    j = 0;
    new_env = init_env(env);
    if (!split[0] || !new_env)
        return (NULL);
    while (env[j])
    {
        if (ft_strncmp(env[j], split, ft_strlen(split)) == 0)
        {
            free(new_env[j]);
            new_env[j] = ft_strdup(cmd);
        }
        else
        {
            free(new_env[j]);
            new_env[j] = ft_strdup(env[j]);
        }
        j++;
    }
    ft_free_tab((void **)(env));
    return (new_env);
}