/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaboya <algaboya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 18:24:16 by etamazya          #+#    #+#             */
/*   Updated: 2024/12/09 20:06:29 by algaboya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	swap(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int	partition(char **arr, int low, int high)
{
	char	*pivot;
	int		i;
	int		j;

	pivot = arr[high];
	i = low - 1;
	j = low;
	while (j < high)
	{
		if (ft_strcmp(arr[j], pivot) < 0)
		{
			i++;
			swap(&arr[i], &arr[j]);
		}
		j++;
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

void	quick_sort(char **arr, int low, int high)
{
	int	p;

	p = 0;
	if (low < high)
	{
		p = partition(arr, low, high);
		quick_sort(arr, low, p - 1);
		quick_sort(arr, p + 1, high);
	}
}

char	**sort_env(char **env)
{
	int		i;
	int		j;
	char	**env_clone;

	i = 0;
	while (env[i] != NULL)
		i++;
	env_clone = (char **)malloc((i + 1) * sizeof(char *));
	if (!env_clone)
		return (NULL);
	j = 0;
	while (j < i)
	{
		env_clone[j] = ft_strdup(env[j]);
		if (!env_clone[j])
		{
			while (j > 0)
				free(env_clone[--j]);
			free(env_clone);
			return (NULL);
		}
		j++;
	}
	env_clone[i] = (NULL);
	quick_sort(env_clone, 0, i - 1);
	return (env_clone);
}

// if will be need for the previous (sort_env) function to make clone for env param
// char **clone_env(char **env)
// {
//     int i;
//     int j;
//      
//     i = 0;
//     j = 0;
//     while (env[i])
//         i++;
//     char **clone = malloc((i + 1) * sizeof(char *));
//     if (!clone)
//         return NULL;
//     while (j < i)
//     {
//         clone[j] = strdup(env[j]);
//         if (!clone[j])
//         {
//             while (j > 0)
//                 free(clone[--j]);
//             free(clone);
//             return NULL;
//         }
//      j++;
//     }
//     clone[i] = NULL;
//     return clone;
// }

// char **sort_env(char **env)
// {
//     char **clone = clone_env(env);
//     if (!clone)
//         return NULL;
//     quick_sort(clone, 0, i - 1);
//     return (clone);
// }