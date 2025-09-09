#include "command.h"
#include <stdio.h>
#include "parse.h"

int	parse_command(t_command_list **cmd_list, char *str, char **envp);

int main(int ac, char *av[], char **envp)
{
	t_command_list *cmd_list = NULL;
	t_command_list *next_cmd = NULL;
	
	if (ac != 2)
		return (printf("input command line\n"), 1);
	
	int result = parse_command(&cmd_list, av[1], envp);
	if (result == ERROR){
		if (cmd_list)
		{
			for (; cmd_list; cmd_list = next_cmd)
			{
				next_cmd = cmd_list->next;
				t_simple_cmd cmd = cmd_list->cmd;
				if (cmd.argv){
					for (int i = 0; cmd.argv[i]; i++)
						free(cmd.argv[i]);
					free(cmd.argv);
				}
				t_redir_list *next = NULL;
				if (cmd.redir_list)
				{
					for (; cmd.redir_list; cmd.redir_list = next)
					{
						next = cmd.redir_list->next;
						free(cmd.redir_list->data.value.file_name);
						free(cmd.redir_list);
					}
					free(cmd_list);
				}
				cmd_list = next_cmd;
				
			}
		}
		return (printf("minishell: syntax error\n"), 2);
	}
		
	
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
			printf("redir: type: %d ", cmd.redir_list->data.type);
			if (cmd.redir_list->data.type != R_HEREDOC)
				printf("file: %s\n", cmd.redir_list->data.value.file_name);
			free(cmd.redir_list->data.value.file_name);
			free(cmd.redir_list);
		}
		free(cmd_list);
		cmd_list = next_cmd;
	}
	return (0);
}