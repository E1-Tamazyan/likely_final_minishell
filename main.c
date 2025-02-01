/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elen_t13 <elen_t13@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 14:42:13 by etamazya          #+#    #+#             */
/*   Updated: 2025/02/01 14:31:46 by elen_t13         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ************************
// *** WARNING *** FULL ***
// ************************

int	main(int argc, char **argv, char **env)
{
	t_shell	*general;
	char	*input;

	(void)argv;
	input = NULL;
	general = (t_shell *)malloc(sizeof(t_shell));
	check_malloc(general);
	if (argc == 1)
	{
		init_general(general);
		create_env(env, general);
		incr_shlvl(general);
		if (init_input(input, general)) // if 1 error
			return (free(general), get_exit_status());
	}
	free(general);
	return (get_exit_status());
}
