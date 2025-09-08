#include <stdlib.h>
#include <stdio.h>
#include "config.h"
#include "token.h"

#define UNCLOSED_QUOTE	-1

t_token_type	lex(char **token_value, char *str, size_t *ip);

int main(int ac, char *av[])
{
	if (ac != 2)
		return (printf("need one arg\n"), 1);
	int result;
	char *value;
	size_t i = 0;
	while (1)
	{
		result = lex(&value, av[1], &i);
		if (result == T_NULL || result == T_ERROR)
			return (printf("end: %d\n", result), 0);
		printf("type: %d, value: %s\n", result, value);
	}
}
