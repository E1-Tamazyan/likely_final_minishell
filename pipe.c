/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elen_t13 <elen_t13@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 21:15:45 by tumolabs          #+#    #+#             */
/*   Updated: 2025/02/01 14:47:25 by elen_t13         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_pipe(t_shell *general)
{
	int	i;

	int(*fd)[2];
	i = 0;
	fd = malloc(sizeof(int[2]) * general->pipe_count);
	if (!fd)
	{
		printf("Malloc Error\n");
		clean_gen_exit(general, 1, 0, 1);
	}
	// printf("___pipe___\n");
	// while (i < general->pipe_count)
	// {
	//     if (pipe(fd[i]) == -1)
	//     {
	//         close_pipes(fd, general->pipe_count);
	//         free(fd);
	//         printf("Pipe Error\n");
	//         clean_gen_exit(general, 1, 0, 1);
	//     }
	//     i++;
	//     printf("pipes are created\n");
	// }
	while (i < general->pipe_count)
	{
		if (pipe(fd[i++]) == -1)
		{
			while (i > 0)
			{
				close(fd[i][0]);
				close(fd[i--][1]);
			}
			free(fd);
			printf("Pipe Error\n");
			// minishell_error("pipe error", "", "");
			return (-1);
		}
	}
	general->fd = fd;
	// int j = 0;
	// while (j < general->pipe_count)
	// {
	//     printf("[%d] - [%d][%d]\n", j, general->fd[j][0], general->fd[j][1]);
	//     j++;
	// }
	return (EXIT_SUCCESS);
}

void	close_pipes(int (*fd)[2], int count)
{
	int i;

	i = 0;
	while (i < count)
	{
		close(fd[i][0]);
		// dprintf(2, "closing fd[%i][0]\n", i);
		close(fd[i][1]);
		// dprintf(2, "closing fd[%i][1]\n", i);
		i++;
	}
	// dprintf(2, "PIPES ARE CLOSED\n\n");
}