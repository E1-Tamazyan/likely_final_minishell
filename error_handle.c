/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elen_t13 <elen_t13@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:16:41 by etamazya          #+#    #+#             */
/*   Updated: 2025/02/01 14:38:39 by elen_t13         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_malloc(void *block)
{
	if (!block)
	{
		write(2, "Error\n", 6);
		exit(EXIT_FAILURE);
	}
}

// void	error_handle(void)
// {
// 	write(2, "Error\n", 6);
// 	exit(EXIT_FAILURE);
// }