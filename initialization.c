/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tumolabs <tumolabs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:38:08 by algaboya          #+#    #+#             */
/*   Updated: 2025/02/01 14:52:45 by tumolabs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_general(t_shell *general)
{
	general->tok_lst = NULL;
	general->env_lst = NULL;
	general->cmd_lst = NULL;
	general->doll_lst = (t_dollar *)malloc(sizeof(t_dollar)); // check this later
	general->sorted_env_lst = NULL;
	general->shlvl = -1;
	general->sg_quote = 0; //no quote
	general->db_quote = 0; // no quote
	general->pipe_index = 0;
	// general->exit_status = 0;
	general->pipe_count = 0;
	general -> original_stdin = dup(STDIN_FILENO);
	general -> original_stdout = dup(STDOUT_FILENO);
}

int	init_input(char *input, t_shell *general)
{
	static int	index;

	while (1)
	{
		index = 0;
		init_signal(1);
		input = readline("\033[38;5;51m\033[48;5;16mminisHell:\033[0m "); //neon
		if(input && input[0])
		{
			add_history(input);
			if (init_tokens_cmds(input, general, 0) == 0)
			{
				execution(general, index);
				close_pipes(general->fd, general->pipe_count);
			}
			free(input);
		}
		else if (!input)
		{
			free(general->doll_lst);
			exit(get_exit_status());
		}
	}
	return (free(input), get_exit_status());
}

t_env *init_env_nodes(char **env)
{
	t_env	*list_env;
	t_env	*tmp;
	t_env	*new_node;
	int		i;

	i = 0;
	list_env = NULL;
	tmp = NULL;
	while (env[i] != NULL)
	{
		new_node = ft_lstnew(env[i], 1);
		if (!new_node)
			return NULL;
		if (list_env == NULL)
		{
			list_env = new_node;
			tmp = list_env;
		}
		else
			ft_lstadd_back(tmp, new_node);
		i++;
	}
	return (list_env);
}

void	check_heredoc_syntax(t_token *head)
{
	while (head)
	{
		if(head->type == 5)
		{
			head = head->next;
			if (head->type == 1 || head->type == 2 \
			|| head->type == 3 || head->type == 4 \
			|| head->type == 5)
			{
				printf("\nsyntax error unexpected token %s\n", head->context);
				set_exit_status(2);
				exit(get_exit_status()); // waiting for Alla's exit status
			}
		}
		head = head->next;
	}
}

void	check_heredoc_limit(t_shell *general)
{
	t_token	*head;
	int	count;

	count = 0;
	head = general->tok_lst;

	while (head)
	{
		if (head->type == 5)
			count++;
		head = head->next;
	}
	if (count > 16)
	{
		printf("minisHell: maximum here-document count exceeded\n"); // check later pleaseee. SIGSEGV
		// waiting for Alla's cleaning function, general for this
		exit(2);
	}
	head = general->tok_lst;
	check_heredoc_syntax(head);
}

//the dollar sign should be oneend in tis function
// short	init_tokens(char *input, t_shell *general, int i)
// {
// 	int	start;
// 	int flag;
// 	// t_token *head;

// 	// head = general->tok_lst;
// 	flag = 0;
// 	while ((input[i] >= 9 && input[i] <= 13) || input[i] == 32)
// 		i++;
// 	while (flag >= 0 && input[i] != '\0')
// 	{
// 		if (flag >= 0 && input[i] && (input[i] == '|' || input[i] == '>'
// 			|| input[i] == '<' || input[i] == ' ')) // added dollar sign - init_op_token
// 				flag = init_op_token(input, i, &general->tok_lst);
// 		else
// 		{
// 			start = i;
// 			while (flag >= 0 && input[i] && input[i] != '|' && input[i] != '>' && input[i] != '<'
// 				&& input[i] != ' ' && input[i] != '$' && input[i] != 34 && input[i] != 39)
// 				i++;
// 			if (flag >= 0 && input[i] && (input[i] == '|' || input[i] == '>'
// 				|| input[i] == '<' || input[i] == ' ')) // added dollar sign - init_op_token
// 				flag = init_op_token(input, i, &general->tok_lst);
// 			if (input[i] && flag >= 0)
// 				flag = check_cut_quotes(general, &input, &i, start); // and added dollar sign here check_cut_quotes
// 			else if (i > start)
// 			{
// 				// printf("bbb = %d, %d\n", i, start);
// 				add_token_list(&general->tok_lst, my_substr((const char *)input, start, i - start), 0);
// 			}
// 			i--;
// 		}
// 		if(flag < 0)
// 			return (clean_list(&general->tok_lst), -1);
// 		if (input[i])
// 			i++;
// 	}
// 	return (0);
// }

int	init_tokens_cmds(char *input, t_shell *general, int i)
{
	int	start;
	int flag;

	flag = 0;
	while ((input[i] >= 9 && input[i] <= 13) || input[i] == 32)
		i++;
	while (flag >= 0 && input[i] != '\0')
	{
		if (flag >= 0 && input[i] && (input[i] == '|' || input[i] == '>'
			|| input[i] == '<' || input[i] == ' '))
				flag = init_op_token(input, &i, &general->tok_lst);
		else
		{
			start = i;
			while (flag >= 0 && input[i] && input[i] != '|' && input[i] != '>' && input[i] != '<'
				&& input[i] != ' ' && input[i] != '$' && input[i] != 34 && input[i] != 39)
				i++;
			if (input[i] && flag >= 0)
				flag = check_cut_quotes(general, &input, &i, start);
			else if (i > start)
				add_token_list(&general->tok_lst, my_substr((const char *)input, start, i - start), 0);
			i--;
		}
		if(flag < 0)
			return (clean_list(&general->tok_lst), -1);
		if (input[i])
			i++;
	}
	general->tok_lst = remove_extra_quotes(general);
	check_heredoc_limit(general);
	create_cmd_lst(general);
	clean_list(&general->tok_lst);
	return (0);
}

void	print_cmd(t_cmd_lst	*cmd_lst)
{
	t_cmd_lst *temp;

	temp = cmd_lst;
	printf("----\n");
	while (temp)
	{
		printf("Command: %s\n", temp->cmd);
		if (temp -> red_out)
			printf("R_OUT: %s\n", temp->red_out);
		if (temp -> red_in)
			printf("R_IN: %s\n", temp->red_in);
		if (temp -> heredoc)
			printf("R_HEREDOC: %s\n", temp->heredoc);
		if (temp -> red_append)
			printf("R_APPEND: %s\n", temp->red_append);
		printf("stdin %d\n", temp -> std_in);
		printf("stdout %d\n", temp -> std_out);
		printf("Arguments:");
		int i = 0;
		while(temp->args && temp->args[i])
		{
			printf("[%s] ", temp->args[i]);
			i++;
		}
		printf("\n\n");
		temp = temp->next;
	}
	printf("----\n");
}

// int	init_op_token(char *input, int i, t_token **token_list)
// {
// 	if (!input || !token_list)
// 		return i;
// 	if (input[i] && input[i] == '|') // ❗️❗️
// 	{
// 		if (!input[i + 1] || (!input[i + 2] && input[i + 1] != '|')) // change this part later
// 			return (printf("minisHell: syntax error near unexpected token `newline'\n"), -1);
// 		if (input[i + 1] == '|')
// 			return (printf("minisHell: syntax error near unexpected token `||'\n"), -1);
// 		add_token_list(token_list, my_substr(input, i, 1), 1);
// 	}
// 	else if (input[i] && input[i] == '>')
// 	{
// 		if (!input[i + 1] || (input[i + 1] != '<' && !input[i + 2])) // DONEEEE
// 			return (printf("minisHell: syntax error near unexpected token `newline'\n"), -1);
// 		if (input[i + 1] && input[i + 1] == '>') // DONEEE
// 		{
// 			if ((input[i + 2] && input[i + 2] == '>' && (input[i + 3] && input[i + 3] == '>')) || ((input[i + 2] && input[i + 2] == '<') && (input[i + 3] && (input[i + 3] == '<' || input[i + 3] == '|'))))
// 				return (printf("minisHell: syntax error near unexpected token `%c%c'\n", input[i + 2], input[i + 3]), -1);
// 			if (input[i + 2] && (input[i + 2] == '>' || input[i + 2] == '<' || input[i + 2] == '|'))
// 				return (printf("minisHell: syntax error near unexpected token `%c'\n", input[i + 2]), -1);
// 			add_token_list(token_list, my_substr(input, i, 2), 4);
// 			i++;
// 		}
// 		else if (input[i + 1] && (input[i + 1] == '<')) // DONE
// 		{
// 			if (input[i + 2] && input[i + 2] == '<' && input[i + 3] && input[i + 3] == '<') // ><> ><|
// 				return (printf("minisHell: syntax error near unexpected token `%c%c%c'\n", input[i + 1], input[i + 2], input[i + 3]), -1);
// 			if (input[i + 2] && (input[i + 2] == '>' || input[i + 2] == '<')) // ><> ><|
// 				return (printf("minisHell: syntax error near unexpected token `%c%c'\n", input[i + 1], input[i + 2]), -1);
// 			return (printf("minisHell: syntax error near unexpected token `%c'\n", input[i + 1]), -1);
// 		}
// 		else if ((input[i + 1] && input[i + 1] == '|') || !input[i + 2]) // added this part //DONEEEEEEE
// 		{
// 			if (input[i + 2] && input[i + 3] && (input[i + 2] == '>' || input[i + 2] == '<' || input[i + 2] == '|')) // >|<, >|>, >||: // added this part
// 				return (printf("minisHell: syntax error near unexpected token `%c'\n", input[i + 2]), -1); // added this part
// 			else
// 				return (printf("minisHell: syntax error near unexpected token `%c'\n", input[i + 1]), -1); // added this part
// 		}
// 		else
// 			add_token_list(token_list, my_substr(input, i, 1), 3);
// 	}
// 	else if (input[i] && input[i] == '<') // ⛔️⛔️⛔️⛔️⛔️⛔️⛔️     <> <*|
// 	{
// 		if (!input[i + 1] || (input[i + 1] != '>' && !input[i + 2]))
// 			return (printf("minisHell: syntax error near unexpected token `newline'\n"), -1);
// 		if (input[i + 1] && input[i + 1] == '<')
// 		{
// 			if ((input[i + 2] && input[i + 2] == '>') && (input[i + 3] && (input[i + 3] == '>' ||  input[i + 3] == '|')))
// 				return (printf("minisHell: syntax error near unexpected token `%c%c'\n", input[i + 2], input[i + 3]), -1);
// 			if (input[i + 1] == '|' || (input[i + 2] && (input[i + 2] == '<' || input[i + 2] == '>' || input[i + 2] == '|')))
// 				return (printf("minisHell: syntax error near unexpected token `%c'\n", input[i + 2]), -1);
// 			add_token_list(token_list, my_substr(input, i, 2), 5);
// 			i++;
// 		}
// 		// else if (input[i + 1] == '>')
// 		// 	printf(">"); // ⛔️⛔️⛔️⛔️⛔️⛔️⛔️ try to understand do you need to implement this?  cmd:ls <> echo dasd (works only for existing file)
// 		else if (input[i + 1] == '|')
// 				return (printf("minisHell: syntax error near unexpected token `%c'\n", input[i + 1]), -1);
// 		else
// 			add_token_list(token_list, my_substr(input, i, 1), 2);
// 	}
// 	return (i);
// }


// int init_op_token(char *input, int *i, t_token **token_list)
// {
// 	if (!input || !token_list)
// 		return -1;
// 	if (input[*i] && input[*i] == '|')
// 	{
// 		if (!input[*i + 1] || (input[*i + 1] != '|' && !input[*i + 2])) // Handle syntax error
// 			return (printf("minisHell: syntax error near unexpected token `newline'\n"), -1);
// 		if (input[*i + 1] == '|')
// 			return (printf("minisHell: syntax error near unexpected token `||'\n"), -1);
// 		add_token_list(token_list, my_substr(input, *i, 1), 1);
// 	}
// 	else if (input[*i] && input[*i] == '>')
// 	{
// 		// Handle '>' and '>>' tokens
// 		if (!input[*i + 1] || (input[*i + 1] != '<' && !input[*i + 2])) // Handle error
// 			return (printf("minisHell: syntax error near unexpected token `newline'\n"), -1);
// 		if (input[*i + 1] && input[*i + 1] == '>')
// 		{
// 			if (input[*i + 2] && (input[*i + 2] == '>' || input[*i + 2] == '<' || input[*i + 2] == '|'))
// 				return (printf("minisHell: syntax error near unexpected token `%c%c'\n", input[*i + 2], input[*i + 3]), -1);
// 			add_token_list(token_list, my_substr(input, *i, 2), 4);
// 			(*i)++;
// 		}
// 		else if (input[*i + 1] && input[*i + 1] == '<')
// 			return (printf("minisHell: syntax error near unexpected token `%c%c'\n", input[*i + 1], input[*i + 2]), -1); //Handle error for invalid combinations like '><' or '<|'
// 		else
// 			add_token_list(token_list, my_substr(input, *i, 1), 3);
// 	}
// 	else if (input[*i] && input[*i] == '<')
// 	{
// 		if (!input[*i + 1] || (input[*i + 1] != '>' && !input[*i + 2])) // Handle error
// 			return (printf("minisHell: syntax error near unexpected token `newline'\n"), -1);
// 		if (input[*i + 1] && input[*i + 1] == '<')
// 		{
// 			if (input[*i + 2] && (input[*i + 2] == '>' || input[*i + 2] == '<'))
// 				return (printf("minisHell: syntax error near unexpected token `%c%c'\n", input[*i + 2], input[*i + 3]), -1);
// 			add_token_list(token_list, my_substr(input, *i, 2), 5);
// 			(*i)++;
// 		}
// 		else
// 			add_token_list(token_list, my_substr(input, *i, 1), 2);
// 	}
// 	return (*i);
// }


int	create_env(char **env, t_shell *general)
{
	char	**sorted;

	general -> env_lst = init_env_nodes(env);
	sorted = sort_env(env);
	general -> sorted_env_lst = init_env_nodes(sorted);
	free_array(sorted);
	sorted = NULL;
	return (0);
}


t_cmd_lst	*initialize_new_cmd()
{
	t_cmd_lst	*new_cmd;

	new_cmd = (t_cmd_lst	*)malloc(sizeof(t_cmd_lst));
	check_malloc(new_cmd);
	new_cmd->cmd = NULL;
	new_cmd->args = NULL;
	new_cmd->next = NULL;
	new_cmd->heredoc = NULL;
	new_cmd->red_in = NULL;
	new_cmd->red_out = NULL;
	new_cmd->red_append = NULL;
	new_cmd->std_in = -2;
	new_cmd->std_out = -2;
	return (new_cmd);
}



static int check_dollar_sign(char *input, int *i, t_token **token_list)
{
	if (input[*i] && input[*i] == '$')
	{
		if (input[*i + 1] && input[*i + 1] == '$')
			add_token_list(token_list, my_substr(input, *i, 2), 4);
		(*i)++;
		return 1;
	}
	return 0;
}

static int check_pipe_sign(char *input, int *i, t_token **token_list)
{
	if (input[*i] && input[*i] == '|')
	{
		if (!input[*i + 1] || (input[*i + 1] != '|' && !input[*i + 2])) // Syntax error
			return (printf("minisHell: syntax error near unexpected token `newline'\n"), -1);
		if (input[*i + 1] == '|') // Handle `||` error
			return (printf("minisHell: syntax error near unexpected token `||'\n"), -1);
		add_token_list(token_list, my_substr(input, *i, 1), 1);
		return 1;
	}
	return 0;
}

static int check_greater_than_sign(char *input, int *i, t_token **token_list)
{
	if (input[*i] && input[*i] == '>')
	{
		if (!input[*i + 1] || (input[*i + 1] != '<' && !input[*i + 2])) // Syntax error
			return (printf("minisHell: syntax error near unexpected token `newline'\n"), -1);

		if (input[*i + 1] && input[*i + 1] == '>')
		{
			if (input[*i + 2] && (input[*i + 2] == '>' || input[*i + 2] == '<' || input[*i + 2] == '|'))
				return (printf("minisHell: syntax error near unexpected token `%c%c'\n", input[*i + 2], input[*i + 3]), -1);
			add_token_list(token_list, my_substr(input, *i, 2), 4);
			(*i)++;
		}
		else if (input[*i + 1] && input[*i + 1] == '<')
		{
			return (printf("minisHell: syntax error near unexpected token `%c%c'\n", input[*i + 1], input[*i + 2]), -1);
		}
		else
			add_token_list(token_list, my_substr(input, *i, 1), 3);
		return 1;
	}
	return 0;
}

static int check_less_than_sign(char *input, int *i, t_token **token_list)
{
	if (input[*i] && input[*i] == '<')
	{
		if (!input[*i + 1] || (input[*i + 1] != '>' && !input[*i + 2])) // Syntax error
			return (printf("minisHell: syntax error near unexpected token `newline'\n"), -1);

		if (input[*i + 1] && input[*i + 1] == '<')
		{
			if (input[*i + 2] && (input[*i + 2] == '>' || input[*i + 2] == '<'))
				return (printf("minisHell: syntax error near unexpected token `%c%c'\n", input[*i + 2], input[*i + 3]), -1);
			add_token_list(token_list, my_substr(input, *i, 2), 5);
			(*i)++;
		}
		else
			add_token_list(token_list, my_substr(input, *i, 1), 2);
		return 1;
	}
	return 0;
}

int init_op_token(char *input, int *i, t_token **token_list)
{
	if (!input || !token_list)
		return -1; // Return error if input or token_list is invalid
	// Check for specific tokens
	if (check_dollar_sign(input, i, token_list) == -1)
		return -1;
	if (check_pipe_sign(input, i, token_list) == -1)
		return -1;
	if (check_greater_than_sign(input, i, token_list) == -1)
		return -1;
	if (check_less_than_sign(input, i, token_list) == -1)
		return -1;
	return (*i);
}
