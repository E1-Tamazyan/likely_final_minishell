/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaboya <algaboya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 17:31:52 by algaboya          #+#    #+#             */
/*   Updated: 2024/12/26 18:54:48 by algaboya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int pipe_count(t_token  *tok_lst)
{
    int     i;
    t_token *tmp;

    i = 0;
    tmp = tok_lst;
    while (tmp)
    {
        if (tmp->type == PIPE)
            i++;
        tmp = tmp->next;
    }
    return (i);
}