/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 02:25:41 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/08 20:09:58 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "parse.h"

int	parse(t_element **element_list, char *str);
int expand(t_element_list *element_list, char **envp);
static void	*free_element_list(t_element_list *list);
int create_command_list(t_command_list **cmd_list, t_element_list *element_list);

/*
	create command list from str.
	return 0 if succeed, else non-zero.
*/

int	parse_command(t_command_list **cmd_list, char *str, char **envp)
{
	int				result;
	t_element_list	*element_list;

	element_list = NULL;
	result = parse(&element_list, str); // yyparse // get_command_list_element
	if (result == ERROR)
		return (free_element_list(element_list), ERROR);
	gather_heredoc(element_list); // heredocが必要かどうかはココで判定する
	result = expand(element_list, envp); // コマンド引数の環境変数展開,  コマンド引数の単語分割、空文字削除, リダイレクト部の展開
	if (result != NO_ERROR)
		return (free_element_list(element_list), ERROR);
	result = create_command_list(cmd_list, element_list); // なかで適切にelenentlistをcleanする
	if (result != NO_ERROR)
		return (free_element_list(element_list), ERROR);
	return (result);
}

int	set_redirect_word(t_simple_cmd *cmd, t_redir_word_list *rword_list)
{
	if (cmd->redir_list->data.type != R_HEREDOC)
	{
		cmd->redir_list->data.value.file_name = strdup(rword_list->data.rword.value);
		if (!cmd->redir_list->data.value.file_name)
			return (error_create_redirect_list(cmd, rword_list));
	}
	else  if (cmd->redir_list->data.type == R_HEREDOC) // word_list->data.rword.valueがEOF
		gather_heredoc(&cmd->redir_list->data, rword_list->data.rword); // make tmp file, read stdin, write in, unlink tmp file set fd as the ->file name 
		// rword_list->data.pipe にpipefdをセット
	return (NO_ERROR);
}
