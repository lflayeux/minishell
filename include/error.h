/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 18:02:54 by lflayeux          #+#    #+#             */
/*   Updated: 2025/06/20 16:41:13 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <errno.h>
struct s_shell;

# define SUCCESS		0
# define GEN_ERROR		1
# define BUILTIN_ERROR	2
# define CMD_EXEC		126
# define CMD_N_FOUND	127
# define EXIT_ARG		128
# define CTRL_C			130
# define CTRL_D			137


# define N_CMD_MESS		"command not found"
# define FILE_MESS		"No such file or directory"
# define PARSE_MESS		"syntax error near unexpected token"

typedef enum e_error_type
{
	MALLOC,
	SYNTAX_PIPE,
	SYNTAX_END,
	OPEN,
}							ERROR_TYPE;

void    print_error(char *s1, char *s2, t_shell *shell, int type);
int     parse_error(t_shell *shell);

#endif