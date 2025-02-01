/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:16:41 by etamazya          #+#    #+#             */
/*   Updated: 2024/12/11 11:21:07 by etamazya         ###   ########.fr       */
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