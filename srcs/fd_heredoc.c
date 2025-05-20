/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fragarc2 <fragarc2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:07:44 by fragarc2          #+#    #+#             */
/*   Updated: 2025/05/20 15:40:43 by fragarc2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

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

void heredoctor(char *word, int *fds,  t_env *cmds)
{
	char *expanded_line;
	char **str;
	char *line;

	while(1)
	{
	    expanded_line = NULL;
        str = NULL;
        line = readline("> ");
        if (!line || ft_strcmp(line, word) == 0)
        {
            free(line);
            free(word);
			return ;
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
}

int handle_fd_input_heredoc(t_env *cmds, char *word)
{
    int fds[2];

    if (cmds->heredoc != -1)
	{
        close(cmds->heredoc);
        cmds->heredoc = -1;
    }
    if (pipe(fds) == -1)
        return -1;
    heredoctor( word, fds, cmds);
    close(fds[1]);
    cmds->heredoc = fds[0];
    return 0;
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
