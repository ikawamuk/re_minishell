/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 19:58:38 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/12 20:01:12 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int expand(t_element_list *element_list, char **envp)
{
	while (element_list)
	{
		expand_element();
		element_list = element_list->next;
	}
}
