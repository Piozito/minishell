/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fragarc2 <fragarc2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 12:00:49 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/05/22 15:46:30 by fragarc2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <X11/keysym.h>
# include <X11/X.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>

typedef struct s_env
{
	char			*cmd;
	char			**arg;
	char			*path;
	char			**env;
	char			**exp;
	int				fd;
	int				heredoc;
	int 			saved_stdout;
	int 			saved_stdin;
	int				exit_status;
	struct s_env	*next;
}				t_env;

int		ft_cd(t_env *cmds);
int		fd_error(char *str);
int		ft_pwd(t_env *cmds);
int		ft_env(t_env *cmds);
int		ft_pipe(t_env *cmds);
int		ft_exit(t_env *cmds);
int		ft_echo(t_env *cmds);
int		ft_unset(t_env *env);
int		ft_export(t_env *env);
int		apply_fd(t_env *cmds);
int		cmd_check(t_env *cmds);
int		ft_exec(t_env *command);
int		pop(t_env *cmds, int i);
int		apply_heredoc(t_env *cmds);
int		check_builtin(t_env *cmds);
int		executable_check(t_env *cmds);
int		is_chr(const char *str, int c);
int		parsing(t_env *cmd, const char *input);
int		wait_for_it(pid_t last_pid);
int		handle_parent(pid_t pid, t_env *command);
int		check_heredoc(t_env *cmds, const char *s, size_t *index);
char	*my_get_path(t_env *cmds);
char	**deep_copy_environ(char **environ);
char	**update_env(char *arg, char **env);
char	*get_file(const char *s, size_t *index);
char	*env_expander(t_env *cmds, char *var_name);
char	**pipe_check(t_env *cmds, const char *input);
char	**new_env_maker(char **env, int j, char *arg);
char	*ft_strrealloc(char *result, size_t *size_ptr);
char	*ft_strstr(const char *big, const char *little);
char	*expand_string_variables(t_env *cmd, const char *input);
char	*ft_find_closing_quote(const char *str, int start, char quote);
char	**ft_split_quotes(t_env *cmd, const char *s, char delimiter, int del);
void	duping(t_env *cmds);
void	ft_debug(t_env *cmd);
void	create_pipe(int p_fd[2]);
void	export_print(t_env *env);
void	check_errors(t_env *cmds);
void	command_not_found(char *cmd);
void	ex_refresh(t_env *env, int i);
void	free_subtokens(char **subtokens);
void	remove_args(char **args, int pos);
void	free_env(char **array, char **env);
void	expand_variables(t_env *cmd, char **result);
void	pipes_handler(t_env *cmds, const char *input);
void	pipo(t_env *cmd, int num_cmds, pid_t last_pid);
void	handle_parent_process(int p_fd[2], int *prev_fd);
void	initialize_cmd(t_env *cmd, t_env *new_cmd, int i);
void	general_error(char *str, int free, int ex, t_env *cmds);
void	execute_child(char *path, char **exec_args, t_env *command);
pid_t	handle_child_process(t_env *cmds, int prev_fd, int p_fd[2], int is_last);

#endif
