/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elen_t13 <elen_t13@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 18:28:32 by algaboya          #+#    #+#             */
/*   Updated: 2025/02/01 14:39:19 by elen_t13         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ************************
// *** CAUTION *** FULL ***
// ************************

static size_t	strlcpyk(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strlen((char *)src);
	if (dstsize && dst)
	{
		while (i < dstsize - 1 && src[i] != '\0')
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (j);
}

static int	ft_word_count(char const *s, char c)
{
	int	i;
	int	d_count;

	i = 0;
	d_count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			while (s[i] != c && s[i + 1])
				i++;
			d_count++;
		}
		i++;
	}
	return (d_count);
}

static char	**ft_ptrptr(char *s, char **ptr, char c)
{
	int	i;
	int	let_count;
	int	d_count;

	i = 0;
	d_count = ft_word_count(s, c);
	while (i < d_count)
	{
		let_count = 0;
		while (*s != c && *s)
		{
			let_count++;
			s++;
		}
		if (let_count != 0)
		{
			ptr[i] = (char *)malloc(sizeof(char) * (let_count + 1));
			strlcpyk(ptr[i], s - let_count, let_count + 1);
			i++;
		}
		s++;
	}
	return (ptr);
}

char	**ft_split(char *s, char c)
{
	int		d_count;
	char	**ptr;

	if (!s)
		return (NULL);
	d_count = ft_word_count(s, c);
	ptr = (char **)malloc(sizeof(char *) * (d_count + 1));
	if (!ptr)
		return (NULL);
	ptr[d_count] = NULL;
	return (ft_ptrptr(s, ptr, c));
}

int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "export") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "exit") == 0 || ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "echo") == 0)
		return (1);
	return (0);
}
