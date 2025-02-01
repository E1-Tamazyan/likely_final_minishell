/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_fts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elen_t13 <elen_t13@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:39:24 by etamazya          #+#    #+#             */
/*   Updated: 2025/02/01 14:47:29 by elen_t13         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printStrings(char **strs)
{
	int	i;

	i = 0;
	if (!strs)
		return ;
	while (strs[i] != NULL)
	{
		printf("%s\n", strs[i]);
		i++;
	}
}
