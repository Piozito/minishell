/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:32:29 by marvin            #+#    #+#             */
/*   Updated: 2025/04/22 15:32:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void remove_args(char **args, int pos)
{
    int j = pos;
    while (args[j + 2])
    {
        args[j] = args[j + 2];
        j++;
    }
    args[j] = NULL;
    args[j + 1] = NULL;
}

int handle_fd_input(char *file)
{
	if(ft_strchr(file, '<') || ft_strchr(file, '>'))
        return -1;
    int fd_in = open(file, O_RDONLY);
    if (fd_in == -1)
        return -1;
    if (dup2(fd_in, 0) == -1)
    {
        close(fd_in);
        return -1;
    }
    close(fd_in);
    return 0;
}

int handle_fd_output(char *file)
{
	if(ft_strchr(file, '<') || ft_strchr(file, '>'))
        return -1;
    int fd_out = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd_out == -1)
        return -1;
    if (dup2(fd_out, 1) == -1)
    {
        close(fd_out);
        return -1;
    }
    close(fd_out);
    return 0;
}

int handle_fd_output_append(char *file)
{
	if(ft_strchr(file, '<') || ft_strchr(file, '>'))
        return -1;
    int fd_out = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (fd_out == -1)
        return -1;
    if (dup2(fd_out, 1) == -1)
    {
        close(fd_out);
        return -1;
    }
    close(fd_out);
    return 0;
}

int ft_counter(char *line, int c)
{
	int i = 0;
	int counter = 0;
	if(line[i])
	{
		if(line[i] == c)
			counter++;
		i++;
	}
	return counter;
}

char *concatenate_strings(char **strings)
{
    if (strings == NULL)
        return NULL;
    size_t total_length = 0;
    size_t i = 0;
    while (strings[i] != NULL)
    {
        total_length += ft_strlen(strings[i]);
        i++;
    }
    char *result = (char *)malloc(total_length + 1);
    if (result == NULL)
        return NULL;
    result[0] = '\0';
    i = 0;
    while (strings[i] != NULL)
    {
        ft_strlcat(result, strings[i], total_length + 1);
        i++;
    }
    return result;
}

int handle_fd_input_heredoc(t_env *cmds, char *word)
{
    int fds[2];
    char *line;
    char *expanded_line;
    char **str;

    if (cmds->heredoc != -1)
	{
        close(cmds->heredoc);
        cmds->heredoc = -1;
    }
    if (pipe(fds) == -1)
        return -1;
    while (1)
    {
        expanded_line = NULL;
        str = NULL;
        line = readline("> ");
        if (!line || ft_strcmp(line, word) == 0)
        {
            free(line);
            free(word);
            break;
        }
        str = ft_split_quotes(cmds, line, 27, 0);
        expanded_line = concatenate_strings(str);
        if(!expanded_line)
            expanded_line = ft_strdup(line);
        ft_putstr_fd(expanded_line, fds[1]);
        write(fds[1], "\n", 1);
        free(line);
        free(str);
        free(expanded_line);
    }
    close(fds[1]);
    cmds->heredoc = fds[0];
    return 0;
}

char *get_file(const char *s, int *index)
{
    char *res = NULL;
	int i;
    int start;
	int length;

	i = 0;
	int j = *index;
	j++;
	if(s[j] == '>' || s[j] == '<')
		j++;
    while (s[j] == ' ' || s[j] == '\t')
        j++;
    start = j;
    while (s[j] && s[j] != ' ' && s[j] != '\t' && s[j] != '\'' && s[j] != '\"')
        j++;
    length = j - start;
    res = (char *)malloc((length + 1) * sizeof(char));
    if (!res)
        return NULL;
    while (i < length)
	{
        res[i] = s[start + i];
		i++;
	}
    res[length] = '\0';
	if(res[0] == '\0')
		return NULL;
    return res;
}

int fd_error(char *str)
{
	ft_putstr_fd(str, 2);
	write(2, " redirection error.", 19);
	write(2, "\n", 1);
	return 1;
}

int check_heredoc(t_env *cmds, const char *s, int *index)
{
	(void)cmds;
	char *word;
	if (s[*index] == '<' && s[*index + 1] == '<')
	{
		if(s[*index + 2] && s[*index + 2] != '<')
		{
			word = get_file(s, index);
			if(!word)
				return (fd_error("heredoc"));
			if(ft_strchr(word, '<') || ft_strchr(word, '>'))
				return (fd_error("heredoc"));
			if (handle_fd_input_heredoc(cmds, word) == -1)
				return (fd_error("heredoc"));
		}
		else
			return (fd_error("heredoc"));
	}
	return 0;
}

int apply_heredoc(t_env *cmds)
{
    if (cmds->heredoc != -1)
	{
        if (dup2(cmds->heredoc, 0) == -1) {
            close(cmds->heredoc);
            cmds->heredoc = -1;
            return -1;
        }
        close(cmds->heredoc);
        cmds->heredoc = -1;
    }
    return 0;
}

int apply_fd(t_env *cmds)
{
    int i = 0;
	if (cmds->heredoc != -1)
        apply_heredoc(cmds);
    while (cmds->arg[i])
    {
		if ((ft_strncmp(cmds->arg[i], "<", 2) == 0 ||
		ft_strncmp(cmds->arg[i], ">", 2) == 0 ||
		ft_strncmp(cmds->arg[i], ">>", 3) == 0 ||
		ft_strncmp(cmds->arg[i], "<<", 3) == 0) && cmds->arg[i + 1])
        {
			if (ft_strncmp(cmds->arg[i], ">>", 3) == 0)
            {
				if (handle_fd_output_append(cmds->arg[i + 1]) == -1)
				return (fd_error("append"));
            }
            else if (ft_strncmp(cmds->arg[i], "<", 2) == 0)
            {
				if (handle_fd_input(cmds->arg[i + 1]) == -1)
				return (fd_error("input"));
            }
            else if (ft_strncmp(cmds->arg[i], ">", 2) == 0)
            {
				if (handle_fd_output(cmds->arg[i + 1]) == -1)
				return (fd_error("output"));
			}
			remove_args(cmds->arg, i);
		}
		else
		i++;
    }
	
    return 0;
}
