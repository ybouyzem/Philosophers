/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouyzem <ybouyzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 06:29:51 by ybouyzem          #+#    #+#             */
/*   Updated: 2024/11/17 14:03:13 by ybouyzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	all_philos_finished(t_philo *philos)
{
	int i;

	i = 0;
	while (i < philos[0].program->num_of_philos)
	{
		if (!philos[i].is_finished)
			return (0);
		i++;
	}
	return (1);
}

void    *ft_monitor(void    *arg)
{
	int    i;
	size_t passtime;
	t_philo *philos;

	philos = (t_philo *)arg;
	while (1)
	{
		i = 0;
		while (i < philos[0].program->num_of_philos)
		{ 
			pthread_mutex_lock(&philos[0].program->monitor_lock);
			passtime = get_current_time() - philos[i].last_meal;
			if (passtime > philos[i].program->time_to_die)
			{
				pthread_mutex_lock(&philos[i].program->dead_lock);
				philos->program->dead_flag = 1;
				pthread_mutex_unlock(&philos[i].program->dead_lock);
				printf("%d is died\n", philos[i].id);
				pthread_mutex_unlock(&philos[0].program->monitor_lock);
				return (NULL);
			}
			i++;
			pthread_mutex_unlock(&philos[0].program->monitor_lock);
		}
	}
}
