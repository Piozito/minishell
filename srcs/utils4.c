/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:39:09 by fragarc2          #+#    #+#             */
/*   Updated: 2025/05/20 17:01:48 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	check_errors(t_env *cmds)
{
	t_env	*temp;

	temp = cmds;
	while (temp)
	{
		temp->path = my_get_path(temp);
		if (temp->path == NULL)
			command_not_found(cmds->cmd);
		temp = temp->next;
	}
}

char	*ft_strstr(const char *big, const char *little)
{
	size_t	i;
	size_t	j;

	if (*little == '\0')
		return ((char *)big);
	if (*big == '\0')
		return (NULL);
	i = 0;
	while (big[i])
	{
		j = 0;
		while (big[i + j] == little[j] && little[j])
			j++;
		if (little[j] == '\0')
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}

void command_not_found(char *cmd)
{
	write(2, "command not found: \"", 20);
	ft_putstr_fd(cmd, 2);
	write(2, "\"\n", 2);
}

int executable_check(t_env *cmds)
{
	int i = 0;
	if(!cmds->cmd)
	{
		if(ft_strncmp(cmds->arg[0], ">", 1) == 0 || ft_strncmp(cmds->arg[1], "<", 1) == 0)
		{
			apply_fd(cmds);
		}
		return 1;
	}
	while(cmds->cmd[i])
	{
		if(ft_isalpha(cmds->cmd[i]) == 1)
			return 0;
		i++;
	}
	return 1;
}

char *get_file(const char *s, size_t *index)
{
    char *res = NULL;
	size_t i;
    size_t start;
	size_t length;

	i = -1;
	size_t j = *index;
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
    while (++i < length)
        res[i] = s[start + i];
    res[length] = '\0';
	if(res[0] == '\0')
		return NULL;
    return res;
}
