#include "parse.h"
#include "command.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int create_command_list(t_command_list **cmd_list, t_element_list *element_list);

int main(int ac, char *av[])
{
	if (ac != 9)
		return (printf("input argv and redir file name\n"), 1);

	t_element		element1;

	element1.word_list = malloc(sizeof(t_word_list));
	element1.word_list->data.flag = 0;
	element1.word_list->data.value = strdup(av[1]);
	element1.word_list->next = malloc(sizeof(t_word_list));
	element1.word_list->next->data.flag = 0;
	element1.word_list->next->data.value = strdup(av[2]);
	element1.word_list->next->next = NULL;
	element1.rword_list = malloc(sizeof(t_redir_word_list));
	element1.rword_list->data.type = R_IN;
	element1.rword_list->data.rword.flag = 0;
	element1.rword_list->data.rword.value = strdup(av[3]);
	element1.rword_list->next = malloc(sizeof(t_redir_word_list));
	element1.rword_list->next->data.type = R_IN;
	element1.rword_list->next->data.rword.flag = 0;
	element1.rword_list->next->data.rword.value = strdup(av[4]);
	element1.rword_list->next->next = NULL;

	t_element		element2;

	element2.word_list = malloc(sizeof(t_word_list));
	element2.word_list->data.flag = 0;
	element2.word_list->data.value = strdup(av[5]);
	element2.word_list->next = malloc(sizeof(t_word_list));
	element2.word_list->next->data.flag = 0;
	element2.word_list->next->data.value = strdup(av[6]);
	element2.word_list->next->next = NULL;
	element2.rword_list = malloc(sizeof(t_redir_word_list));
	element2.rword_list->data.type = R_IN;
	element2.rword_list->data.rword.flag = 0;
	element2.rword_list->data.rword.value = strdup(av[7]);
	element2.rword_list->next = malloc(sizeof(t_redir_word_list));
	element2.rword_list->next->data.type = R_IN;
	element2.rword_list->next->data.rword.flag = 0;
	element2.rword_list->next->data.rword.value = strdup(av[8]);
	element2.rword_list->next->next = NULL;


	t_element_list *element_list1 = malloc(sizeof(t_element_list));
	t_element_list *element_list2 = malloc(sizeof(t_element_list));

	element_list1->data = element1;
	element_list1->next = element_list2;
	element_list2->data = element2;
	element_list2->next = NULL;

	t_command_list *cmd_list = NULL;
	
	create_command_list(&cmd_list, element_list1);

	t_command_list *next_cmd = cmd_list->next;
	for (; cmd_list; cmd_list = next_cmd)
	{
		next_cmd = cmd_list->next;
		t_simple_cmd cmd = cmd_list->cmd;
		for (int i = 0; cmd.argv[i]; i++)
		{
			printf("argv[%d]: %s\n", i, cmd.argv[i]);
			free(cmd.argv[i]);
		}
		free(cmd.argv);
		t_redir_list *next = NULL;
		for (; cmd.redir_list; cmd.redir_list = next)
		{
			next = cmd.redir_list->next;
			printf("redir: type: %d file: %s\n", cmd.redir_list->data.type, cmd.redir_list->data.value.file_name);
			free(cmd.redir_list->data.value.file_name);
			free(cmd.redir_list);
		}
		free(cmd_list);
		cmd_list = next_cmd;
	}
	return (0);
}