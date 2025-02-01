/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elen_t13 <elen_t13@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 20:21:20 by algaboya          #+#    #+#             */
/*   Updated: 2025/02/01 14:43:03 by elen_t13         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_lst(t_cmd_lst **cmd_lst)
{
	t_cmd_lst	*temp;
	int			i;

	if (!cmd_lst || !*cmd_lst)
		return ;
	while (*cmd_lst)
	{
		temp = *cmd_lst;
		i = 0;
		// free(temp->cmd);
		free_set_null(temp->cmd);
		if (temp->args)
		{
			while (temp->args[i])
			{
				// free(temp->args[i]);
				// temp->args[i] = NULL;
				free_set_null(temp->args[i]);
				i++;
			}
			free(temp->args);
			temp->args = NULL;
		}
		free(temp);
		temp = NULL;
		*cmd_lst = (*cmd_lst)->next;
	}
	*cmd_lst = NULL;
}

void	free_tok_lst(t_token *tok_lst)
{
	t_token	*tmp;

	while (tok_lst)
	{
		tmp = tok_lst;
		if (tmp->context)
		{
			free(tmp->context);
			tmp->context = NULL;
		}
		free(tmp);
		tok_lst = tok_lst->next;
		write(1, "FREE TOK\n", 9);
	}
	free(tok_lst);
	tok_lst = NULL;
}

void	free_env_lst(t_env *env_lst)
{
	t_env	*temp;

	while (env_lst)
	{
		temp = env_lst->next;
		if (env_lst->key)
		{
			free(env_lst->key);
			env_lst->key = NULL;
		}
		if (env_lst->value)
		{
			free(env_lst->value);
			env_lst->value = NULL;
		}
		free(env_lst);
		env_lst = temp;
	}
	free(env_lst);
	env_lst = NULL;
}

void	free_doll_lst(t_dollar *doll_lst)
{
	t_dollar	*tmp;

	tmp = doll_lst;
	while (doll_lst)
	{
		tmp = doll_lst->next;
		free(doll_lst->u_key);
		doll_lst->u_key = NULL;
		free(doll_lst->value);
		doll_lst->value = NULL;
		free(doll_lst);
		doll_lst = tmp;
	}
	free(doll_lst);
	doll_lst = NULL;
}

void	free_set_null(char *tmp)
{
	free(tmp);
	tmp = NULL;
}
