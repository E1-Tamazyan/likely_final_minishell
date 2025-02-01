/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tumolabs <tumolabs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 18:45:39 by tumolabs          #+#    #+#             */
/*   Updated: 2025/01/19 20:28:22 by tumolabs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_prompt(int sig)
{
	set_exit_status(1);
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)sig;
}

void	ctrl_c(int sig)
{
	write(1, "\n", 1);
	(void)sig;
}

void	back_slash(int sig)
{
    ft_putstr_fd("Quit: 3\n", 2);
	(void)sig;
}

void	sig_handler_hdoc(int sig)
{
	(void)sig;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	set_exit_status(1);
}


void init_signal(int mode)
{
    if (mode == 1) // waits input
    {
        signal(SIGINT, restore_prompt);
        signal(SIGQUIT, SIG_IGN);
    }
    else if (mode == 2) // under execution
    {
        signal(SIGINT, ctrl_c);
		signal(SIGQUIT, back_slash);
    }
    else if (mode == 3) //during heredoc
    {
        signal(SIGINT, sig_handler_hdoc);
		signal(SIGQUIT, SIG_IGN);
    }
}