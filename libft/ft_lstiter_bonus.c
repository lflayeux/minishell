/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 10:45:38 by lflayeux          #+#    #+#             */
/*   Updated: 2024/11/26 12:19:29 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
/*
void    print_content(void *content)
{
	content = "1";
    printf("%s\n", (char *)content);
}
int main()
{
	t_list *test = ft_lstnew("Salut");
	t_list *test2 = ft_lstnew("mec");
	t_list *test3 = ft_lstnew("cava");


	test->next = test2;
	test2->next = test3;
	test3->next = NULL;


	printf("%p\n", test);
	ft_lstiter(test, print_content);
	printf("%p\n", test);
	ft_lstclear(&test, free);
}*/
