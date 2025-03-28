/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 15:48:26 by marvin            #+#    #+#             */
/*   Updated: 2025/03/27 15:59:46 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./pipex/libft/libft.h"
# include "./pipex/pipex.h"
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

#define MAX_FLAGS 10
#define MAX_ARGS 10
#define MAX_COMMANDS 100
#define MAX_PATH 1024

typedef struct s_env
{
    char *cmd;
    char *flag[MAX_FLAGS];
    char *arg[MAX_ARGS];
    char *path;
    char **env;
} t_env;

typedef struct s_type
{
    char PIPE;
    char ECO; 
    char CD;
    int VALUE;
}               t_type;

typedef struct s_node
{
    char *TYPE;
    void *LEFT;
    void *RIGHT;
}				t_node;

void 	ft_echo(t_env *cmds);
int 	ft_pwd();
void	ft_cd(t_env *cmds);
void    ft_env(t_env *cmds);
void 	ft_exit(t_env *cmds);
void 	ft_unset(t_env *env);
void    ft_export(t_env *env);

#endif