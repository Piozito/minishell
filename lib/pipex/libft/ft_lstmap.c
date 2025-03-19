/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:04:58 by aaleixo-          #+#    #+#             */
/*   Updated: 2024/11/12 10:54:45 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*last;
	t_list	*new_node;

	new_list = NULL;
	last = NULL;
	while (lst != NULL)
	{
		new_node = (t_list *)malloc(sizeof(t_list));
		if (!new_node)
		{
			del(new_list);
			return (NULL);
		}
		new_node->content = f(lst->content);
		new_node->next = NULL;
		if (!new_list)
			new_list = new_node;
		else
			last->next = new_node;
		last = new_node;
		lst = lst->next;
	}
	return (new_list);
}
/*
void	*add_one(void *num)
{
	int	*val;
	int	*result;

	val = (int *)num;
	result = malloc(sizeof(int));
	if (result)
		*result = (*val) + 1;
	return (result);
}

#include <stdio.h>

void	free_int(void *num)
{
	free(num);
}

int	main(void)
{
	t_list *head = malloc(sizeof(t_list));
	t_list *current = head;
	unsigned int i = 0;
	int nums[] = {1, 2, 3, 4, 5};
	while (i < 5)
	{
		current->content = malloc(sizeof(int));
		*(int *)(current->content) = nums[i];
		if (i < 4)
		{
			current->next = malloc(sizeof(t_list));
			current = current->next;
		}
		else
			current->next = NULL;
		i++;
	}

	t_list *new_list = ft_lstmap(head, &add_one, &free_int);

	printf("lista: ");
	current = head;
	while (current)
	{
		printf("%d ", *(int *)(current->content));
		t_list *next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
	printf("\n");

	printf("Resultado: ");
	current = new_list;
	while (current)
	{
		printf("%d ", *(int *)(current->content));
		t_list *next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
	printf("\n");
	free(new_list);
	return (0);
}*/