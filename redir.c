/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elen_t13 <elen_t13@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 21:55:53 by algaboya          #+#    #+#             */
/*   Updated: 2025/02/01 14:48:09 by elen_t13         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_init(t_shell *g, t_cmd_lst **cmd, t_token *tok)
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
	char	*input;

	(void)g;
	cmd->std_in = open("temple.txt", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (cmd->std_in < 0)
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
		write(cmd->std_in, input, ft_strlen(input));
		write(cmd->std_in, "\n", 1);
		free(input);
	}
	close(cmd->std_in);
	open_infile(g, "temple.txt");
}

int	open_heredoc(t_shell *g, t_token *tok, t_cmd_lst *cmd, int flag)
{
	(void)flag;
	printf("tokk == %s\n", tok->context);
	if (g->cmd_lst->heredoc == NULL)
	{
		if (heredoc_init(g, &cmd, tok) == -1)
			return (-1);
	}
	else if (g->cmd_lst->heredoc != NULL)
	{
		free(g->cmd_lst->heredoc);
		if (heredoc_init(g, &cmd, tok) == -1)
			return (-1);
	}
	execute_heredoc(g, cmd);
	return (0);
}

int	open_redir_2(t_shell *g)
{
	if (ft_strcmp(g->curr_tok->context, "<<") == 0)
	{
		printf("tokk == %s\n", g->curr_tok->context);
		g->curr_tok = ft_lst_delone(&g->tok_lst, g->curr_tok);
		g->curr_cmd->std_in = open_heredoc(g, g->curr_tok, g->curr_cmd, 1);
		if (g->curr_cmd->std_in == -1)
			return (EXIT_FAILURE);
	}
	else if (g->curr_tok->context[0] == '<')
	{
		g->curr_tok = ft_lst_delone(&g->tok_lst, g->curr_tok);
		g->curr_cmd->std_in = open_infile(g, g->curr_tok->context);
		if (g->curr_cmd->std_in == -1)
			return (EXIT_FAILURE);
	}
	return (0);
}

int	open_redir(t_shell *g)
{
	int	status;

	status = 0;
	if (ft_strcmp(g->curr_tok->context, ">>") == 0)
	{
		g->curr_tok = ft_lst_delone(&g->tok_lst, g->curr_tok);
		g->curr_cmd->std_out = open_redir_out(g, g->curr_tok->context, 1);
		if (g->curr_cmd->std_out == -1)
			return (EXIT_FAILURE);
	}
	else if (g->curr_tok->context[0] == '>')
	{
		printf("%s\n, ", g->curr_cmd->cmd);
		g->curr_tok = ft_lst_delone(&g->tok_lst, g->curr_tok);
		g->curr_cmd->std_out = open_redir_out(g, g->curr_tok->context, 0);
		if (g->curr_cmd->std_out == -1)
			return (EXIT_FAILURE);
	}
	else
		status = open_redir_2(g);
	g->curr_tok = ft_lst_delone(&g->tok_lst, g->curr_tok);
	return (status);
}