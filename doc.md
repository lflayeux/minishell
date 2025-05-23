
# 🧠 Minishell - Notes de Développement
---
## ✅ TODO


- [ ] `echo -n`       
- [ ] `cd`
- [x] `pwd`
- [ ] `export`
- [ ] `unset`
- [ ] `env`
- [x] `exit`
---
## ✅ Tokenisation

### Règles de tokenisation

2. Si `<`, `>`, `<<`, `>>` → redirection
3. Si `|` → pipe
4. Si `word` :
   - Vérifier : `$?`, `$$`, `$PATH`. '\'', ""

PIPE = 0
INFILE = 1
OUTFILE = 2
HERE_DOC = 3
APPEND = 4
WORD = 5

<<
<
>>
>
---
## ✅ Parsing

### Objectif

Trier chaque commande en :
- `infile`
- `cmd`
- `args`
- `outfile`
- `pipe`

### Logique

- Utiliser une liste chaînée.
- Tant qu’il n’y a pas de `pipe`, construire un bloc de commande.

---

## ✅ Structures

### `enum TYPE_OF_TOKEN`
```c
enum TYPE_OF_TOKEN
{
    // À définir : WORD, REDIR_IN, REDIR_OUT, PIPE, etc.
};

==> dhieuh$PATHde"dedede$PATH'deded'"'$PATH'


## ✅ Execution

liste chainee de maillons tels que :
typedef struct s_exec_pipeline
{
	char					**cmd;
	char					*infile;
	char					*outfile;
	bool					if_infile;
	bool					if_outfile;
	struct s_exec_pipeline	*pipe_to;
}							t_exec;

chaque maillon sera un enfant a creer + une exec de cmd + un dup2 si if_infile = 1 + un dup2 si if_infile = 1

exemple main avec : < Makefile ls -l | cat > out

exec num 0
        command:
                cmd num 0: ls
                cmd num 1: -l
        infile:1,   Makefile
        outfile:0,   (null)
exec num 1
        command:
                cmd num 0: cat
        infile:1,   Makefile
        outfile:1,   out


```
---
---
### ===>        PB A CORRIGER: 
---

```bash
# Prompt simulé : 🦾 miniboss 🦾 >
< Makefile | cat -e
[1]    805462 segmentation fault (core dumped)  ./minishell  # create_lst_exec
```