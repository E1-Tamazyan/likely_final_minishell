/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elen_t13 <elen_t13@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 16:35:06 by algaboya          #+#    #+#             */
/*   Updated: 2025/02/01 14:41:04 by elen_t13         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_builtin(t_shell *general, char *command)
{
	int	i;
	int	j;

	// dprintf(2, "export\n");
	j = 1;
	if (ft_strcmp(command, "env") == 0 && !general->cmd_lst->args[1])
		return (print_env(general->sorted_env_lst, 0), EXIT_SUCCESS);
	if (ft_strcmp(command, "export") == 0 && !general->cmd_lst->args[1])
		return (print_env(general->env_lst, 1), EXIT_SUCCESS);
	while (general->cmd_lst->args[j])
	{
		if (export_valid(general->cmd_lst->args[j]) == FAILURE_EXIT)
		{
			if (!general->cmd_lst->args[j + 1])
				return (FAILURE_EXIT);
			else
				j++;
		}
		if (ft_strchr(general->cmd_lst->args[j], '=') >= 0)
		{
			i = ft_strchr(general->cmd_lst->args[j], '=');
			add_env_lst_var(general->cmd_lst->args[j], general, i);
		}
		else
			add_env_no_var(general->cmd_lst->args[j], general);
		j++;
	}
	return (EXIT_SUCCESS);
}

int	export_valid(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isalpha(arg[0]) || ft_isdigit(arg[0]))
		{
			printf("ERROR\n");
			error_message(arg);
			return (FAILURE_EXIT);
		}
		i++;
	}
	return (SUCCESS_EXIT);
}

t_env	**add_env_no_var(char *context, t_shell *general)
{
	t_env	*lol;
	t_env	*tmp;

	tmp = general->env_lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, context) == 0)
		{
			lol = my_lstnew(context, NULL);
			return (NULL);
		}
		tmp = tmp->next;
	}
	lol = my_lstnew(context, NULL);
	ft_lstadd_back(general->env_lst, lol);
	return (EXIT_SUCCESS);
}

t_env	**add_env_lst_var(char *context, t_shell *general, int i)
{
	char	*val;
	char	*key;
	t_env	*tmp;
	t_env	*lol;

	tmp = general->env_lst;
	key = my_substr(context, 0, i);
	val = my_substr(context, i + 1, ft_strlen(context) - i);
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(val);
			lol = my_lstnew(key, val);
			return (NULL);
		}
		tmp = tmp->next;
	}
	lol = my_lstnew(key, val);
	if (!lol)
		return (NULL);
	ft_lstadd_back(general->env_lst, lol);
	ft_lstadd_back(general->sorted_env_lst, lol);
	return (EXIT_SUCCESS);
}

char	**list_to_array(t_env *env)
{
	int		i;
	int		len;
	char	*tmp;
	char	**str;
	t_env	*env_temp;

	len = count_lst_len(env);
	str = (char **)malloc(sizeof(char *) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	env_temp = env;
	while (env_temp)
	{
		tmp = str_join(env_temp->key, "=");
		str[i] = str_join(tmp, env_temp->value);
		free_set_null(tmp);
		if (!str[i])
			return (free_array(str), NULL);
		i++;
		env_temp = env_temp->next;
	}
	str[i] = NULL;
	return (str);
}

int	count_lst_len(t_env *env_lst)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = env_lst;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

// int	is_same_key(t_env *env_lst, char *key)
// {
// t_env	*tmp;

// tmp = env_lst;
// while (tmp)
// {
// 	if (ft_strcmp(tmp->key, key) == 0)
// 		return (0);
// 	tmp = tmp->next;
// }
// 	return (1);
// }

// t_env	** remove_node(t_shell *general, t_env *tmp)
// {
// 	t_env	*temp;

// 	temp = general->env_lst;
// 	while (temp)
// 	{
// 		if (ft_strcmp(temp->key, tmp->key) == 0)
// 		{
// 			free(temp->key);
// 			free(temp->value);
// 			free(temp);
// 			return (NULL);
// 		}
// 		temp = temp->next;
// 	}
// 	return (NULL);
// }
