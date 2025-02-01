/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tumolabs <tumolabs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:45:48 by etamazya          #+#    #+#             */
/*   Updated: 2025/02/01 14:07:53 by tumolabs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ************************
// *** WARNING *** FULL ***
// ************************
// **5 functions already **

// t_env	*ft_lstnew(char *context) // contains blabla = blabla=bla
// {
// 	int	pos;
// 	t_env	*node;

// 	node = malloc(sizeof(t_env));
// 	check_malloc(node);
// 	pos = put_key(node, context);	
// 	put_value(node, context, pos);
// 	node -> next = NULL;
// 	return (node);
// }

t_env	*my_lstnew(char *key, char *value) // contains blabla = blabla=bla
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	check_malloc(node);
	node->key = key;
	node->value = value;
	node -> next = NULL;
	return (node);
}

void	ft_lstadd_back(t_env *lst, t_env *node)
{
	t_env	*current;

	if (!node)
		return ;
	if (!lst)
	{
		lst = node;
		return ;
	}
	current = lst;
	// printf("mine_env %s%s\n", node->key, node->value);
	while (current -> next)
		current = current -> next;
	// printf("%s\n", current->key);
	// printf("%s\n", current->value);
	// printf("%s\n", node->key);
	// printf("%s\n", node->value);
	current->next = node;
}

void	ft_strlcpy(char *dest, const char *src, int size, int pos, char limiter)
{
	int	i;

	i = 0;
	while (i < size && src[pos] && src[pos] != limiter)
	{
		dest[i] = src[pos];
		i++;
		pos++;
	}
	dest[i] = '\0';
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;
	int		res;

	i = 0;
	while ((s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
		{
			res = (int)(unsigned char)s1[i] - (int)(unsigned char)s2[i];
			return (res);
		}
		i++;	
	}
	return (0);
}

// int	ft_isalnum(int i)
// {
// 	if ((i >= '0' && i <= '9') || (i >= 'a' && i <= 'z')
// 		|| (i >= 'A' && i <= 'Z'))
// 		return (1);
// 	return (0);
// }