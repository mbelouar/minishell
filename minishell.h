/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 18:48:31 by mbelouar          #+#    #+#             */
/*   Updated: 2023/10/15 20:42:31 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <term.h>
# include <curses.h>
# include <termios.h>
# include <dirent.h>
# include <stdint.h>
# include <sys/ioctl.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <signal.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include <fcntl.h>

# define SUCCESS 0
# define FAILURE 1
# define MAX_PATH_LENGTH 4096

typedef struct s_tokenizer	t_tokenizer;
typedef enum e_type			t_type;

enum	e_type
{
	CMD,
	BUILTIN,
	PIPE,
	RED_OUT_TRUNC,
	RED_OUT_APPEND,
	RED_IN,
	HEREDOC
};

int	g_status;

struct	s_tokenizer
{
	char		*content;
	t_type		type;
	t_tokenizer	*next;
};

typedef struct s_data
{
	char			**env;
	char			*pwd;
	t_list			*lst;
	t_tokenizer		*tokenizer;
}				t_data;

typedef struct s_pipe
{
	int		pipe_fd[2];
	int		prev_in;
	int		pid;
	int		cmd_nb;
	char	**cmd;
	char	*cmd_name;
}				t_pipe;

void		ft_export(char **args, t_data *data);
void		export_alone(t_data *data);
char		**export_env(char **old_env, char *export);
void		replace_var(char *new_var, t_data *data, int index);
void		exp_and_check(t_data *data, char **args, int *i);
int			var_index(char *name, t_data *data);
int			check_export(char *str);
int			print_export(char **env);
char		**dup_env(char **env);

void		ft_unset(char **args, t_data *data);
char		**delete_env_var(char **old_env, int index);
void		free_env(char **env);

void		ft_echo(char **args);

void		ft_pwd(t_data *data);

void		ft_exit(char **args);

void		ft_env(char **env);
int			envlen(char **env);

void		ft_cd(char **args, t_data *data);
int			cd_path(char **args, t_data *data);
int			cd_alone(t_data *data);
int			cd_minus(t_data *data);
int			change_pwd(t_data *data, char *input);
void		change_env_oldpwd(t_data *data);
void		change_env_pwd(t_data *data);


int			analylizer(t_list *list);
int			check_quotes(char *line);

t_tokenizer	*new_node(char *content, t_type type);
void		printEnumName(enum e_type value);
void		printList(t_tokenizer *head);
void		ft_create_node(t_tokenizer **head, char *content, t_type type);
void		ft_redirection(t_list *curr_node, t_data *data);
void		tokenizer(t_data *data);
void		free_token_list(t_tokenizer **head);
int			builtin_check(char *cmd);
void		free_double_pointer(char **arr);

void		execute(t_data *data);
void		execute_compound_command(t_data *data);
void		exec_in_child(t_pipe p, t_data *data);
void		execute_simple_cmd(t_data *data);
void		execute_external_cmd(t_data *data, int save_fd[2]);
void		execute_builtin_cmd(t_data *data, int save_fd[2]);
void		setup_redirections(t_tokenizer *head);
char		*get_absolute_path( char *command_name, t_data *da);
int			check_pipe(t_tokenizer *lst);
int			count_cmds(t_tokenizer *lst);
void		exec_builtin(char **cmd, t_data *data);

void		setup_pipes(int *p1, int *p2, int i, int cmd_nbr);
void		setup_nchild_pipes(int *p1, int *p2, int i);
void		close_all_pipes(int *p1, int *p2);
void		exec_cmd(t_data *data, char **cmd, char *cmd_name);
void		child_exec(t_data *data, t_pipe p, int i, t_tokenizer *curr);
void		parent_exec(t_pipe p, int i);

void		ft_red_out_trunc(t_tokenizer *head);
void		ft_red_out_append(t_tokenizer *head);
void		ft_red_in(t_tokenizer *head);

void		error_sentence(char *str);
void		ft_cmd_not_found(char *str);
void		perror_exec(void);
void		perror_fork(void);

void		ft_heredoc(char *delimiter);
void		signal_handler(int signum);
void		signal_heredoc(int signum);

#endif
