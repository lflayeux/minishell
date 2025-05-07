# 🧠 Minishell - Notes de Développement

## ✅ Tokenisation

### Règles de tokenisation

1. Si `quotes` → `WORD` + `true`
2. Si `<`, `>`, `<<`, `>>` → redirection
3. Si `|` → pipe
4. Si `word` :
   - Vérifier : `$?`, `$$`, `$PATH`

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

