/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:33:18 by lflayeux          #+#    #+#             */
/*   Updated: 2025/05/28 14:59:59 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// ==================
// ======= PWD ======
// ==================

void    exec_pwd()
{
    char *path;
    path = getcwd(NULL, 0);
    printf(YLW"%s\n"RST, path);
    free(path);
}
// ==================
// ======= CD =======
// ==================

void    exec_cd(char *path)
{
    char    *join;

    if (path[0] == '~')
    {
        join = ft_strjoin(getenv("HOME"), path + 1);
        printf("%s\n", join);
        chdir(join);
    }
    else
        chdir(path);
    exec_pwd();
}
// ==================
// ======= ECHO =====
// ==================

void exec_echo(t_exec *exec, int *i)
{
    int newline;
    int j;

    (*i)++;
    newline = 1;
    while (exec->cmd[*i])
    {
        if (ft_strncmp(exec->cmd[*i], "-n", 2) == 0)
        {
            j = 2;
            while (exec->cmd[*i][j] == 'n')
                j++;
            if (exec->cmd[*i][j] == '\0')
            {
                newline = 0;
                (*i)++;
                continue;
            }
        }
        break;
    }
    while (exec->cmd[*i])
    {
        printf("%s", exec->cmd[*i]);
        if (exec->cmd[*i + 1])
            printf(" ");
        (*i)++;
    }
    if (newline)
        printf("\n");
}
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

// // ========================
// // ======= UNSET ENV ======
// // ========================
// void    unset_env(char ***env, char *unset_env)
// {
//     char **new_env;
//     int len;
//     int i;

//     i = 0;
//     len = 0;
//     while ((*env)[len])
//         len++;
//     new_env = ft_calloc(len + 1, sizeof(char *));
//     if (new_env == NULL)
//         return ;
//     while (env[i])
//     {
//         if (ft_strncmp((*env)[i], unset_env, ft_strlen(unset_env)) == 0)
//             i++;
//         new_env[i] = ft_strdup((*env)[i]);
//         i++;
//     }
//     ft_free_tab((void **)(*env));
//     *env = new_env;
// }

// void    exec_unset(t_exec	**exec, int *i, char ***env)
// {
//     char **split;

//     while ((*exec)->cmd[*i + 1])
//     {
//         if (!is_valid_env((*exec)->cmd[*i + 1]))
//         {
//             printf("INVALID ENV: %s\n", (*exec)->cmd[*i + 1]);
//             return ;
//         }
//         split = ft_split((*exec)->cmd[*i + 1], '=');
//         if (!getenv(split[0]))
//             return ;
//         else
//             unset_env(env, (*exec)->cmd[*i + 1]);
//         (*i)++;
//     }
// }

// // ========================
// // ======= SET NEW ENV ======
// // ========================


char **put_env(t_shell **shell, int *i, char **env)
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
    new_env[j] = ft_strdup((*shell)->exec->cmd[*i + 1]);
    new_env[j + 1] = NULL;
    ft_free_tab((void **)(env));
    return (new_env);
}
// ========================
// ======= RESET ENV ======
// ========================
char **set_env(t_shell **shell, int *i, char *split, char **env)
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
            new_env[j] = ft_strdup((*shell)->exec->cmd[*i + 1]);
        }
        else
            new_env[j] = ft_strdup(env[j]);
        j++;
    }
    ft_free_tab((void **)(env));
    return (new_env);
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

void stock_export(t_shell **shell, int *i)
{
    char **split;

    if (ft_strchr((*shell)->exec->cmd[*i + 1], '=') != 0)
    {
        split = ft_split((*shell)->exec->cmd[*i + 1], '=');
        if (ft_get_env((*shell)->env, split[0]))
            (*shell)->secret = set_env(shell, i, split[0], (*shell)->secret);
        else
            (*shell)->secret = put_env(shell, i, (*shell)->secret);
        ft_free_tab((void **)split);
    }
    else
    {
        if (ft_get_env((*shell)->env, (*shell)->exec->cmd[*i + 1]))
            (*shell)->env = set_env(shell, i, (*shell)->exec->cmd[*i + 1], (*shell)->env);
        else
            (*shell)->env = put_env(shell, i,(*shell)->env);
    }
}
void    exec_export(t_shell	**shell, int *i)
{
    int j;

    j = 0;
    if (!(*shell)->exec->cmd[*i + 1])
    {
        while ((*shell)->secret[j])
            printf("declare -x \"%s\"\n", (*shell)->secret[j++]);
        ft_free_tab((void **)(*shell)->env);
        (*shell)->env = init_env((*shell)->secret);
    }
    while ((*shell)->exec->cmd[*i + 1])
    {
        if (!is_valid_env((*shell)->exec->cmd[*i + 1]))
            printf("INVALID ENV: %s\n",(*shell)->exec->cmd[*i + 1]);
        else
            stock_export(shell, i);
        (*i)++;
    }
 }


// POUR EXPORT SI PAS DE = ON EXPORT A PART
void    check_env(t_shell **shell, int *i)
{
    char **split;

    split = ft_split((*shell)->exec->cmd[*i + 1], '=');
    if (!split)
        return ;
    if (ft_get_env((*shell)->env, split[0]) == 1)
    {
        (*shell)->env = set_env(shell, i, split[0], (*shell)->env);
        ft_free_tab((void **)split);
        return ;
    }
    (*shell)->env = put_env(shell, i, (*shell)->env);
    ft_free_tab((void **)split);
}
// si env sans rien -> printf env
// si env avec var= -> add ou remplace var puis printf var
// sinn rien faire
void exec_env(t_shell **shell, int *i)
{
    int j;

    while ((*shell)->exec->cmd[*i + 1])
    {
        if (ft_strchr((*shell)->exec->cmd[*i + 1], '='))
                check_env(shell, i);
        else
            break;
        (*i)++;
    }
    j = 0;
    while ((*shell)->env[j])
    {
        printf("%s\n", (*shell)->env[j]);
        j++;
    }
    (*i)++;
}

void    built_in(t_shell **shell, int *i)
{
    if (!(ft_strcmp((*shell)->exec->cmd[*i], "echo")))
        exec_echo((*shell)->exec, i);
    else if (ft_strcmp((*shell)->exec->cmd[*i], "cd") == 0)
         exec_cd((*shell)->exec->cmd[++(*i)]);
    else if (ft_strcmp((*shell)->exec->cmd[*i], "pwd") == 0)
        exec_pwd();
    else if (ft_strcmp((*shell)->exec->cmd[*i], "env") == 0)
        exec_env(shell, i);
    else if (ft_strcmp((*shell)->exec->cmd[*i], "export") == 0)
        exec_export(shell, i);
//    else if (ft_strcmp((*shell)->exec->cmd[*i], "unset") == 0)
//        exec_unset((*shell)->exec, i, (*shell)->env);
    else
        return ;
}
