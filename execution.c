/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tumolabs <tumolabs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 17:25:43 by algaboya          #+#    #+#             */
/*   Updated: 2025/02/01 14:31:13 by tumolabs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

void	set_exit_status(int status)
{
	g_exit_status = status;
}

int	get_exit_status(void)
{
	return (g_exit_status);
}

void free_fd_array(int (*fd)[2]) {
    if (fd)
    {
        free(fd);
        fd = NULL;
    }
}

void    execution(t_shell *general, int index)
{
    int         i;
    t_cmd_lst   *new;
    t_cmd_lst   *tmp_cmd_lst;
    
    new  = general->cmd_lst;
    tmp_cmd_lst = general->cmd_lst;
    if (general->cmd_lst == NULL)
        return ;
    if (general->pipe_count > 0)
    {
        index = pipe_fork(general, tmp_cmd_lst, index);
	    i = 0;
	    while (i < index && new)
	    {
	    	waiting(new->pid, &g_exit_status);
            new = new->next;
	    	i++;
	    }
    }
    else
        set_exit_status(exec_one_cmd(general, tmp_cmd_lst));
}

int    pipe_fork(t_shell *general, t_cmd_lst *tmp_cmd_lst, int index)
{
    int         i;

    i = 0;
    create_pipe(general);
    while (i < (general->pipe_count + 1))
    {
        execute(general, tmp_cmd_lst, index);
        index++;
        tmp_cmd_lst = tmp_cmd_lst->next;
        i++;
    }
    close_pipes(general->fd, general->pipe_count);
    // free_array(general->fd); //clean tomorrow
    return (index);
}

void	waiting(pid_t pid, int *_status)
{
	waitpid(pid, _status, 0);
	if (WIFSIGNALED(*_status))
	{
		*_status = WTERMSIG(*_status) + 128;
		if (*_status == 131)
			write(1, "Quit: 3\n", 9);
		return (set_exit_status(*_status));
	}
	set_exit_status(WEXITSTATUS(*_status));
}

int    exec_one_cmd(t_shell *general, t_cmd_lst *tmp_cmd_lst)
{
    int status;
    if (tmp_cmd_lst->cmd && is_builtin(tmp_cmd_lst->cmd))
	{

		redir_dups(tmp_cmd_lst);
        do_builtin(general, tmp_cmd_lst);
		dup2(general -> original_stdin, STDIN_FILENO);
		dup2(general -> original_stdout, STDOUT_FILENO);
	}
    else
    {
        init_signal(2);
        general->cmd_lst->pid = fork();
        if (general->cmd_lst->pid == 0)
        {
        	if (redir_dups(tmp_cmd_lst) >= 0)
           		set_exit_status(exec_external_cmds(general, general->cmd_lst));
            clean_gen_exit(general, 1, get_exit_status(), 1);
        }
        else if (general->cmd_lst->pid > 0)
            waiting(general->cmd_lst->pid, &status);
        else
            perror("fork");
    }
    // printf("smth\n");
    return (get_exit_status());
}

void    do_builtin(t_shell *general, t_cmd_lst *tmp_cmd_lst)
{
    (void)tmp_cmd_lst;
    if (ft_strcmp((const char *)tmp_cmd_lst->cmd, "export") == 0)
    	set_exit_status(export_builtin(general, tmp_cmd_lst));
    else if (ft_strcmp((const char *)tmp_cmd_lst->cmd, "env") == 0)
    	set_exit_status(export_builtin(general, tmp_cmd_lst));
    else if (ft_strcmp((const char *)tmp_cmd_lst->cmd, "cd") == 0)
    	set_exit_status(cd_builtin(general, tmp_cmd_lst));
    else if (ft_strcmp((const char *)tmp_cmd_lst->cmd, "unset") == 0)
	    set_exit_status(unset_builtin(general));
	else if (ft_strcmp((const char *)tmp_cmd_lst->cmd, "exit") == 0)
	    set_exit_status(exit_builtin(general));
    else if (ft_strcmp((const char *)tmp_cmd_lst->cmd, "pwd") == 0)
		set_exit_status(pwd_builtin(general));
    else if (ft_strcmp((const char *)tmp_cmd_lst->cmd, "echo") == 0)
		set_exit_status(echo_builtin(general, tmp_cmd_lst));
}

// void __attribute__((constructor)) foo(){
//     printf("%d\n", getpid());
// }

int execute(t_shell *general, t_cmd_lst *tmp_cmd_lst, int index)
{
    init_signal(2);
    tmp_cmd_lst->pid = fork();

    if (tmp_cmd_lst->pid == 0)
    {
		//printf("cmd -> name %s\n", tmp_cmd_lst -> args[1]);
        duping(general, index);
        if (redir_dups(tmp_cmd_lst) < 0)
			clean_gen_exit(general, get_exit_status(), 0, 1);
        if (tmp_cmd_lst->cmd && is_builtin(tmp_cmd_lst->cmd))
        {
            do_builtin(general, tmp_cmd_lst);
            clean_gen_exit(general, get_exit_status(), 0, 1);
        }
        set_exit_status(exec_external_cmds(general, tmp_cmd_lst));
          printf("stat = %d\n", get_exit_status());

    }
    if (index > 0)
        close(general->fd[index - 1][0]);
    if (index < general->pipe_count)
        close(general->fd[index][1]);
    return (EXIT_SUCCESS);
}

void    duping(t_shell *general, int index)
{
    if (index == 0)
    {
        if (dup2(general->fd[0][1], STDOUT_FILENO) == -1)
            close_exit(general);
    }
    else if (index == general->pipe_count)
    {
        if (dup2(general->fd[index - 1][0], STDIN_FILENO) == -1)
            close_exit(general);
    }
    else
    {
        if (dup2(general->fd[index][1], STDOUT_FILENO) == -1)
            close_exit(general);
        if (dup2(general->fd[index - 1][0], STDIN_FILENO) == -1)
            close_exit(general);
    }
    close_pipes(general->fd, general->pipe_count);
    return ;
}

int exec_external_cmds(t_shell *general, t_cmd_lst *tmp_cmd_lst)
{
	if (!tmp_cmd_lst->cmd)
		clean_gen_exit(general, get_exit_status(), 0, 1);
    if (is_abs_rel_path(tmp_cmd_lst->cmd))
     {

          do_path_exec(general);
        //   return (get_exit_status());
     }
    else
    {
        split_and_run(general, tmp_cmd_lst);
        return (get_exit_status());
    }
    return (get_exit_status());
}

void    split_and_run(t_shell *general, t_cmd_lst *tmp_cmd_lst)
{
    char    *path;
    char    **env;
    char    **splitted;
    path = getenv("PATH");
    splitted = ft_split(path, ':');
    path = the_path(splitted, tmp_cmd_lst->cmd);
    free_array(splitted);
    if (path == NULL)
    {
        //mini_error(tmp_cmd_lst->cmd, 2);
		error_msg(127, tmp_cmd_lst->cmd);
        // general->exit_status = 1;
        free_set_null(path);
        free_cmd_lst(&general->cmd_lst);
        // free_fd_array(general->fd);
        clean_gen_exit(general, 127, 1, 1);
    }
    env = list_to_array(general->sorted_env_lst);
    execve(path, tmp_cmd_lst->args, env);
    free_array(env);
    env = NULL;
    free_set_null(path);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write (fd, s, ft_strlen(s));
}

int	is_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (false);
	return (S_ISDIR(path_stat.st_mode));
}

void do_path_exec(t_shell *general)
{
    if (is_directory(general->cmd_lst->cmd))
    {
        my_error(NULL, "Is a directory", 126);
        // free_cmd_lst(&general->cmd_lst);
        // general->cmd_lst = NULL;
        clean_gen_exit(general, 126, 0, 1);
	}
    if (access(general->cmd_lst->cmd, F_OK) == 0)
    {
        if (access(general->cmd_lst->cmd, X_OK) == 0)
        {
            if (execve(general->cmd_lst->cmd, general->cmd_lst->args,
                list_to_array(general->sorted_env_lst)) == -1)
            {
                my_error(NULL, "No such file or directory", 127);
                clean_gen_exit(general, 127, 1, 1);
            }
        }
        else
        {
            my_error(NULL, "Permission denied", 126);
            clean_gen_exit(general, 126, 1, 0);
        }
    }
    else
    {
        my_error(NULL, "No such file or directory", 127);
        clean_gen_exit(general, 127, 1, 1);
    }
}

