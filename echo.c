/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 20:55:03 by algaboya          #+#    #+#             */
/*   Updated: 2025/01/31 19:37:12 by ashahbaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo_builtin(t_shell *general, t_cmd_lst *cmd)  //need argssssss
{
	//printf("olaaaaaa\n");
	int i;
    int j;
    int line_flag;

    i = 1;
    j = 2;
    line_flag = 0;
	(void)general;
    if (!cmd->args[i])
        return (ft_putstr_fd("\n", 1), 0);
    if (ft_strcmp(cmd->args[i], "-n") == 0)
    {
        while (cmd->args[i][j] == 'n')
            j++;
        line_flag = 1;
    }
    while (cmd->args && cmd->args[i])
    {
        ft_putstr_fd(cmd->args[i], 1);
        i++;
        if (cmd->args[i])
            ft_putstr_fd(" ", 1);
    }
    if (line_flag == 0)
    {    ft_putstr_fd("\n", 1);}
    set_exit_status(SUCCESS_EXIT);
	return (SUCCESS_EXIT);
}

