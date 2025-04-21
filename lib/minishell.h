/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 12:00:49 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/04/21 12:07:34 by aaleixo-         ###   ########.fr       */
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
	char			**flag;
	char			**arg;
	char			*path;
	char			**env;
	char			**exp;
	struct s_env	*next;
}				t_env;

void	ft_echo(t_env *cmds);
void	ft_pwd(t_env *cmds);
void	ft_cd(t_env *cmds);
void	ft_env(t_env *cmds);
void	ft_exit(t_env *cmds);
void	ft_unset(t_env *env);
void	ft_export(t_env *env);
void	ft_exec(t_env *command);
void	parsing(t_env *cmd, const char *input);
void	ft_free_tab(char **tab);
void	initialize_cmd(t_env *cmd);
char	*my_get_path(char *cmd);
void	pipes_handler(t_env *cmds, const char *input);
void	ft_pipe(t_env *cmds);
void	check_builtin(t_env *cmds);
void	apply_redirections(t_env *cmds);
char	**ft_split_quotes(char const *s, char c, int del);
char **pipe_check(const char *input);
void ft_debug(t_env *cmd);

#endif
