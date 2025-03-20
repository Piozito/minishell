/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 15:48:26 by marvin            #+#    #+#             */
/*   Updated: 2025/03/20 16:53:33 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
# include "./pipex/libft/libft.h"
# include "./pipex/pipex.h"

#define MAX_PATH 1024

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

void ft_echo(char **args);
int ft_pwd();
int ft_cd (char *path);

#endif