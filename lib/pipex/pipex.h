/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:29:52 by marvin            #+#    #+#             */
/*   Updated: 2025/03/24 12:28:25 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

#include "./libft/libft.h"
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

void    ft_free_tab(char **tab);
char    *my_getenv(char *cmd, char **env);
char    *get_path(char *cmd, char **env);
int     open_file(char *file, int read);
void    exit_handler(int n_exit);


#endif
