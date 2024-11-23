/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouyzem <ybouyzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:07:14 by ybouyzem          #+#    #+#             */
/*   Updated: 2024/11/23 01:54:13 by ybouyzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_all(int *i, void **ptr_list)
{
	int	j;

	j = 0;
	while (j < *i)
	{
		free(ptr_list[j]);
		ptr_list[j++] = NULL;
	}
	*i = 0;
}

void	*ft_malloc(size_t size, int mode)
{
	static void	*ptr_list[INT_MAX];
	static int	i;
	void		*ptr;

	i = 0;
	if (mode == 1)
	{
		free_all(&i, ptr_list);
		return (NULL);
	}
	ptr = malloc(size);
	if (!ptr)
		return (ft_malloc(0, 1), NULL);
	ptr_list[i++] = ptr;
	ptr_list[i] = NULL;
	return (ptr);
}

void	destroy_mutex(pthread_mutex_t **mutex_list, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		pthread_mutex_destroy(mutex_list[j]);
		j++;
	}
}

void	ft_mutex(pthread_mutex_t *mutex, int mode)
{
	static pthread_mutex_t	*mutex_list[1000];
	static int				i;

	i = 0;
	if (mode == 0)
	{
		mutex_list[i++] = mutex;
		mutex_list[i] = NULL;
	}
	else
	{
		destroy_mutex(mutex_list, i);
		i = 0;
	}
}
