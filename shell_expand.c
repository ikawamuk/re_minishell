/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 06:50:55 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/12 20:01:18 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "command.h"

int expand(t_element_list *element_list, char **envp);
void quote(t_element_list *element_list);
int dequote(t_element_list *element_list);
int split(t_element_list *element_list);

#include <string.h>
int shell_expand(t_element_list *element_list, char **envp)
{
	quote(element_list); // クオートマーカーセット
	expand(element_list, envp); // word listの展開
	if (split(element_list) == ERROR) // word list単語分割、空文字列消去
		return (ERROR);
	if (dequote(element_list) == ERROR)
		return (ERROR); // クオート除去
	return (NO_ERROR);
}

