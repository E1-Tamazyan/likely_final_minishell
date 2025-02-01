/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elen_t13 <elen_t13@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 16:11:43 by etamazya          #+#    #+#             */
/*   Updated: 2025/02/01 14:44:12 by elen_t13         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//  5 functions

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		// printf("str[i] = %c\n", str[i]);
		i++;
	}
	return (i);
}

char	*my_substr(const char *s, unsigned int start, int len)
{
	int		i;
	char	*ptr;

	if (!s)
		return (NULL);
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	ptr = malloc(sizeof(char) * (len + 1));
	check_malloc(ptr);
	// if (!ptr)
	// 	return (NULL);
	i = 0;
	while (len)
	{
		ptr[i] = s[start];
		i++;
		start++;
		len--;
	}
	ptr[i] = '\0';
	return (ptr);
}

int	ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != (char)c)
		i++;
	if (s[i] == (char)c)
		return (i);
	else
		return (-1);
}

char	*ft_substr(char const *s, unsigned int start, int len)
{
	char			*sub;
	int				count;
	unsigned int	i;

	count = (unsigned int)ft_strlen(s);
	if (!s)
		return (NULL);
	if (start >= (unsigned int)count)
		len = 0;
	if (len > count)
		sub = (char *)malloc(count);
	else
		sub = (char *)malloc(len + 1);
	check_malloc(sub);
	i = 0;
	while (i < (unsigned int)len && s[start] != '\0')
	{
		sub[i] = s[start];
		i++;
		start++;
	}
	sub[i] = '\0';
	return (sub);
}

char	*ft_strdup(const char *s1)
{
	size_t i;
	char *s1_dup;

	i = 0;
	s1_dup = (char *)malloc(ft_strlen(s1) + 1);
	check_malloc(s1_dup);
	// write(1,"DUP\n",4);
	while (s1[i] != '\0')
	{
		s1_dup[i] = s1[i];
		i++;
	}
	s1_dup[i] = '\0';
	// printf("ft_strdup, s1_dup = %s, s1[0] = %c\n", s1_dup, s1_dup[0]);
	return ((char *)s1_dup);
}