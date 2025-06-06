#!/bin/bash

FILE="tester/dico_cmd.txt"


# strings "$FILE" | while IFS= read -r line; do
#     echo $line >> "Found string: $line"

# rm -f out_bash.txt
# rm -f out_token.txt


#   # 1) Escape any “<” “>” or “|” so that Bash won’t treat them as operators
#     safe="${line//</\\<}"
#     safe="${safe//>/\\>}"
#     safe="${safe//|/\\|}"

#     # 2) Perform only variable expansion (including $$, $PATH, etc.)
#     #    but NOT real redirections, by using printf via eval.
#     expanded=$(bash -c 'eval "printf \"%s\" '"$safe"'"' 2>/dev/null)

#     # 3) Un-escape the metacharacters so they reappear literally
#     expanded="${expanded//\\</<}"
#     expanded="${expanded//\\>/>}"
#     expanded="${expanded//\\|/|}"

#     # 4) Now split on bash‐like quoting rules—without ever doing I/O—
#     #    by calling Python’s shlex.split() on the fully‐expanded string.
#     python3 - <<PYCODE >> out_bash.txt
# import shlex, sys
# text = sys.stdin.read().rstrip("\n")
# for tok in shlex.split(text):
#     print(tok)
# PYCODE <<EOF
# $expanded
# EOF


# # TOKENISATION CHECK
# cat <<EOF > temp_2.c
# #include "include/minishell.h"

# int	main(int ac, char **av, char **envp)
# {
#     int i;
#     char *line;
#     t_shell *shell;
#     t_tok *tmp;

#     shell = malloc(sizeof(t_shell));
# 	init_shell(&shell, envp);

#     i = 1;
#     (void)ac;
#     line = "";
#     while(av[i])
#     {
#         line = ft_strjoin(line, av[i]);
#         if(av[i + 1])
#             line = ft_strjoin(line, " ");
#         i++;
#     }
#     while (*line != '\0')
# 	{
# 		tokenize(&line, &(shell->tok), shell);
# 	}
#     word_identification(&shell);
#     tmp = shell->tok;
#     while(tmp)
#     {
#         if(tmp->type == WORD)
#             printf("%s\n", tmp->word);
#         else
#             printf("%s\n", get_token_name(tmp->type));
#         tmp = tmp->next;
#     }
# }
# EOF

# mkdir include_tmp src_tmp
# cp include/*.h include_tmp/
# cp libft/*.h include_tmp/
# cp src/tokenization/*.c src/*.c src/lst/*.c src/expansion/*.c libft/*.c src/signals/*.c pipex_modif/*.c src_tmp/
# # Après avoir copié les .c dans src_tmp/
# find src_tmp/ -type f -name '*.c' -exec sed -i 's|#include "../../include/minishell.h"|#include "../include_tmp/minishell.h"|' {} +
# find src_tmp/ -type f -name '*.c' -exec sed -i 's|#include "libft.h"|#include "../include_tmp/libft.h"|' {} +
# gcc temp_2.c src_tmp/*.c -Isrc_tmp -lreadline -lncurses -o temp_prog_2
# ./temp_prog_2 $line >> out_token.txt
# rm -f temp_2.c temp_prog_2
# rm -rf include_tmp src_tmp


# if cmp -s out_token.txt out_bash.txt; then
#     echo "${GREEN}For ${RESET}$line ${GREEN}Files are identical ✅ ${RESET}"
# else
#     echo "${RED}For ${RESET}$line ${RED}Files differ ❌ ${RESET}"
#     strings out_bash.txt
#     strings out_token.txt
#     break
# fi

# > out_bash.txt > out_token.txt

# Define colors (no spaces around '=')
GREEN='\033[0;32m'
RED='\033[0;31m'
RESET='\033[0m'

strings -n1 "$FILE" | while IFS= read -r line; do
    # echo "$line"


cat <<EOF > temp_2.c
#include "include/minishell.h"

int	main(int ac, char **av, char **envp)
{
    int i;
    char *line;
    t_shell *shell;
    t_tok *tmp;

    shell = malloc(sizeof(t_shell));
	init_shell(&shell, envp);

    i = 1;
    (void)ac;
    line = "";
    while(av[i])
    {
        line = ft_strjoin(line, av[i]);
        if(av[i + 1])
            line = ft_strjoin(line, " ");
        i++;
    }
    while (*line != '\0')
	{
		tokenize(&line, &(shell->tok), shell);
	}
    word_identification(&shell);
    create_lst_exec(shell);
    pipex(shell);
}
EOF

mkdir include_tmp src_tmp
cp include/*.h include_tmp/
cp libft/*.h include_tmp/
cp src/tokenization/*.c src/*.c src/lst/*.c src/expansion/*.c libft/*.c src/signals/*.c pipex_modif/*.c src_tmp/
# Après avoir copié les .c dans src_tmp/
find src_tmp/ -type f -name '*.c' -exec sed -i 's|#include "../../include/minishell.h"|#include "../include_tmp/minishell.h"|' {} +
find src_tmp/ -type f -name '*.c' -exec sed -i 's|#include "libft.h"|#include "../include_tmp/libft.h"|' {} +
gcc temp_2.c src_tmp/*.c -Isrc_tmp -lreadline -lncurses -o temp_prog_2
if [[ "$line" == *">"* ]]; then
    ./temp_prog_2 "$line"
else
    ./temp_prog_2 "$line" > out1.txt
fi


# EXEC RESULT CHECK
if [[ "$line" == *">"* ]]; then
    eval "$line"
else
    eval "$line" > out2.txt 
fi


rm -f temp_2.c temp_prog_2
rm -rf include_tmp src_tmp

if cmp -s out1.txt out2.txt; then
    echo -e "${GREEN}For ${RESET}$line ${GREEN}Files are identical ✅ ${RESET}"
else
    echo -e "${RED}For ${RESET}$line ${RED}Files differ ❌ ${RESET}"
    break
fi

done