/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouyzem <ybouyzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:05:30 by ybouyzem          #+#    #+#             */
/*   Updated: 2024/11/17 12:32:05 by ybouyzem         ###   ########.fr       */
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

void	printer(t_philo *philo, int mode)
{
	size_t time;
	pthread_mutex_lock(&philo->program->write_lock);
	time = get_current_time() - philo->start_time;
	if (mode == LFORK)
		printf("%d has taken a left fork\n", philo->id);
	else if (mode == RFORK)
		printf("%d has taken a right fork\n", philo->id);
	else if (mode == EATING)
	{
		printf("%d is eating\n", philo->id);
		philo->last_meal = get_current_time();
	}
	else if (mode == SLEEPING)
		printf("%d is sleeping\n", philo->id);
	else if (mode == THINKING)
		printf("%d is thinking\n", philo->id);
	pthread_mutex_unlock(&philo->program->write_lock);
}
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
		if (philo->program->dead_flag)
			break ;
		usleep(100);
	}
}

int is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->program->dead_lock);
	if (philo->program->dead_flag || philo->is_finished)
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
	printer(philo, LFORK);
	if (pthread_mutex_lock(philo->right_fork))
		return (1);
	printer(philo, RFORK);
	return (0);
}

void	eating(t_philo *philo)
{
	printer(philo, EATING);
	my_sleep(philo->program->time_to_eat, philo);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	philo->meals_eaten++;
	if (philo->meals_eaten == philo->program->required_meals)
		philo->is_finished = 1;
}