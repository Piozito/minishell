/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:49:17 by aaleixo-          #+#    #+#             */
/*   Updated: 2024/11/12 10:55:14 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **stack, t_list *new)
{
	new->next = *stack;
	*stack = new;
}
/*
#include <stdio.h>

int	main(void)
{
	t_list *head = NULL;

	t_list *node1 = (t_list *)malloc(sizeof(t_list));
	t_list *node2 = (t_list *)malloc(sizeof(t_list));
	t_list *node3 = (t_list *)malloc(sizeof(t_list));

	node1->content = strdup("Primeiro");
	node1->next = NULL;
	ft_lstadd_front(&head, node1);

	node2->content = strdup("Segundo");
	node2->next = NULL;
	ft_lstadd_front(&head, node2);

	node3->content = strdup("Terceiro");
	node3->next = NULL;
	ft_lstadd_front(&head, node3);

	printf("Lista:\n");
	t_list *current = head;
	while (current)
	{
		printf("%s\n", (char *)(current->content));
		current = current->next;
	}

	current = head;
	while (current)
	{
		t_list *next = current->next;
		free(current->content);
		free(current);
		current = next;
	}

	return (0);
}*/