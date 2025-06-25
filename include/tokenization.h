/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 18:10:25 by lflayeux          #+#    #+#             */
/*   Updated: 2025/06/25 12:23:29 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZATION_H
# define TOKENIZATION_H

# include "struct.h"

// ==============================================
// =================== TOKENS ===================
// ==============================================

# define NEW_TOK ft_lstnew_tok
# define ADD_TOK ft_lstadd_back_tok

/**
 * @brief Creates a new token node.
 *
 * @param type The type of the token.
 * @param word The string value of the token.
 * @param shell Pointer to the shell context (used for error handling).
 * @return Pointer to the newly created token node, or NULL on failure.
 */
t_tok	*ft_lstnew_tok(TOK_TYPE type, char *word, t_shell *shell);
/**
 * @brief Returns the last node of a token list.
 *
 * @param lst Pointer to the head of the token list.
 * @return Pointer to the last token in the list, or NULL if the list is empty.
 */
t_tok	*ft_lstlast_tok(t_tok *lst);
/**
 * @brief Adds a new token node at the end of the list.
 *
 * @param token Address of the pointer to the first element of the list.
 * @param new Pointer to the new token node to add.
 */
void	ft_lstadd_back_tok(t_tok **token, t_tok *new);
/**
 * @brief Frees all nodes in a token list and their associated memory.
 *
 * @param lst Pointer to the head of the token list.
 */
void	ft_lstclear_tok(t_tok *lst);
/**

	* @brief Analyse un symbole de redirection ou de pipe et l'ajoute à la liste de tokens.
 *
 * @param input Chaîne d'entrée à partir du caractère courant.
 * @param shell Structure principale contenant la liste de tokens.
 * @return Nombre de caractères consommés (1 ou 2 selon le symbole).
 */
int		symbol_token(char *input, t_shell *shell);
/**
 * @brief Analyse un mot (séquence non symbolique) et l'ajoute comme token.
 *
 * @param input Chaîne d'entrée à partir du caractère courant.
 * @param shell Structure contenant la liste de tokens.
 * @return Longueur du mot consommé.
 */
int		word_token(char *input, t_shell *shell);
/**
 * @brief Tokenise toute l'entrée utilisateur en séparant les mots,
	espaces et symboles.
 *
 * @param shell Structure principale contenant l'entrée et la liste de tokens.
 */
int		tokenize(t_shell *shell);
/**

	* @brief Extrait un mot depuis l'entrée (gère les quotes) et l'ajoute comme token.
 *
 * @param input Chaîne d'entrée à partir du caractère courant.
 * @param shell Structure contenant la liste de tokens.
 * @param word Pointeur vers la mémoire allouée pour contenir le mot.
 */
void	add_word_tok(char *input, t_shell *shell, char *word);
/**
 * @brief Calcule la longueur d’un mot à tokeniser (gère les quotes).
 *
 * @param input Chaîne d’entrée à partir du caractère courant.
 * @return Longueur du mot jusqu'à un espace ou un symbole hors quote.
 */
int		len_word_tok(char *input);
/**
 * @brief Vérifie si un caractère est un symbole de shell (`<`, `>`, `|`).
 *
 * @param c Caractère à tester.
 * @return 1 si c'est un symbole, 0 sinon.
 */
int		is_symbol(char c);
/**

	* @brief Vérifie si un caractère est un espace ou un séparateur de type `isspace()`.
 *
 * @param c Caractère à tester.
 * @return 1 si c'est un caractère d'espacement, 0 sinon.
 */
int		is_space(char c);

#endif