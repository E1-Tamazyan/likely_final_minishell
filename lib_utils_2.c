/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elen_t13 <elen_t13@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:14:51 by etamazya          #+#    #+#             */
/*   Updated: 2025/02/01 14:44:16 by elen_t13         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 4 function

size_t	my_strlcpy(char *dst, const char *src, size_t dstsize)
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

// char	*ft_strjoin(char *s1, char *s2)
// {
// 	char	*res;
// 	size_t	len;
// 	size_t	i;
// 	size_t	j;

// 	len = ft_strlen(s1) + ft_strlen(s2);
// 	res = (char *)malloc((len + 1) * sizeof(char));
// 	if (!res)
// 		return (NULL);
// 	i = 0;
// 	while (s1 && s1[i])
// 	{
// 		res[i] = s1[i];
// 		i++;
// 	}
// 	j = 0;
// 	while (s2 && s2[j])
// 		res[i++] = s2[j++];
// 	res[i] = '\0';
// 	free(s1);
// 	return (res);
// }

char	*str_join(char const *s1, char const *s2)
{
	char	*ptr;

	if (!s1 || !s2)
		return (NULL);
	ptr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	check_malloc(ptr);
	my_strlcpy(ptr, s1, ft_strlen(s1) + 1);
	my_strlcpy(ptr + ft_strlen(s1), s2, (ft_strlen(s2) + 1));
	ptr[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	return (ptr);
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

void	ft_strcpy(char *s1, const char *s2, int start, int len)
{
	int	i;

	i = 0;
	// printf("len = %d\n", len);
	while (s2[start] && i < len)
	{
		s1[i] = s2[start];
		// printf("1_%c, 1_%c\n", s1[ i], s2[start]);
		i++;
		start++;
		// len--;
	}
}
void	ft_strcpy_2(char *s1, const char *s2, int start, int len)
{
	int	i;

	i = 0;
	// printf("****%d\n", len);
	// printf("len = %d\n", len);
	while (s2[i] && i < len)
	{
		s1[start] = s2[i];
		// printf("2_%c, 2_%c\n", s1[start], s2[i]);
		i++;
		start++;
	}
}

void	ft_strcpy_3(char *s1, const char *s2, int start_s1, int start_s2)
{
	while (s2[start_s2])
	{
		s1[start_s1] = s2[start_s2];
		start_s1++;
		start_s2++;
	}
	s1[start_s1] = s2[start_s2];
}

char	*ft_strjoin(char *s1, char *s2)
{
	char *res;
	size_t len;
	size_t i;
	size_t j;

	len = ft_strlen(s1) + ft_strlen(s2);
	res = (char *)malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
		res[i++] = s2[j++];
	res[i] = '\0';
	// free(s1);
	return (res);
}