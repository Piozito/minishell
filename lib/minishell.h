/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 12:00:49 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/06/09 15:52:51 by aaleixo-         ###   ########.fr       */
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
	int				heredoc;
	int				saved_stds[2];
	int				exit_status;
	struct s_env	*prev;
	struct s_env	*next;
}				t_env;

int		ft_cd(t_env *cmds);
int		fd_error(char *str);
int		ft_pwd(t_env *cmds);
int		ft_env(t_env *cmds);
int		is_valid(char *str);
int		ft_pipe(t_env *cmds);
int		ft_exit(t_env *cmds);
int		ft_echo(t_env *cmds);
int		ft_unset(t_env *env);
int		ft_export(t_env *env);
int		apply_fd(t_env *cmds);
int		ft_clear(t_env *cmds);
int		cmd_check(t_env *cmds);
int		env_tester(t_env *cmd);
int		ft_exec(t_env *command);
int		pop(t_env *cmds, int i);
int		check_heredoc(t_env *cmds);
int		apply_heredoc(t_env *cmds);
int		check_builtin(t_env *cmds);
int		wait_for_it(pid_t last_pid);
int		check_redirs(char **result);
int		executable_check(t_env *cmds);
int		is_chr(const char *str, int c);
int		word_count_m(const char *s, char c);
int		parsing(t_env *cmd, const char *input);
int		handle_parent(pid_t pid, t_env *command);
int		arg_counter(char **subtokens, int *command_set);
int		var_quote(const char *input, size_t *i, int quote);
int		is_separator(char ch, char c, int quote, int dquote);
int		general_error(char *str, int free, int ex, t_env *cmds);
int		handle_quote(const char *s, size_t *index, int *quote_flag);
int		check_break(const char *s, size_t idx, char quote, char del);
int		extract_helper(char **result, size_t *allocated_size, size_t i);
int		word_count_helper(const char *s, size_t *i, int *quote, char c);
int		extract_helper(char **result, size_t *allocated_size, size_t i);
int		extract_help(const char *s, size_t *index, char del, char *quote);
int		handle_redir(const char *s, size_t *index, char *result, size_t *i);
char	**fake_env_creator(void);
char	*my_get_path(t_env *cmds);
char	*get_file(t_env *cmds, size_t i);
char	**deep_copy_environ(char **environ);
char	**update_env(char *arg, char **env);
char	*concatenate_strings(char **strings);
char	*hc_expand(t_env *cmd, const char *input);
char	*var_getter(const char *input, size_t *i);
char	*env_expander(t_env *cmds, char *var_name);
char	**pipe_check(t_env *cmds, const char *input);
char	**new_env_maker(char **env, int j, char *arg);
char	*ft_strrealloc(char *result, size_t *size_ptr);
char	*ft_strstr(const char *big, const char *little);
char	*extract_word(const char *s, size_t *index, char del);
char	*expand_string_variables(t_env *cmd, const char *input);
char	*var_expander(const char *input, size_t *i, t_env *cmd);
char	**ft_split_quotes(t_env *cmd, const char *s, char delimiter);
char	*ft_find_closing_quote(const char *str, int start, char quote);
void	duping(t_env *cmds);
void	ft_handler(int sig);
void	ft_fake_handler(int sig);
void	export_print(t_env *env);
void	ft_noint_handler(int sig);
void	malloc_fail(char **tokens);
void	command_not_found(t_env *cmds);
void	ex_refresh(t_env *env, int i);
void	free_subtokens(char **subtokens);
void	ft_cmds_free(t_env *cmds, int ex);
void	remove_args(char **args, int pos);
void	ft_putenv(t_env *cmds, char *var);
void	free_env(char **array, char **env);
void	remove_closed_quotes(char **result);
void	expand_variables(t_env *cmd, char **result);
void	pipes_handler(t_env *cmds, const char *input);
void	quotes(const char *s, size_t idx, char *quote);
void	pipo(t_env *cmd, int num_cmds, pid_t *last_pid);
void	handle_parent_process(int p_fd[2], int *prev_fd);
void	initialize_cmd(t_env *cmd, t_env *new_cmd, int i);
void	command_finder(char **subtokens, int *command_set);
void	set_args(t_env *cmd, char **subtokens, int command_set);
void	check_shlvl(char **new_environ, char **environ, int count);
void	var_joiner(char *exp, char **res, size_t *cap, size_t *len);
void	execute_child(char *path, char **exec_args, t_env *command);
void	hc_expline(const char *input, size_t *cap, char **res, t_env *cmd);
pid_t	handle_child(t_env *cmds, int prev_fd, int p_fd[2], int is_last);

#endif