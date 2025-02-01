/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utils_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaboya <algaboya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:37:23 by etamazya          #+#    #+#             */
/*   Updated: 2025/01/26 23:33:44 by algaboya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_remove_list(t_token *prev, t_token *current)
{
	if (prev)
		prev->next = current->next;
	if (current->context)
		free(current->context);
	free(current);
}

t_token	*ft_lst_delone(t_token **lst, t_token *node)
{
	t_token	*current;
	t_token	*prev;

	if (!lst || !*lst || !node)
		return (NULL);
	if (*lst == node)
	{
		current = (*lst)->next;
		free((*lst)->context);
		free(*lst);
		*lst = current;
		return (current);
	}
	prev = NULL;
	current = *lst;
	while (current && current != node)
	{
		prev = current;
		current = current->next;
	}
	if (current == node)
		ft_remove_list(prev, current);
	return (prev->next);
}
void	list_add_back_cmd(t_cmd_lst **lst, t_cmd_lst *new)
{
	t_cmd_lst	*add;

	add = *lst;
	if (!new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		while (add->next != NULL)
			add = add->next;
		add->next = new;
		new->next = NULL;
	}
}