/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 02:25:41 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/08 23:07:21 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "parse.h"
#include <string.h>
#include <stdio.h>

int	parse(t_element_list **element_list, char *str);
// int expand(t_element_list *element_list, char **envp);
int create_command_list(t_command_list **cmd_list, t_element_list *element_list);
void	*free_element_list(t_element_list *list);
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
	(void)envp;
	// result = expand(element_list, envp); // コマンド引数の環境変数展開,  コマンド引数の単語分割、空文字削除, リダイレクト部の展開
	// if (result != NO_ERROR)
	// 	return (free_element_list(element_list), ERROR);


	result = create_command_list(cmd_list, element_list); // なかで適切にelenentlistをcleanする
	if (result != NO_ERROR)
		return (free_element_list(element_list), ERROR);
	return (result);
}


