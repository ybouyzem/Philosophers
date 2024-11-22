/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouyzem <ybouyzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 06:29:51 by ybouyzem          #+#    #+#             */
/*   Updated: 2024/11/22 17:27:53 by ybouyzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	all_philos_finished(t_philo *philos)
{
	int i;

	i = 0;
	while (i < philos[0].program->num_of_philos)
	{
		pthread_mutex_lock(&philos[i].program->meal_lock);
		if (!philos[i].finish_eating)
		{
			pthread_mutex_unlock(&philos[i].program->meal_lock);
			return (0);
		}
		pthread_mutex_unlock(&philos[i].program->meal_lock);
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
			if (pthread_mutex_lock(&philos[0].program->monitor_lock) != 0)
				return (printf("failed to lock mutex\n"), NULL);
			passtime = get_current_time() - philos[i].last_meal;
			if (passtime >= philos[i].program->time_to_die || all_philos_finished(philos))
			{
				if (pthread_mutex_lock(&philos[i].program->dead_lock) != 0)
					return (printf("failed to lock mutex\n"), NULL);
				philos->program->program_finished = 1;
				if (pthread_mutex_unlock(&philos[i].program->dead_lock) != 0)
					return (printf("failed to unlock mutex\n"), NULL);
				if (!all_philos_finished(philos))
					printf("%zu %d died\n", (get_current_time() - philos[i].start_time), philos[i].id);
				if (pthread_mutex_unlock(&philos[0].program->monitor_lock) != 0)
					return (printf("failed to unlock mutex\n"), NULL);
				return (NULL);
			}
			i++;
			if (pthread_mutex_unlock(&philos[0].program->monitor_lock) != 0)
				return (printf("failed to unlock mutex\n"), NULL);
		}
	}
}



