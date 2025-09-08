#include <string.h>
#include <stdio.h>
#include "command.h"
#include "parse.h"

int create_command(t_simple_cmd *cmd, t_element element);

int main(int ac, char *av[])
{
	t_simple_cmd	cmd;
	t_element		element;

	if (ac != 5)
		return (printf("input argv and redir file name\n"), 1);
	
	element.word_list = malloc(sizeof(t_word_list));
	element.word_list->data.flag = 0;
	element.word_list->data.value = strdup(av[1]);
	element.word_list->next = malloc(sizeof(t_word_list));
	element.word_list->next->data.flag = 0;
	element.word_list->next->data.value = strdup(av[2]);
	element.word_list->next->next = NULL;
	element.rword_list = malloc(sizeof(t_redir_word_list));
	element.rword_list->data.type = R_IN;
	element.rword_list->data.rword.flag = 0;
	element.rword_list->data.rword.value = strdup(av[3]);
	element.rword_list->next = malloc(sizeof(t_redir_word_list));
	element.rword_list->next->data.type = R_IN;
	element.rword_list->next->data.rword.flag = 0;
	element.rword_list->next->data.rword.value = strdup(av[4]);
	element.rword_list->next->next = NULL;
	
	create_command(&cmd, element);

	for (int i = 0; cmd.argv[i]; i++)
		printf("argv[%d]: %s\n", i, cmd.argv[i]);
	t_redir_list *next = cmd.redir_list->next;
	for (; cmd.redir_list; cmd.redir_list = next)
	{
		next = cmd.redir_list->next;
		printf("redir: type: %d file: %s\n", cmd.redir_list->data.type, cmd.redir_list->data.value.file_name);
	}
	return (0);
}