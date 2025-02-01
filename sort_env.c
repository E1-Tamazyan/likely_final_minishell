/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elen_t13 <elen_t13@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 18:24:16 by etamazya          #+#    #+#             */
/*   Updated: 2025/02/01 14:48:43 by elen_t13         ###   ########.fr       */
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
