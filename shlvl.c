/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaboya <algaboya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 22:06:51 by tumolabs          #+#    #+#             */
/*   Updated: 2025/02/01 00:53:03 by algaboya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	j;
	int	val;

	j = 1;
	i = 0;
	val = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			j *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		val = val * 10 + (str[i] - '0');
		i++;
	}
	val *= j;
	return (val);
}

static int	ft_count(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i = 1;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static long	ft_abs(long n)
{
	if (n < 0)
		return (-n);
	else
		return (n);
}

char	*ft_itoa(int n)
{
	int		k;
	long	nbr;
	char	*ptr;

	k = ft_count(n);
	nbr = ft_abs(n);
	ptr = (char *)malloc(sizeof(char) * (k + 1));
	if (!ptr)
		return (NULL);
	ptr[k] = '\0';
	if (n == 0)
	{
		ptr[0] = '0';
		return (ptr);
	}
	if (n < 0)
		ptr[0] = '-';
	while (nbr != 0)
	{
		k--;
		*(ptr + k) = nbr % 10 + '0';
		nbr = nbr / 10;
	}
	return (ptr);
}

void    set_shlvl(t_shell *general)
{
    int shlvl;
    char *lvl;
    
    shlvl = ft_atoi(get_value(general, "SHLVL"));
    if (shlvl < 0)
        shlvl = 0;
    else if (shlvl >= 1000)
        shlvl = 1;
    lvl = ft_itoa(shlvl);
    change_env_value(general->env_lst, "SHLVL", lvl);
    change_env_value(general->sorted_env_lst, "SHLVL", lvl);
}

void    incr_shlvl(t_shell *general)
{
    int shlvl;
    char *lvl;

    shlvl = ft_atoi(get_value(general, "SHLVL"));
    shlvl++;
    lvl = ft_itoa(shlvl);
    change_env_value(general->env_lst, "SHLVL", lvl);
    change_env_value(general->sorted_env_lst, "SHLVL", lvl);
	free(lvl);
}
