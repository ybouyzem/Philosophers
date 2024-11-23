/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouyzem <ybouyzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:16:50 by ybouyzem          #+#    #+#             */
/*   Updated: 2024/11/23 19:58:44 by ybouyzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_write(t_philo *philo, char *str)
{
	size_t	timestamp;

	pthread_mutex_lock(&philo->program->dead_lock);
	if (philo->program->program_finished)
	{
		pthread_mutex_unlock(&philo->program->dead_lock);
		return (1);
	}
	timestamp = get_current_time() - philo->start_time;
	printf("%zu %d %s\n", timestamp, philo->id, str);
	pthread_mutex_unlock(&philo->program->dead_lock);
	return (0);
}

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->program->dead_lock);
	if (philo->program->program_finished)
	{
		pthread_mutex_unlock(&philo->program->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->program->dead_lock);
	return (0);
}

int	is_holding_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	ft_write(philo, FORK);
	if (philo->program->num_of_philos == 1)
	{
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	pthread_mutex_lock(philo->right_fork);
	ft_write(philo, FORK);
	return (0);
}

void	eating(t_philo *philo)
{
	ft_write(philo, EATING);
	pthread_mutex_lock(&philo->program->monitor_lock);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(&philo->program->monitor_lock);
	pthread_mutex_lock(&philo->program->meal_lock);
	philo->meals_eaten++;
	if (philo->meals_eaten == philo->program->required_meals)
		philo->finish_eating = 1;
	pthread_mutex_unlock(&philo->program->meal_lock);
	my_sleep(philo->program->time_to_eat, philo);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*ft_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		my_sleep(50, philo);
	while (1)
	{
		if (is_dead(philo))
			break ;
		if (is_holding_forks(philo))
			break ;
		eating(philo);
		ft_write(philo, SLEEPING);
		my_sleep(philo->program->time_to_sleep, philo);
		ft_write(philo, THINKING);
	}
	return (NULL);
}
