/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouyzem <ybouyzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:05:30 by ybouyzem          #+#    #+#             */
/*   Updated: 2024/11/20 23:36:51 by ybouyzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int ft_isspace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t' 
		|| c == '\v' || c == '\r')
		return (1);
	return (0);
}

int ft_atoi(char *str)
{
	int n;
	int i;
	int sign;
	
	i = 0;
	n = 0;
	sign = 1;
	while (ft_isspace(str[i]) && str[i])
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		n = (n * 10) + str[i] - '0';
		i++;
	}
	return (n * sign);
}

int	ft_write(t_philo *philo, char *str)
{
	size_t timestamp;
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

// void	printer(t_philo *philo, int mode)
// {
// 	size_t timestamp;

// 	if (philo->program->program_finished)
// 		return ;
// 	pthread_mutex_lock(&philo->program->write_lock);
// 	timestamp= get_current_time() - philo->start_time;
// 	if (mode == FORK)
// 		printf("%zu %d has taken a fork\n", timestamp, philo->id);
// 	else if (mode == EATING)
// 	{
// 		printf("%zu %d is eating\n", timestamp, philo->id);
// 		philo->last_meal = get_current_time();
// 	}
// 	else if (mode == SLEEPING)
// 		printf("%zu %d is sleeping\n", timestamp, philo->id);
// 	else if (mode == THINKING)
// 		printf("%zu %d is thinking\n", timestamp, philo->id);
// 	pthread_mutex_unlock(&philo->program->write_lock);
// }

size_t get_current_time()
{
	struct timeval tv;
	//contains tv.tv_sec (seconds) and tv.tv_usec (microseconds)
	size_t time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

void my_sleep(size_t time, t_philo *philo)
{
	size_t start;

	start = get_current_time();
	while (get_current_time() - start < time)
	{
		pthread_mutex_lock(&philo->program->monitor_lock);
		if (philo->program->program_finished)
		{
			pthread_mutex_unlock(&philo->program->monitor_lock);
			return ;
		}
		pthread_mutex_unlock(&philo->program->monitor_lock);
		usleep(100);
	}
}

int is_dead(t_philo *philo)
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
	if (pthread_mutex_lock(philo->left_fork))
		return (1);
	// printer(philo, FORK);
	ft_write(philo, FORK);
	if (philo->program->num_of_philos == 1)
	{
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	if (pthread_mutex_lock(philo->right_fork))
		return (1);
	// printer(philo, FORK);
	ft_write(philo, FORK);
	return (0);
}

void	eating(t_philo *philo)
{
	// printer(philo, EATING);
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