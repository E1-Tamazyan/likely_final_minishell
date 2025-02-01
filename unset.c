/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tumolabs <tumolabs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 19:32:50 by algaboya          #+#    #+#             */
/*   Updated: 2025/02/01 14:46:45 by tumolabs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// full 5

// FIRST
int	unset_builtin(t_shell *general)
{
	char	**new_args;
	int		i;

	i = 1;
	new_args = general->cmd_lst->args;
	if (!new_args[1])
		return (EXIT_SUCCESS);
	while (new_args[i])
	{
		if (is_key_valid(general, new_args[i]))
			return (EXIT_SUCCESS);
		else
			return(unset_exp_var(general, new_args[i]));
		i++;
	}
	return (EXIT_SUCCESS);
}

int	is_key_valid(t_shell *general,char *key)
{
	t_env	*tmp;

	tmp = general->env_lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (EXIT_SUCCESS);
		tmp = tmp->next;
	}
	return(FAILURE_EXIT);
}

int	unset_exp_var(t_shell *general, char *new)
{
	t_env	*tmp;

	tmp = general->env_lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, new) == 0)
			return (delete_exp_node(&general->env_lst, tmp));
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}

int	delete_exp_node(t_env **lst, t_env *nodik)
{
	t_env	*prev;
	t_env	*tmp;

	prev = NULL;
	tmp = *lst;
	if (*lst == nodik)
	{
		tmp = (*lst)->next;
		free_node(*lst);
		return (EXIT_SUCCESS);
	}
	while (tmp)
	{
		if (tmp == nodik)
		{
			prev->next = tmp->next;
			free_node(tmp);
			return (EXIT_SUCCESS);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}

void	free_node(t_env *node)
{
	if (node->key)
	{
		free(node->key);
		node->key = NULL;
	}
	if (node->value)
	{
		free(node->value);
		node->value = NULL;
	}
	free(node);
	node = NULL;
}

// echo <"./test_files/infile" <missing <"./test_files/infile"
// wrong exit status