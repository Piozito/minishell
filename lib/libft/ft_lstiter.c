/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:03:04 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/03/09 17:41:04 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst != NULL)
	{
		f(lst->content);
		lst = lst->next;
	}
}
/*
#include <stdio.h>

void	print_content(void *content)
{
	printf("%s\n", (char *)content);
}

int	main(void)
{
	t_list *node1 = (t_list *)malloc(sizeof(t_list));
	node1->content = ft_strdup("Node 1");
	node1->next = NULL;

	t_list *node2 = (t_list *)malloc(sizeof(t_list));
	node2->content = ft_strdup("Node 2");
	node2->next = NULL;

	node1->next = node2;

	printf("Lista:\n");
	ft_lstiter(node1, &print_content);

	free(node1->content);
	free(node1);
	free(node2->content);
	free(node2);

	return (0);
}*/