/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tumolabs <tumolabs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 21:55:53 by algaboya          #+#    #+#             */
/*   Updated: 2025/02/01 13:38:20 by tumolabs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int heredoc_init(t_shell *g, t_cmd_lst **cmd, t_token *tok)
{
	(void)g;
	(void)cmd;
	// if(tok)
	// {
		if ((*cmd)->heredoc == NULL)
		{
			(*cmd)->heredoc = ft_strdup(tok->context);
			check_malloc((*cmd)->heredoc);
		}
	// }
	return (0);
}
void	execute_heredoc(t_shell *g, t_cmd_lst *cmd)
{
	char *input;

	(void)g;
	cmd -> std_in = open("temple.txt", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (cmd -> std_in < 0)
	{
		printf("./minisHell\n");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		input = readline("> ");
		if (input == NULL)
			break ;
		if (ft_strcmp(input, cmd->heredoc) == 0)
		{
			free(input);
			break ;
		}
		write(cmd -> std_in, input, ft_strlen(input));
		write(cmd -> std_in, "\n", 1);
		free(input);
	}
	close(cmd -> std_in);
	open_infile(g, "temple.txt");
}



// int redirs_management(t_cmd_lst *cmd, t_ttype type)
// {
// 	if (cmd->red_out)
// 		free_set_null(cmd->red_out);
// 	cmd->red_out = ft_strdup(g->curr_tok->context);
// 	cmd -> std_out = open_redir_out(g, cmd -> red_out, 0);
// 	 }
// 	t_cmd_lst *cmd;

// 	cmd = g -> cmd_lst;
// 	while (cmd)
// 	{
// 		// if (cmd -> red_out)
// 		// 	cmd -> std_out = open_redir_out(g, cmd -> red_out, 0);
// 		if (cmd -> red_append)
// 			cmd -> std_out = open_redir_out(g, cmd -> red_append, 1);
// 		else if (cmd -> heredoc)
// 			execute_heredoc(g, cmd);
// 		else if (cmd -> red_in)
// 			cmd -> std_in = open_infile(g, cmd -> red_in);
// 		cmd = cmd -> next;
// 	}
// 	return (0);
// }
