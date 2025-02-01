/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaboya <algaboya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:11:10 by elen_t13          #+#    #+#             */
/*   Updated: 2025/01/26 23:17:55 by algaboya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	count_mid_args(t_token *start, t_token *end)
// {
// 	int	count;

// 	count = 0;
// 	while (start && start != end)
// 	{
// 		count++;
// 		start = start->next;
// 	}
// 	return (count);
// }

// static void	fill_cmd_token(t_cmd_lst *new_cmd, t_token *cmd_start, int token_count)
// {
// int		i;
// t_token	*current_token;

// i = 0;
// current_token = cmd_start;
// new_cmd->args = malloc(sizeof(char *) * (token_count + 1));
// if (!new_cmd->args)
// 	return ;
// if (ft_strcmp(current_token->context, " ") == 0)
// new_cmd->cmd = strdup(current_token->next->context);
// else
// new_cmd->cmd = strdup(current_token->context);
// write(1, "#\n", 2);
// 	new_cmd->args[0] = strdup(current_token->context);
// 	current_token = cmd_start->next;
// 	while (i < token_count)
// 	{
// 		new_cmd->args[i] = strdup(current_token->context);
// 		printf("new_cmd->arg = %s[%d]\n", new_cmd->args[i], i);
// 		current_token = current_token->next;
// 		i++;
// 	}
// 	new_cmd->args[token_count] = NULL;
// }

// static t_cmd_lst *create_cmd_lst(t_token *token_lst)
// {
// 	t_cmd_lst *cmd_lst = NULL;
// 	t_cmd_lst *current_cmd = NULL;
// 	t_cmd_lst *new_cmd;
// 	t_token *start;
// 	int token_count;
// 	t_token	*current_token;
// 	int i;

// 	i = 1;
// 	while (token_lst)
// 	{
// 		new_cmd = malloc(sizeof(t_cmd_lst));
// 		check_malloc(new_cmd);
// 		new_cmd->cmd = NULL;
// 		new_cmd->args = NULL;
// 		new_cmd->next = NULL;
// 		start = token_lst;
// 		printf("start = %s\n", start->context);
// 		while (token_lst && token_lst->type != 1)
// 			token_lst = token_lst->next;
// token_count = count_mid_args(start, token_lst);
// 		if (token_count > 0)
// 		{
// 			new_cmd->args = malloc(sizeof(char *) * (token_count + 1));
// 			check_malloc(new_cmd->args);
// 			current_token = start;
// 			if (ft_strcmp(current_token->context, " ") == 0)
// 			{
// 				new_cmd->cmd = strdup(current_token->next->context);
// 				new_cmd->args[0] = strdup(current_token->next->context);
// 			}
// 			else
// 			{
// 				new_cmd->cmd = strdup(current_token->context);
// 				new_cmd->args[0] = strdup(current_token->context);
// 			}
// 			current_token = start->next;
// 			while (i < token_count)
// 			{
// 				new_cmd->args[i] = strdup(current_token->context);
// 				current_token = current_token->next;
// 				i++;
// 			}
// 			new_cmd->args[token_count] = NULL;
// 		}
// 		if (!cmd_lst)
// 			cmd_lst = new_cmd;
// 		else
// 			current_cmd->next = new_cmd;
// 		current_cmd = new_cmd;
// 		if (token_lst && token_lst->type == 1)
// 			token_lst = token_lst->next;
// 	}
// 	return (cmd_lst);
// }

// static t_cmd_lst *create_cmd_lst(t_token *token_lst) {
//     t_cmd_lst *cmd_lst = NULL;
//     t_cmd_lst *current_cmd = NULL;

//     while (token_lst) {
//         t_cmd_lst *new_cmd = malloc(sizeof(t_cmd_lst));
//         check_malloc(new_cmd);

//         new_cmd->cmd = NULL;
//         new_cmd->args = NULL;
//         new_cmd->next = NULL;
//         t_token *current_token = token_lst;
//         int token_count = 0;
//         while (current_token && current_token->type != 1) {
//             if (token_count == 0) {
//                 new_cmd->cmd = strdup(current_token->context);
//             }
//             token_count++;
//             current_token = current_token->next;
//         }
//         new_cmd->args = malloc(sizeof(char *) * (token_count + 1));
//         check_malloc(new_cmd->args);
//         current_token = token_lst;
//         for (int i = 0; i < token_count; i++) {
//             new_cmd->args[i] = strdup(current_token->context);
//             current_token = current_token->next;
//         }
//         new_cmd->args[token_count] = NULL;
//         if (!cmd_lst) {
//             cmd_lst = new_cmd;
//         } else {
//             current_cmd->next = new_cmd;
//         }
//         current_cmd = new_cmd;
//         while (token_lst && token_lst->type != 1) {
//             token_lst = token_lst->next;
//         }
//         if (token_lst && token_lst->type == 1) {
//             token_lst = token_lst->next;
//         }
//     }
//     return cmd_lst;
// }

// static t_cmd_lst *initialize_new_cmd()
// {
//     t_cmd_lst *new_cmd = malloc(sizeof(t_cmd_lst));
//     check_malloc(new_cmd);
//     new_cmd->cmd = NULL;
//     new_cmd->args = NULL;
//     new_cmd->next = NULL;
//     return new_cmd;
// }

// static int count_tokens(t_token *token_lst)
// {
//     int count;

//     count = 0;
//     while (token_lst && token_lst->type != 1)
//     {
//         count++;
//         token_lst = token_lst->next;
//     }
//     return count;
// }

// static void populate_command(t_cmd_lst *cmd, t_token *token_lst, int token_count)
// {
//     cmd->cmd = strdup(token_lst->context);
//     cmd->args = malloc(sizeof(char *) * (token_count + 1));
//     check_malloc(cmd->args);

//     for (int i = 0; i < token_count; i++)
//     {
//         cmd->args[i] = strdup(token_lst->context);
//         token_lst = token_lst->next;
//     }
//     cmd->args[token_count] = NULL;
// }

// static t_token *skip_tokens(t_token *token_lst)
// {
//     while (token_lst && token_lst->type != 1)
//         token_lst = token_lst->next;
//     if (token_lst && token_lst->type == 1)
//         token_lst = token_lst->next;
//     return token_lst;
// }

// static t_cmd_lst *create_cmd_lst(t_token *token_lst)
// {
//     t_cmd_lst *cmd_lst = NULL;
//     t_cmd_lst *current_cmd = NULL;

//     while (token_lst)
//     {
//         t_cmd_lst *new_cmd = initialize_new_cmd();
//         int token_count = count_tokens(token_lst);

//         populate_command(new_cmd, token_lst, token_count);

//         if (!cmd_lst)
//         {
//             cmd_lst = new_cmd;
//         }
//         else
//         {
//             current_cmd->next = new_cmd;
//         }
//         current_cmd = new_cmd;

//         token_lst = skip_tokens(token_lst);
//     }
//     return cmd_lst;
// }

// void create_print_cmd(t_shell *general)
// {
//     // t_cmd_lst *commands = NULL;
//     general->cmd_lst = create_cmd_lst(general->tok_lst);
//     // general->my_cmd = general->cmd_lst;
//     // t_cmd_lst *temp = general->cmd_lst;
//     // while (temp)
//     // {
//     //     printf("Command: %s\n", temp->cmd);
//     //     printf("Arguments:");
//     //     for (int i = 0; temp->args[i]; i++)
//     //     {
//     //         printf("%s ", temp->args[i]);
//     //     }
//     //     printf("\n\n");
//     //     // printf("------------\n");
//     //     temp = temp->next;
//     // }
//     general->pipe_count = pipe_count(general->tok_lst);
//     // printf("pipe = %d\n", general->pipe_count);
//     clean_list(&general->tok_lst);
//     general->tok_lst = NULL;
//     // system("leaks minishell");
//     // free_tok_lst(general->tok_lst);
//     // print_tokens(general -> tok_lst);
// }
