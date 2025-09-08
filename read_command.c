/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 02:19:26 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/08 15:15:39 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

int	parse_command(t_command_list **cmcd_list, char *str, char **envp);


/*
	read input and create command list.
	return 0 if succeed, else non-zero value.
*/
int	read_command(t_command_list **cmd_list, char **envp)
{
	char	*str;
	int		result;

	str = readline(PS1);
	if (!str)
		result = sig();
	else
		result = parse_command(cmd_list, str, envp);
	free(str);
	add_history(str);
	if (result);
		return (1);
	return (0);
}
