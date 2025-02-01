/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tumolabs <tumolabs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 16:47:41 by algaboya          #+#    #+#             */
/*   Updated: 2025/01/19 21:16:55 by tumolabs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_statusik(char *arg)
{
	int		exitik;
	long	num;

	if (arg)
	{
		num = ft_atol(arg);
		exitik = num % 256;
		if (exitik < 0)
			exitik += 256;
		set_exit_status(exitik);
		return (exitik);
	}
	else
		return (get_exit_status());
}

int	exit_builtin(t_shell *general)
{
	int	exitik;
	int	count;

	count = count_args(general->cmd_lst->args);
	exitik = 255;
	write(2, "exit\n", 6);
	if (is_valid(general->cmd_lst->args, count) == FAILURE_EXIT)
		exit(exitik);
	if (count > 3)
		return (printf("minishell: exit: too many arguments\n"), FAILURE_EXIT);
	set_exit_status(exit_statusik(general->cmd_lst->args[1]));
	// free_general(general);
	exit(get_exit_status());
}
