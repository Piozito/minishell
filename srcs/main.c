/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:41:07 by marvin            #+#    #+#             */
/*   Updated: 2025/03/18 17:41:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int main(t_node node)
{
    if (node.type == PIPE)
        return (execute_pipe(node.left, node.right));
    else
        return (execute_simple_command(node.value))
    if (node.type == ECHO)
        return(execute_simple_command(node.value))
    if (node.type == CD)
        return(execute_simple_command(node.value))
    

}