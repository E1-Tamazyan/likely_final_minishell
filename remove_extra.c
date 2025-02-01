/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_extra.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaboya <algaboya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 22:48:10 by algaboya          #+#    #+#             */
/*   Updated: 2025/01/26 22:48:22 by algaboya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *remove_quoted_positions(char *str, int *indexes, int index_count, int len)
{
	int i;
	int j;
	char *res;
	int skip;
	int k;

	res = malloc(len - index_count + 1);
	check_malloc(res);
	i = 0;
	j = 0;
	while (i < len)
	{
		skip = 0;
		k = 0;
		while (k < index_count)
		{
			if (indexes[k] == i)
			{
				skip = 1;
				break;
			}
			k++;
		}
		if (!skip)
			res[j++] = str[i];
		i++;
	}
	res[j] = '\0';
	free(str);
	return (res);
}


static char *remove_outer_quotes(t_shell *general, char *str, int i, int i_c)
{
	int len;
	int *indexes;

	len = ft_strlen(str);
	indexes = ft_calloc(len, sizeof(int));
	check_malloc(indexes);
	while (str[i])
	{
		if (!general->sg_quote && str[i] == '\"')
		{
			general->db_quote = !general->db_quote;
			indexes[i_c++] = i;
		}
		else if (!general->db_quote && str[i] == '\'')
		{
			general->sg_quote = !general->sg_quote;
			indexes[i_c++] = i;
		}
		i++;
	}
	str = remove_quoted_positions(str, indexes, i_c, len);
	if (!str)
		return (free(indexes), NULL);
	return (free(indexes), str);
}


t_token *remove_extra_quotes(t_shell *general)
{
	t_token *head;

	head = general->tok_lst;
	general->db_quote = 0;
	general->sg_quote = 0;
	while (general->tok_lst != NULL)
	{
		general->tok_lst->context = remove_outer_quotes(general, general->tok_lst->context, 0, 0);
		// printf("Token context after removing quotes: -->%s<--\n", general->tok_lst->context);
		general->tok_lst = general->tok_lst->next;
	}
	general->tok_lst = head;
	return (general->tok_lst);
}
