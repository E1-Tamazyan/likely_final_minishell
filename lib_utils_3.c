/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utils_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elen_t13 <elen_t13@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:04:59 by elen_t13          #+#    #+#             */
/*   Updated: 2025/02/01 14:44:22 by elen_t13         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isalnum(int arg)
{
	if ((arg >= 48 && arg <= 57) || (arg >= 65 && arg <= 90) || (arg > 96
			&& arg < 123))
		return (1);
	else
		return (0);
}
void	*ft_memset(void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*str1;

	str1 = (unsigned char *)str;
	i = 0;
	while (i < n)
	{
		str1[i] = c;
		i++;
	}
	return (str1);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*str;

	if ((count != 0 && size > 65536) || (size != 0 && count > 65536))
		return (NULL);
	str = malloc(count * size);
	if (!str)
		return (NULL);
	str = ft_memset(str, '\0', count * size);
	return (str);
}

t_env	*ft_lstnew(char *context, int printable) // contains blabla = blabla=bla
{
	int pos;
	t_env *node;

	node = malloc(sizeof(t_env));
	check_malloc(node);
	pos = put_key(node, context);
	put_value(node, context, pos);
	node->is_print = printable;
	node->next = NULL;
	return (node);
}
