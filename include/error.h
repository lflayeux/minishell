/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandemonium <pandemonium@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 18:02:54 by lflayeux          #+#    #+#             */
/*   Updated: 2025/07/10 23:56:20 by pandemonium      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <errno.h>
struct s_shell;

# define SUCCESS 0
# define GEN_ERR 1
# define BUILTIN_ERROR 2
# define CMD_EXEC 126
# define N_FOUND 127
# define EXIT_ARG 128
# define CTRL_C 130
# define CTRL_D 137

# define N_CMD_MESS "command not found"
# define FILE_MESS "No such file or directory"
# define PARSE_MESS "syntax error near unexpected token"
# define N_DIR "Not a directory"
# define PERM	"Permissions denied"
# define ID "not a valid identifier"

typedef enum e_error_type
{
	MALLOC,
	SYNTAX_PIPE,
	SYNTAX_END,
	OPEN,
}		ERROR_TYPE;

void	print_error(char *s1, char *s2, t_shell *shell, int type);
t_tok	*parse_error(t_shell *shell);

#endif