/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:47:31 by aaleixo-          #+#    #+#             */
/*   Updated: 2024/11/14 15:22:47 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(int value)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = value;
	new->index = 0;
	new->next = NULL;
	return (new);
}
/*
#include <stdio.h>

int	main(void)
{
	int num = 42;
	t_list *node = ft_lstnew(&num);

	printf("Node content: %d\n", *(int *)node->content);

	char *str = "batata";
	node = ft_lstnew(str);

	printf("Str content: %s\n", (char *)node->content);

	return (0);
}*/