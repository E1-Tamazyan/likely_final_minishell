/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elen_t13 <elen_t13@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 14:42:32 by etamazya          #+#    #+#             */
/*   Updated: 2025/02/01 14:47:06 by elen_t13         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SUCCESS_EXIT 0
# define FAILURE_EXIT 1
# define EXPORT 1
# define ENV 0
// # include <std.h> // exit(),
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>  // rl_clear_history(), add_history(),
# include <readline/readline.h> // rl_clear_history(), rl_on_new_line(), rl_replace_line(), rl_redisplay(),
# include <signal.h>            //signal(),
# include <stdbool.h>
# include <stdio.h>  // readline(), perror()
# include <stdlib.h> // exit(),
# include <sys/ioctl.h>
# include <sys/resource.h> // (struct rusage *rusage),
# include <sys/stat.h>
# include <sys/wait.h> // wait(), waitpid(), wait3(),
# include <unistd.h>   // fork(), access(),

# define NO_SUCH_FILE_MSG "No such file or directory"
# define PERMISSION_DENIED_MSG "Permission denied"
# define IS_DIRECTORY_MSG "is a directory"
# define NOT_DIRECTORY_MSG "Not a directory"
typedef enum s_ttype
{
	WORD = 0,          // commands and arguments
	PIPE = 1,          // '|'
	REDIR_IN = 2,      // '<'
	REDIR_OUT = 3,     // '>'
	REDIR_APPEND = 4,  // '>>'
	REDIR_HEREDOC = 5, // '<<'
}						t_ttype;

typedef struct s_token
{
	char				*context;
	t_ttype				type;
	struct s_token		*next;
}						t_token;

// typedef struct s_env
// {
// 	char			*key;
// 	char			*value;
// 	struct s_env	*next;
// }					t_env;

typedef struct s_env
{
	char				*key;
	char				*value;
	int					is_print;
	struct s_env		*next;
}						t_env;

typedef struct s_cmd_lst
{
	int					pid;
	char				*cmd;
	char				**args;
	struct s_cmd_lst	*next;
	char				*heredoc;
	char				*red_in;
	char				*red_out;
	char				*red_append;
	int					std_in;
	int					std_out;
}						t_cmd_lst;

// typedef struct s_cmd_lst
// {
// 	char				*cmd;
// 	char				**args;
// 	int					pid;
// 	struct s_cmd_lst	*next;
// 	int		std_in; // fd
// 	int		std_out; // fd
// 	//Gaya's vers.
// 	// char	*pipe;
// 	// char	*redir_in;
// 	// char	*redir_out;
// 	// char	*append_in;
// 	// char	*append_out;
// }			t_cmd_lst;

typedef struct s_dollar
{
	char				*u_key;
	char				*value;
	// int				dollar_sign; // 1 = sgl_quote, 2 = dbl quote
	struct s_dollar		*next;

}						t_dollar;

typedef struct s_shell
{
	t_token				*tok_lst;
	t_env				*env_lst;
	t_cmd_lst			*cmd_lst;
	t_dollar			*doll_lst;
	t_env				*sorted_env_lst;
	t_token				*curr_tok;
	t_cmd_lst			*curr_cmd;
	int (*fd)[2];
	int shlvl; // check
	int					sg_quote;
	int					db_quote;
	int					pipe_index;
	int					pipe_count;
	int					exit_status;
	char				*name;
	int					original_stdin;
	int					original_stdout;
}						t_shell;

void					my_error(char *cmd, char *error, int status);
void					execute_heredoc(t_shell *g, t_cmd_lst *cmd);
int						is_redir(t_ttype type);
t_token					*ft_lst_delone(t_token **lst, t_token *node);
void					list_add_back_cmd(t_cmd_lst **lst, t_cmd_lst *new);
int						heredoc_init(t_shell *g, t_cmd_lst **cmd, t_token *tok);
int						open_redir_2(t_shell *g);
int						open_redir(t_shell *g);
// int			redirs_management(t_shell *g);
void					fill_commands(t_shell *general);
// int			check_fill_commands(t_shell *g, int i, int j);
int						check_fill_commands(t_shell *g);
void					check_heredoc_syntax(t_token *head);
t_cmd_lst				*initialize_new_cmd(void);
int						create_cmd_lst(t_shell *g);

void					ft_strlcpy(char *dest, const char *src, int size,
							int pos, char limiter);
t_env					*ft_lstnew(char *context, int printable);
void					ft_lstadd_back(t_env *lst, t_env *node);
int						ft_strcmp(const char *s1, const char *s2);
int						ft_strlen(const char *str);
char					*my_substr(const char *s, unsigned int start, int len);
int						ft_strchr(const char *s, int c);
char					*ft_strdup(const char *s1);
void					ft_strcpy(char *s1, const char *s2, int start, int len);
void					ft_strcpy_2(char *s1, const char *s2, int start,
							int len);
// void	ft_strcpy_3(char *s1, const char *s2, int start_s1, int start_s2);
// char	*ft_strjoin(char *s1, char *s2);
void					*ft_calloc(size_t count, size_t size);
void					*ft_memset(void *str, int c, size_t n);

void					expand_var(char **input, t_shell *general, int *start,
							int *i);
char					*countcpy_len(char *input, int start, int *l,
							t_shell *general);
int						spec_len(char *input, int start);
int						check_inp_quotes(t_shell *general, char *input, int i,
							int start);

// ***_____main_functions_____***
void					init_general(t_shell *general);
int						init_input(char *input, t_shell *gen);
int						check_cmd(char **env, t_shell *general);
t_env					*init_env_nodes(char **env);

// ***____env_sorting_____***
char					**sort_env(char **env);
void					quick_sort(char **arr, int low, int high);
int						partition(char **arr, int low, int high);
void					swap(char **a, char **b);

// ***_____utils_____***
void					print_env(t_env *new, int flag);
void					print_tokens(t_token *head);
int						put_key(t_env *node, char *src);
void					put_value(t_env *node, char *src, int pos);
int						sgmnt_len(const char *str, int pos);
char					*check_env_var(t_env *env_lst, const char *context);
int						create_env(char **env, t_shell *general);

// ***_____lib utils_____***
void					ft_strlcpy(char *dest, const char *src, int size,
							int pos, char limiter);
// t_env	*ft_lstnew(char *context);
void					ft_lstadd_back(t_env *lst, t_env *node);
int						ft_strcmp(const char *s1, const char *s2);
int						ft_strlen(const char *str);
char					*my_substr(const char *s, unsigned int start, int len);
int						ft_strchr(const char *s, int c);
char					*ft_strdup(const char *s1);
void					ft_strcpy(char *s1, const char *s2, int start, int len);
void					ft_strcpy_2(char *s1, const char *s2, int start,
							int len);
void					ft_strcpy_3(char *s1, const char *s2, int start_s1,
							int start_s2);
char					*ft_strjoin(char *s1, char *s2);

// ***_____tokenization_____***
// short	init_tokens(char *input, t_shell *general, int i);
// int		init_op_token(char *input, int i, t_token **token_list);
// int 	init_op_token(char *input, int *i, t_token **token_list);
int						init_op_token(char *input, int *i,
							t_token **token_list);

void					add_token_list(t_token **list, char *content,
							t_ttype type);
t_token					*create_token(char *content, t_ttype type);

// ** additional
void					printStrings(char **strings);
void					clean_list(t_token **list);
void					clean_env_list(t_env **list);
short					del_t_node(t_token *lst);
int						check_cut_quotes(t_shell *general, char **input, int *i,
							int start);

void					error_msg(int status, char *command_name);

// **************
// int		check_dollar_sign(char *input, int i, t_shell *general);
char					*sgmnt_cpy(char *input, int *i);

// Alla's
void					create_print_cmd(t_shell *general);
int						export_valid(char *arg);
int						pwd_builtin(t_shell *general);
int						echo_builtin(t_shell *general, t_cmd_lst *cmd);
int						cd_builtin(t_shell *general, t_cmd_lst *temp_cmd_lst);
int						export_builtin(t_shell *general, char *command);
void					error_message(char *var);
int						ft_isdigit(int c);
int						ft_isalpha(int c);
t_env					**add_env_lst_var(char *context, t_shell *general,
							int i);
t_env					**add_env_no_var(char *context, t_shell *general);
int						count_lst_len(t_env *env_lst);
char	*str_join(char const *s1, char const *s2); // ft_strjoin => str_join
char					**list_to_array(t_env *env);
size_t					my_strlcpy(char *dst, const char *src, size_t dstsize);
void					free_array(char **arr);
t_env					*my_lstnew(char *key, char *value);
int						print_export(char *new);
t_env					*bubble_sort_lst(t_env *lst);
void					swap_node(t_env *a, t_env *b);
int						change_home(t_shell *general);
char					*get_value(t_shell *general, char *keyik);
int						change_env_value(t_env *lst, char *keyik, char *valik);
int						change_prev_dir(t_shell *general);
int						change_dir(char *dir);
int						unset_builtin(t_shell *general);
int						unset_exp_var(t_shell *general, char *new);
int						delete_exp_node(t_env **lst, t_env *nodik);
void					free_node(t_env *node);
int						exit_builtin(t_shell *general);
int						is_valid(char **args, int count);
long					ft_atol(char *str);
int						count_args(char **args);
int						is_key_valid(t_shell *general, char *key);
int						ft_atoi(const char *str);
char					*ft_itoa(int n);
void					set_shlvl(t_shell *general);
void					incr_shlvl(t_shell *general);

// execution
void					execution(t_shell *general, int index);
void					clean_gen_exit(t_shell *general, int number, int flag,
							int exitik);
int						is_abs_rel_path(char *cmd);
void					ft_putstr_fd(char *s, int fd);
void					mini_error(char *error, int fd);
int						is_directory(const char *path);

// int		exec_cmd(t_shell *general);
int						exec_one_cmd(t_shell *general, t_cmd_lst *tmp_cmd_lst);
int						exec_external_cmds(t_shell *general,
							t_cmd_lst *tmp_cmd_lst);
void					split_and_run(t_shell *general, t_cmd_lst *tmp_cmd_lst);
char					**ft_split(char *s, char c);
void					do_builtin(t_shell *general, t_cmd_lst *tmp_cmd_lst);
int						execute(t_shell *general, t_cmd_lst *tmp_cmd_lst,
							int index);
int						is_builtin(char *cmd);
// free
void					free_cmd_lst(t_cmd_lst **cmd_lst);
void					free_tok_lst(t_token *tok_lst);
void					free_env_lst(t_env *env_lst);
void					free_doll_lst(t_dollar *doll_lst);
void					free_set_null(char *tmp);

// void	fork_and_run(t_shell *general, char *joined);
char					*the_path(char **splitted, char *cmd);
void					do_path_exec(t_shell *general);
// pipe
int						pipe_count(t_token *tok_lst);
int						create_pipe(t_shell *general);
void					close_pipes(int (*fd)[2], int count);
void					close_exit(t_shell *general);
void					duping(t_shell *general, int index);
void					waiting(pid_t pid, int *_status);
int						pipe_fork(t_shell *general, t_cmd_lst *tmp_cmd_lst,
							int index);

// archive
char					*ft_substr(char const *s, unsigned int start, int len);
void					check_malloc(void *str);

// status
void					set_exit_status(int status);
int						get_exit_status(void);
// signal
void					init_signal(int mode);

int						init_tokens_cmds(char *input, t_shell *general, int i);
t_token					*remove_extra_quotes(t_shell *general);
// int 	_management(t_shell *g);
int						open_redir_out(t_shell *general, char *name,
							int append);
int						redir_dups(t_cmd_lst *lst);
int						out_redir(t_cmd_lst *lst);
int						in_redir(t_cmd_lst *lst);
char					*only_for_dol_harcakan(t_shell *general);
int						open_infile(t_shell *general, char *name);
char					*open_dollar(t_shell *general, char *input, int *i,
							int start);

void					print_cmd(t_cmd_lst *cmd_lst);

#endif
