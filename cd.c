/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elen_t13 <elen_t13@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 20:33:37 by algaboya          #+#    #+#             */
/*   Updated: 2025/02/01 14:36:20 by elen_t13         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_error(char *cmd, char *error, int status)
{
	set_exit_status(status);
	ft_putstr_fd("minisHell: ", 2);
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
}

int	cd_builtin(t_shell *general, t_cmd_lst *temp_cmd_lst)
{
	int		status;
	char	*cwd;
	char	*newCWD;

	cwd = getcwd(NULL, 0);
	status = SUCCESS_EXIT;
	if (count_args(temp_cmd_lst->args) >= 2)
		return (my_error("cd", "too many arguments", EXIT_FAILURE),
			EXIT_FAILURE);
	if (!temp_cmd_lst->args[1])
		status = change_home(general);
	else if (temp_cmd_lst->args[1] && ft_strcmp(temp_cmd_lst->args[1],
			"-") == 0)
		status = change_prev_dir(general);
	else if (temp_cmd_lst->args[1])
		status = change_dir(temp_cmd_lst->args[1]);
	newCWD = getcwd(NULL, 0);
	if (!newCWD)
	{
		free_set_null(cwd);
		return (perror("cd: "), FAILURE_EXIT);
	}
	change_env_value(general->env_lst, "PWD", newCWD);
	change_env_value(general->sorted_env_lst, "PWD", newCWD);
	change_env_value(general->env_lst, "OLDPWD", cwd);
	change_env_value(general->sorted_env_lst, "OLDPWD", cwd);
	free_set_null(cwd);
	return (status);
}

int	change_dir(char *dir)
{
	int	status;

	status = chdir(dir);
	if (status != 0)
	{
		printf(" cd: %s: No such file or directory\n", dir);
		return (FAILURE_EXIT);
	}
	return (EXIT_SUCCESS);
}

int	change_home(t_shell *general)
{
	char	*home;

	home = get_value(general, "HOME");
	if (!home)
		return (write(STDERR_FILENO, "HOME is not set",
				ft_strlen("HOME is not set")));
	else if (chdir(home) < 0)
	{
		perror("cd: ");
		return (errno);
	}
	return (EXIT_SUCCESS);
}

int	change_prev_dir(t_shell *general)
{
	char	*prev;
	char	*msg;

	prev = get_value(general, "OLDPWD");
	if (!prev)
		return (perror("minisHell: cd: OLDPWD not set\n"), FAILURE_EXIT);
	else if (chdir(prev) < 0)
	{
		msg = strerror(errno);
		return (write(STDERR_FILENO, msg, ft_strlen(msg)));
	}
	return (EXIT_SUCCESS);
}

char	*get_value(t_shell *general, char *keyik)
{
	t_env	*tmp;

	tmp = general->env_lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, keyik) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

int	change_env_value(t_env *lst, char *keyik, char *valik)
{
	t_env	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, keyik) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(valik);
			if (!tmp->value)
				return (FAILURE_EXIT);
			return (EXIT_SUCCESS);
		}
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}

// int	cd_builtin(t_shell *general)
// {
// 	int	status;

// 	status = SUCCESS_EXIT;
// 	if (!general->cmd_lst->args[1])
// 		status = change_home(general);
// 	else if (general->cmd_lst->args[1]
// 		&& ft_strcmp(general->cmd_lst->args[1], "-") == 0)
// 		status = change_prev_dir(general);
// 	else if (general->cmd_lst->args[1])
// 		status = change_dir(general, general->cmd_lst->args[1]);
// 	return (status);
// }

// int	change_dir(t_shell *general, char *dir)
// {
// 	char	*cwd;
// 	char	*prev;
// 	int		status;

// 	cwd = getcwd(NULL, 0);
// 	status = chdir(dir);
// 	if (status != 0)
// 	{
// 		printf(" cd: %s: No such file or directory\n", dir);
// 		free_set_null(cwd);
// 		return (FAILURE_EXIT);
// 	}
// 	prev = getcwd(NULL, 0);
// 	change_env_value(general->env_lst, "PWD", prev);
// 	change_env_value(general->sorted_env_lst, "PWD", prev);
// 	change_env_value(general->env_lst, "OLDPWD", cwd);
// 	change_env_value(general->sorted_env_lst, "OLDPWD", cwd);
// 	free_set_null(cwd);
// 	free_set_null(prev);
// 	return (EXIT_SUCCESS);
// }

// int	change_home(t_shell *general)
// {
// 	char	*home;
// 	int		status;
// 	char	*cwd;

// 	cwd = getcwd(NULL, 0);
// 	home = get_value(general, "HOME");
// 	status = chdir(home);
// 	if (status != 0)
// 	{
// 		printf(" cd: %s: No such file or directory", home);
// 		free_set_null(cwd);
// 		free_set_null(home);
// 		return (FAILURE_EXIT);
// 	}
// 	change_env_value(general->env_lst, "PWD", home);
// 	change_env_value(general->sorted_env_lst, "PWD", home);
// 	change_env_value(general->env_lst, "OLDPWD", cwd);
// 	change_env_value(general->sorted_env_lst, "OLDPWD", cwd);
// 	free_set_null(cwd);
// 	free_set_null(home);
// 	return (EXIT_SUCCESS);
// }

// int	change_prev_dir(t_shell *general)
// {
// 	int		status;
// 	char	*cwd;
// 	char	*prev;

// 	cwd = getcwd(NULL, 0);
// 	prev = get_value(general, "OLDPWD");
// 	status = chdir(prev);
// 	if (!prev)
// 		return (printf("minisHell: cd: OLDPWD not set\n"), FAILURE_EXIT);
// 	if (status != 0)
// 	{
// 		free_set_null(cwd);
// 		printf(" cd: %s: No such file or directory", prev);
// 		return (FAILURE_EXIT);
// 	}
// 	change_env_value(general->env_lst, "PWD", prev);
// 	change_env_value(general->sorted_env_lst, "PWD", prev);
// 	change_env_value(general->env_lst, "OLDPWD", cwd);
// 	change_env_value(general->sorted_env_lst, "OLDPWD", cwd);
// 	free_set_null(cwd);
// 	return (EXIT_SUCCESS);
// }

// char	*get_value(t_shell *general, char *keyik)
// {
// 	t_env	*tmp;

// 	tmp = general->env_lst;
// 	while (tmp)
// 	{
// 		if (ft_strcmp(tmp->key, keyik) == 0)
// 			return (tmp->value);
// 		tmp = tmp->next;
// 	}
// 	return (NULL);
// }

// int	change_env_value(t_env *lst, char *keyik, char *valik)
// {
// 	t_env	*tmp;

// 	tmp = lst;
// 	while (tmp)
// 	{
// 		if (ft_strcmp(tmp->key, keyik) == 0)
// 		{
// 			free(tmp->value);
// 			tmp->value = ft_strdup(valik);
// 			if (!tmp->value)
// 				return (FAILURE_EXIT);
// 			return (EXIT_SUCCESS);
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (EXIT_SUCCESS);
// }
