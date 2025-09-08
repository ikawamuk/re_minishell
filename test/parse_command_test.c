#include "command.h"
#include <stdio.h>

int	parse_command(t_command_list **cmd_list, char *str, char **envp);

int main(int ac, char *av[], char **envp)
{
	t_command_list *cmd_list = NULL;

	if (ac != 2)
		return (printf("input command line\n"), 1);
	
	parse_command(&cmd_list, av[1], envp);
	
	t_command_list *next_cmd = cmd_list->next;
	for (; cmd_list; cmd_list = next_cmd)
	{
		
		next_cmd = cmd_list->next;
		t_simple_cmd cmd = cmd_list->cmd;
		// printf("HERE1: %s\n", (char *)cmd.argv);
		for (int i = 0; cmd.argv[i]; i++)
		{
			// printf("HERE2\n");
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