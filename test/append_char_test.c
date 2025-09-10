#include <stdlib.h>
#include <string.h>
int append_char(char **str_p, char c)
{
	char	*new_str;
	size_t	len;

	len = strlen((*str_p)) + 2;
	new_str = calloc(sizeof(char), len);
	if (!new_str)
		return (1);
	strncpy(new_str, *str_p, len);
	new_str[len - 2] = c;
	free(*str_p);
	*str_p = new_str;
	return (0);
}

#include <stdio.h>
int main()
{
	char *str = strdup("");

	printf("%s\n", str);
	append_char(&str, 'a');
	printf("%s\n", str);
	append_char(&str, 'b');
	printf("%s\n", str);
	append_char(&str, 'c');
	printf("%s\n", str);
}