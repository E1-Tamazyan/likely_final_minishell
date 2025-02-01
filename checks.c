/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tumolabs <tumolabs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:18:10 by elen_t13          #+#    #+#             */
/*   Updated: 2025/02/01 13:40:51 by tumolabs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ************************
// *** CAUTION *** FULL ***
// ************************
// 4 function

// changed
char *sgmnt_cpy(char *input, int *i)
{
	char *result;
	int j;
	int len;

	len = 0;
	if (input[*i] == '?')
		len++;
	else
	{
		while (input[*i + len] && input[*i + len] != ' ' && input[*i + len] != '$'
		&& input[*i + len] != '"' && input[*i + len] != '\'')
			len++;
	}
	result = (char *)malloc((len + 1) * sizeof(char));
	check_malloc(result);
	j = 0;
	while (input[*i] && input[*i] != ' ' && input[*i] != '$' && input[*i] != '\"'
	 && input[*i] != '\'' && j < len)
	{
		result[j++] = input[*i];
		(*i)++;
	}
	result[j] = '\0';
	return (result);
}
// echo ba"rev $USER$USER jan" vonc es

char *open_dollar(t_shell *general, char *input, int *i, int start)
{
	(void)start;
	if (input[*i] && input[*i] == '$')
	{
		(*i)++;
		general->doll_lst->u_key = sgmnt_cpy(input, i);
		if (!general->doll_lst->u_key[0])
		{
			general->doll_lst->value = (char *)malloc(sizeof(char) * 2);
			check_malloc(general->doll_lst->value);
			general->doll_lst->value[0] = '$';
			general->doll_lst->value[1] = '\0';
		}
		else
			general->doll_lst->value = check_env_var(general->env_lst, general->doll_lst->u_key);
		if (!general->doll_lst->value)
		{
			general->doll_lst->value = (char *)malloc(sizeof(char) * 1);
			check_malloc(general->doll_lst->value);
			general->doll_lst->value[0] = '\0';
		}
	}
	return (general->doll_lst->value);
}

int check_inp_quotes(t_shell *general, char *input, int i, int start)
{
	int flag_sg;
	int flag_db;

	flag_sg = 0;
	flag_db = 0;
	i = start;
	(void)general;
	while (input[i])
	{
		if (input[i] == '\"' && !flag_sg)
			flag_db = !flag_db;
		else if (input[i] == '\'' && !flag_db)
			flag_sg = !flag_sg;
		i++;
	}
	if (flag_db || flag_sg)
		return (printf("Error: Unclosed quotes found in input.\n"), -1);
	return (0);
}
// SIGSEGV
// echo ba"rev $USER' $USERecho ba"rev $USER' $USER 'jan"$USER dff -a | $$

// should make 3 tokens
// echo ba"rev $USER' $USERecho ba"rev
// $USER' $USER 'jan"$USER
// dff -a | $$
