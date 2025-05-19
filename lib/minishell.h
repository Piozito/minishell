/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 12:00:49 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/05/19 15:11:48 by aaleixo-         ###   ########.fr       */
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
	int				exit_status;
	struct s_env	*next;
	int				fd;
	int				heredoc;
	int 			saved_stdout;
	int 			saved_stdin;
}				t_env;

int	ft_echo(t_env *cmds);
int	ft_pwd(t_env *cmds);
int	ft_cd(t_env *cmds);
int	ft_env(t_env *cmds);
int	ft_exit(t_env *cmds);
int	ft_unset(t_env *env);
int	ft_export(t_env *env);
int	ft_exec(t_env *command);
int parsing(t_env *cmd, const char *input);
void	ft_free_tab(char **tab);
void	initialize_cmd(t_env *cmd, t_env *new_cmd, int i);
char	*my_get_path(t_env *cmds);
void	pipes_handler(t_env *cmds, const char *input);
int	ft_pipe(t_env *cmds);
int	check_builtin(t_env *cmds);
char **ft_split_quotes(t_env *cmd, const char *s, char delimiter, int del);
char **pipe_check(t_env *cmds, const char *input);
void	ft_debug(t_env *cmd);
char	**deep_copy_environ();
int apply_fd(t_env *cmds);
int	pop(t_env *cmds, int i);
int		cmd_check(t_env *cmds);
void ft_expand_variable(t_env *cmd, const char *src, int *index, char **dst, int *i);
void check_errors(t_env *cmds);
char	*ft_strstr(const char *big, const char *little);
void general_error(char *str, int free, int ex, t_env *cmds);
char *ft_find_closing_quote(const char *str, int start, char quote);
void command_not_found(char *cmd);
char *env_expander(t_env *cmds, char *var_name);
int check_heredoc(t_env *cmds, const char *s, int *index);
void free_env(char **array, char **env);
int executable_check(char *cmd);
void export_print(t_env *env);
int is_chr(const char *str, int c);
void ex_refresh(t_env *env, int i);
char **update_env(char *arg, char **env);
char **new_env_maker(char **env, int j, char *arg);
int handle_parent(pid_t pid, t_env *command);
void execute_child(char *path, char **exec_args, t_env *command);
void duping(t_env *cmds);

#endif
