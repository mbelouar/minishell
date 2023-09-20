/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 18:48:31 by mbelouar          #+#    #+#             */
/*   Updated: 2023/09/20 23:06:24 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MINISHELL_H
# define MINISHELL_H

# include <term.h>
# include <curses.h>
# include <termios.h>
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
# include "libft/libft.h"

# define SUCCESS 0
# define FAILURE 1

typedef	struct	s_data
{
	char		**env;
	char		*pwd;
	char		*prev_wd;
	char		*curr_wd;
	int			exit_status;
}				t_data;

void	ft_export(char **args, t_data *data);
void	export_alone(t_data *data);
char	**export_env(char **old_env, char *export);
void	replace_var(char *new_var, t_data *data, int index);
int		var_index(char *name, t_data *data);
int		check_export(char *str);
int		print_export(char **env);
char	**dup_env(char **env);

void	ft_unset(char **args, t_data *data);
char	**delete_env_var(char **old_env, int index);
void	free_env(char **env);

void	ft_echo(char **args);

void	ft_pwd(t_data *data);

void	ft_exit(char **args);

void	ft_env(char **env);
int		envlen(char **env);

void	ft_cd(char **args, t_data *data);
int		cd_path(char **args, t_data *data);
int		cd_alone(t_data *data);
int		cd_minus(t_data *data);
int		change_pwd(t_data *data, char *input);
void	change_env_oldpwd(t_data *data);
void	change_env_pwd(t_data *data);

void	error_sentence(char *str);

#endif
