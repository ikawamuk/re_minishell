#include "parse.h"
#include <stdlib.h>
#include <stdio.h>

int	parse(t_element_list **element_list, char *str);

int main(int ac, char *av[])
{
	if (ac != 2)
		return (printf("need one arg\n"), 1);

	t_element_list	*list = NULL;
	t_element_list	*tmp_e = NULL;
	int result = parse(&list, av[1]);
	if (result)
		return (printf("parse: syntax error\n"), 2);
	while (list)
	{
		int i = 0;
		t_word_list	*tmp_w;
		while (list->data.word_list)
		{
			printf("argv[%d]: %s\n", i, list->data.word_list->data.value);
			free(list->data.word_list->data.value);
			tmp_w = list->data.word_list;
			list->data.word_list = list->data.word_list->next;
			free(tmp_w);
			i++;
		}
		i = 0;
		t_redir_word_list	*tmp_r;
		while (list->data.rword_list)
		{
			printf("redir word[%d]: %s\n", i, list->data.rword_list->data.word.value);
			free(list->data.rword_list->data.word.value);
			tmp_r = list->data.rword_list;
			list->data.rword_list = list->data.rword_list->next;
			free(tmp_r);
			i++;
		}
		tmp_e = list;
		list = list->next;
		free(tmp_e);
	}
}