#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./libft/libft.h"

int main(int argc, char **argv, char **env)
{
	int i;
	char **split;

	if (argc != 2)
		return (printf("USE : ./exec $PATH"), 0);
	else
	{
		char *input = argv[1];
		while (*input)
		{
			i = 0;
			printf("%c", *input);
			if (*input == '$')
			{
				while (env[i])
				{
					split = ft_split(env[i], '=');
					printf("split: %s\n result: %s\n", split[0], split[1]);
					if (ft_strcmp(input + 1, split[0]) == 0)
						printf("%s", split[1]);
					i++;
				}
				printf("%d", i);
			}
			input++;
		}
	}

}
