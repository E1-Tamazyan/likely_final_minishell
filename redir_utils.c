/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elen_t13 <elen_t13@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 00:19:48 by algaboya          #+#    #+#             */
/*   Updated: 2025/02/01 14:47:49 by elen_t13         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_redir_out(t_shell *general, char *name, int append)
{
	int	fd;

	if (general->curr_cmd->std_out == -1 || general->curr_cmd->std_in == -1)
		return (-1);
	if (append)
		fd = open(name, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
		fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		error_msg(1, name);
		// return (-1);
	}
	return (fd);
}
int	open_infile(t_shell *general, char *name)
{
	int	fd;

	if (general->curr_cmd->std_out == -1 || general->curr_cmd->std_in == -1)
		return (-1);
	fd = open(name, O_RDONLY);
	if (fd < 0)
	{
		error_msg(1, name);
		return (-1);
	}
	return (fd);
}

int	in_redir(t_cmd_lst *lst)
{
	if (lst->std_in == -1)
		return (-1);
	if (lst->std_in > 0)
	{
		if (dup2(lst->std_in, 0) < 0)
		{
			ft_putstr_fd("minishell: Dup Error\n", 2);
			close(lst->std_in);
			set_exit_status(EXIT_FAILURE);
		}
		close(lst->std_in);
	}
	return (0);
}

int	out_redir(t_cmd_lst *lst)
{
	if (lst->std_out == -1)
		return (-1);
	if (lst->std_out > 0)
	{
		if (dup2(lst->std_out, 1) < 0)
		{
			ft_putstr_fd("minishell: Dup Error\n", 2);
			close(lst->std_out);
			set_exit_status(EXIT_FAILURE);
		}
		close(lst->std_out);
	}
	return (0);
}

int	redir_dups(t_cmd_lst *lst)
{
	if (in_redir(lst) == -1)
		return (-1);
	if (out_redir(lst) == -1)
		return (-1);
	return (0);
}
