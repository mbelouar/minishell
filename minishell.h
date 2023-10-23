/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 18:48:31 by mbelouar          #+#    #+#             */
/*   Updated: 2023/10/23 16:33:45 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>

# define SUCCESS 0
# define FAILURE 1
# define MAX_PATH_LENGTH 4096

typedef struct s_tokenizer	t_tokenizer;
typedef struct s_n			t_n;

int							g_status;

enum						e_type
{
	CMD,
	BUILTIN,
	PIPE,
	RED_OUT_TRUNC,
	RED_OUT_APPEND,
	RED_IN,
	HEREDOC
};

typedef enum e_type			t_type;

struct						s_tokenizer
{
	char					*content;
	t_type					type;
	t_tokenizer				*next;
};

typedef struct s_data
{
	int						exit_status;
	char					**env;
	char					*pwd;
	t_list					*lst;
	t_tokenizer				*tokenizer;
}							t_data;

typedef struct s_pipe
{
	int						pipe_fd[2];
	int						prev_in;
	int						pid;
	int						cmd_nb;
	char					**cmd;
	char					*cmd_name;
}							t_pipe;

typedef struct s_norm
{
	int						i;
	t_pipe					p;
	t_tokenizer				*curr;
	int						*child_pids;
}							t_norm;

struct						s_n
{
	char					*content;
	char					*str;
	char					**tmp;
	char					*test;
};

char						*ft_remove_quotes(char *s);
void						ft_export(char **args, t_data *data);
void						export_alone(t_data *data);
char						**export_env(char **old_env, char *export);
void						replace_var(char *new_var, t_data *data, int index);
void						exp_and_check(t_data *data, char **args, int *i);
int							var_index(char *name, t_data *data);
int							check_export(char *str);
int							print_export(char **env);
char						**dup_env(char **env);

void						ft_unset(char **args, t_data *data);
char						**delete_env_var(char **old_env, int index);
void						free_env(char **env);

void						ft_echo(char **args);

void						ft_pwd(t_data *data);

void						ft_exit(char **args, t_data *data);

void						ft_env(char **env);
int							envlen(char **env);

void						ft_cd(char **args, t_data *data);
char						*ft_getenv(char **env, char *to_get);
int							cd_path(char **args, t_data *data);
int							cd_alone(t_data *data);
int							cd_minus(t_data *data);
int							change_pwd(t_data *data, char *input);
void						change_env_oldpwd(t_data *data);
void						change_env_pwd(t_data *data);

int							analylizer(t_list *list);
int							check_quotes(char *line);

t_tokenizer					*new_node(char *content, t_type type);
void						printEnumName(enum e_type value);
void						printList(t_tokenizer *head);
void						ft_create_node(t_tokenizer **head, char *content,
								t_type type);
void						ft_redirection(t_list *curr_node, t_data *data);
void						tokenizer(t_data *data);
void						free_token_list(t_tokenizer **head);
int							builtin_check(char *cmd);
void						free_double_pointer(char **arr);

int							builtin_check(char *cmd);
void						execute(t_data *data);
void						execute_compound_command(t_data *data);
void						exec_in_child(t_pipe p, t_data *data);
void						execute_simple_cmd(t_data *data);
void						execute_external_cmd(t_data *data, int save_fd[2]);
void						execute_builtin_cmd(t_data *data, int save_fd[2]);
void						setup_redirections(t_data *data, t_tokenizer *head);
char						*get_absolute_path(char *command_name, t_data *da);
void						check_dir(char *command_name, t_data *data);
char						*search_in_path(char *cmd_name, char *path_copy);
char						*get_path_environment(t_data *data);
int							check_pipe(t_tokenizer *lst);
int							count_cmds(t_tokenizer *lst);
void						exec_builtin(char **cmd, t_data *data);

void						setup_pipes(int *p1, int *p2, int i, int cmd_nbr);
void						setup_nchild_pipes(int *p1, int *p2, int i);
void						close_all_pipes(int *p1, int *p2);
void						exec_cmd(t_data *data, char **cmd, char *cmd_name);
void						child_exec(t_data *data, t_pipe p, int i,
								t_tokenizer *curr);
void						parent_exec(t_pipe p, int i);
void						free_pipe_struct(t_pipe *p);

void						ft_red_out_trunc(t_tokenizer *head);
void						ft_red_out_append(t_tokenizer *head);
void						ft_red_in(t_data *data, t_tokenizer *head);

void						err_msg(t_data *data, char *str, int status);
void						ft_cmd_not_found(char *str);
void						perror_exec(void);
void						perror_fork(void);

void						ft_heredoc(t_data *data, char *delimiter);
void						check_heredoc(char *expanded, char *line, int fd[2],
								int quotes);
void						signal_handler(int signum);
void						signal_heredoc(int signum);
int							has_quotes(char *delimiter);

void						expand(t_data *data);
void						ft_get_len(t_list *token, char *data, char **env);
int							get_str_len(char *data, char **env);
char						*get_expand(t_data *data, char *content,
								char **env);
void						ft_mini_expen(t_list *token, char **env);
char						*get_new_string(t_data *data, int len,
								char *content, char **env);
void						ft_help_get_str(t_data *q, char *g, t_list *h,
								char **e);
void						ft_go(t_list *token, char *content);
char						*ft_free_new_str(t_list *s);
int							ft_hundling(t_data *d, t_list *s, char *data,
								char *string);
char						*get_var(char *id, char **env);
char						*get_index(char *string);
int							ft_valid(char c);

void						process_line(t_data *data, char *line, char **tmp);
void						free_resources(t_data *data, char *line);
char						*ft_readline(t_data *data);
void						ft_syntax_err(t_data *data, char *line,
								t_list *lst);
void						ft_quotes_err(t_data *data, char *line);
void						end_of_file(t_data *data);
void						data_init(t_data *data, char **env);
void						create_lst(t_data *data, char **arr);
int							ft_token_size(t_tokenizer *lst);

#endif
