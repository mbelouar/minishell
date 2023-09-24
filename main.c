/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:02:30 by mbelouar          #+#    #+#             */
/*   Updated: 2023/09/24 06:34:08 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	end_of_file(t_data *data)
{
	free_env(data->env);
	free(data->pwd);
	ft_putstr_fd("exit\n", 2);
	exit(EXIT_SUCCESS);
}

void	data_init(t_data *data, char **env)
{
	data->env = dup_env(env);
	data->pwd = getcwd(NULL, 0); //
	data->exit_status = 0;
}

void print_arr(char **arr)
{
	for(int i = 0; arr[i]; i++)
		printf("arr[%d]: %s\n", i, arr[i]);
}

void	create_lst(t_data *data, char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		t_list	*new_node = ft_lstnew(arr[i]);
		ft_lstadd_back(&data->lst, ft_lstnew(arr[i]));
		i++;
	}
}

void print_lst(t_list *head) {
    t_list *current = head;
    while (current != NULL) {
        printf("%s\n", current->content);
        current = current->next;
    }
}

int	ft_token_size(t_tokenizer *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

int	check_pipe(t_tokenizer *lst)
{
	t_tokenizer	*curr;

	curr = lst;
	while (curr)
	{
		if (curr->content[0] == '|')
			return (1);
		curr = curr->next;
	}
	return (0);
}

#define MAX_PATH_LENGTH 4096

char *get_absolute_path(const char *command_name) {
    char *path_env = getenv("PATH");
    if (path_env == NULL) {
        fprintf(stderr, "PATH environment variable is not set\n");
        return NULL;
    }

    char *path_copy = strdup(path_env);
    if (path_copy == NULL) {
        perror("Memory allocation failed");
        return NULL;
    }

    char *path = path_copy;
    char *token;
    char *result = NULL;

    while ((token = strsep(&path, ":")) != NULL) {
        char absolute_path[MAX_PATH_LENGTH];
        snprintf(absolute_path, sizeof(absolute_path), "%s/%s", token, command_name);

        if (access(absolute_path, X_OK) == 0) {
            result = strdup(absolute_path);
            break ;
        }
    }
	free(path_copy);
    return result;
}

void	setup_redirections(t_tokenizer *head)
{
	t_tokenizer	*curr;

	curr = head;
	while (curr && curr->type != PIPE)
	{
		if (curr->type == RED_OUT_TRUNC)
		{
			int fd = open(curr->content, O_RDWR | O_CREAT | O_TRUNC , 0644);
			dup2(fd, STDOUT_FILENO);
		}
		else if (curr->type == RED_OUT_APPEND)
		{
			int fd = open(curr->content, O_RDWR | O_CREAT | O_APPEND , 0644);
			dup2(fd, STDOUT_FILENO);
		}
		else if (curr->type == RED_IN)
		{
			if (access(curr->content, F_OK) == 0)
			{
				int fd = open(curr->content, O_RDONLY);
				dup2(fd, STDIN_FILENO);
			}
			else
			{
				dprintf(2, "minishell: %s: No such file or directory\n", curr->content);
				exit(EXIT_FAILURE);
			}
		}
		curr = curr->next;
	}
}

void	execute_simple_cmd(t_data *data)
{
	t_tokenizer	*curr;
	// add function that retreive the asbsolute path of the command
	char	**cmd;
	char 	*cmd_name = NULL;

	curr = data->tokenizer;
	// cmd = ft_split(curr->content, ' ');
	// if (builtin_check(cmd[0]))
		// exec_builtin();
	// else
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("error:");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		setup_redirections(data->tokenizer);
		while (curr)
		{
			// if (curr->type == RED_OUT_TRUNC)
			// {
			// 	int fd = open(curr->content, O_RDWR | O_CREAT | O_TRUNC , 0644);
			// 	dup2(fd, STDOUT_FILENO);
			// }
			// else if (curr->type == RED_OUT_APPEND)
			// {
			// 	int fd = open(curr->content, O_RDWR | O_CREAT | O_APPEND , 0644);
			// 	dup2(fd, STDOUT_FILENO);
			// }
			// else if (curr->type == RED_IN)
			// {
			// 	if (access(curr->content, F_OK) == 0)
			// 	{
			// 		int fd = open(curr->content, O_RDONLY);
			// 		dup2(fd, STDIN_FILENO);
			// 	}
			// 	else
			// 	{
			// 		dprintf(2, "minishell: %s: No such file or directory\n", curr->content);
			// 		exit(EXIT_FAILURE);
			// 	}
			// }
			if (curr->type == CMD)
			{
				cmd = ft_split(curr->content, ' ');
				cmd_name = get_absolute_path(cmd[0]);
			}
			curr = curr->next;
		}
		if (cmd_name)
		{
			execve(cmd_name, cmd, data->env);
			perror("");
			exit(EXIT_FAILURE);
		}
		dprintf(2, "minishell: %s: command not found\n", cmd[0]);
		exit(127); // to be changed
	}
	else
	{
		waitpid(pid, 0, 0);
	}
}

int	count_cmds(t_tokenizer *lst)
{
	t_tokenizer	*curr;
	int			i;

	curr = lst;
	i = 0;
	while (curr)
	{
		if (curr->type == CMD)
			i++;
		curr = curr->next;
	}
	return (i);
}

void	execute_compound_command(t_data *data)
{
	int	i;
	int	nb;
	int	pipe_fd[2];
	int	prev_in;
	pid_t	pid;
	char	**cmd;
	char 	*cmd_name = NULL;

	i = 0;
	prev_in = 0;
	nb = count_cmds(data->tokenizer);
	t_tokenizer	*curr;
	curr = data->tokenizer;
	while (i < nb)
	{
		while (curr && curr->type != PIPE)
		{
			if (curr->type == CMD)
			{
				cmd = ft_split(curr->content, ' ');
				cmd_name = get_absolute_path(cmd[0]);
				break ;
			}
			curr = curr->next;
		}
		if (i != (nb - 1))
		{
			curr = curr->next->next;
			pipe(pipe_fd);
		}
		pid = fork();
		if (pid < 0)
		{
			perror("error:");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			dup2(prev_in, STDIN_FILENO);
			close(pipe_fd[0]);
			if (i != (nb - 1))
			{
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[1]);
			}
			if (i == 0)
				setup_redirections(data->tokenizer);
			else
				setup_redirections(curr);
			printf("cmd_name: %s\n", cmd_name);
			execve(cmd_name, cmd, data->env);
			perror("error: ");
			exit(EXIT_FAILURE);
		}
		else
		{
			if (i == (nb - 1))
				waitpid(pid, 0, 0);
			if (prev_in)
				close(prev_in);
			prev_in = dup(pipe_fd[0]);
			close(pipe_fd[0]);
			close(pipe_fd[1]);
		}
		i++;
	}
}

void	execute(t_data *data)
{
	if (check_pipe(data->tokenizer) == 0)
		execute_simple_cmd(data);
	else
		execute_compound_command(data);
}

int		main(int ac, char **av, char **env)
{
	t_data	data;
	char*		line;

	(void)ac;
	(void)av;
	data_init(&data, env);
	if (!data.env)
		exit(EXIT_FAILURE);
	while (1)
	{
		line = readline("> ");
		if (!line)
			end_of_file(&data);
		char	**tmp = ft_split(line, ' ');
		if (!tmp)
			continue;
		if (ft_strcmp(tmp[0], "echo") == 0)
			ft_echo(tmp);
		if (ft_strcmp(tmp[0], "export") == 0)
			ft_export(tmp, &data);
		if (ft_strcmp(tmp[0], "unset") == 0)
			ft_unset(tmp, &data);
		if (ft_strcmp(tmp[0], "env") == 0)
			ft_env(data.env);
		if (ft_strcmp(tmp[0], "pwd") == 0)
			ft_pwd(&data);
		if (ft_strcmp(tmp[0], "exit") == 0)
			ft_exit(tmp);
		if (ft_strcmp(tmp[0], "cd") == 0)
			ft_cd(tmp, &data);
		create_lst(&data, tmp);
		// print_lst(data.lst);
		tokenizer(&data);

		// printList(data.tokenizer);
		execute(&data);
		free_token_list(&data.tokenizer);
		ft_lstclear(&data.lst);
		// is_builtin();
			// builtin();
		// for (int i = 0; tmp[i]; i++)
		// 	printf("%s\n", tmp[i]);
		// else
		// 	struct = parser_start(&data);
		// 	execute(struct);
	}
	return (0);
}
