/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elen_t13 <elen_t13@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:46:36 by algaboya          #+#    #+#             */
/*   Updated: 2025/02/01 14:47:45 by elen_t13         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_builtin(t_shell *general)
{
	char	cwd[4096];

	if (!general)
	{
		printf("minisHell: pwd: Data error\n");
		return (EXIT_FAILURE);
	}
	if (!getcwd(cwd, sizeof(cwd)))
	{
		printf("minisHell: pwd: Data error\n");
		return (EXIT_FAILURE);
	}
	printf("%s\n", cwd);
	return (EXIT_SUCCESS);
}
