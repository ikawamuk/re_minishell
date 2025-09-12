#include "parse.h"
#include <stdio.h>
void quote(t_element_list *element_list);
int dequote(t_element_list *element_list);
int	parse(t_element_list **element_list, char *str);
void *free_element_list(t_element_list *list);
int main(int ac, char *av[])
{
	int				result;
	t_element_list	*list = NULL;;
	t_element_list	*tmp_e = NULL;

	if (ac != 2)
		return (printf("input cmd line\n"), 1);
	result = parse(&list, av[1]); // yyparse // get_command_list_element
	if (result == ERROR)
		return (ERROR);
	quote(list);
	//dequote(list);
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
			printf("redir word[%d]: %s\n", i, list->data.rword_list->data.rword.value);
			free(list->data.rword_list->data.rword.value);
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
