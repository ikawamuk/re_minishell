/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 06:50:55 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/12 17:07:39 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "command.h"

void quote(t_element_list *element_list);
int dequote(t_element_list *element_list);
int split(t_element_list *element_list);

int expand(t_element_list *element_list, char **envp)
{
	quote(element_list); // クオートマーカーセット
	(void)envp; // word listの展開
	if (split(element_list) == ERROR) // word list単語分割、空文字列消去
		return (ERROR);
		// リダイレクトの展開は実行部でやろう。
		// redirect word listの展開
		// redirect word listで単語分割、空文字列が発生した場合はambiguas redirectでエラー
	// ワイルドカードの展開（グロブ展開）
	if (dequote(element_list) == ERROR)
		return (ERROR); // クオート除去
	return (NO_ERROR);
}

