#include <string.h>
#include <stdio.h>
#include "command.h"
#include "parse.h"

int create_command(t_simple_cmd *cmd, t_element element);

int main(int ac, char *av[])
{
	t_simple_cmd	cmd;
	t_element		element;

	if (ac != 3)
		return (printf("input argv and redir file name\n"), 1);
	element.word_list->data.flag = 0;
	element.word_list->data.value = strdup(av[1]);
	element.rword_list->data.type = R_IN;
	element.rword_list->data.rword.flag = 0;
	element.rword_list->data.rword.value = strdup(av[2]);
	create_command(&cmd, element);
	for (int i = 0; cmd.argv[i]; i++)
		printf("argv[%d]: %s", i, cmd.argv[i]);
	t_redir_list *next = cmd.redir->next;
	for (; cmd.redir; cmd.redir = next)
	{
		next = cmd.redir->next;
		printf("redir: type: %d file:%s", cmd.redir->redir.type, cmd.redir->redir.file_name);
	}
	return (0);
}