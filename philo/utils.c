/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouyzem <ybouyzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:05:30 by ybouyzem          #+#    #+#             */
/*   Updated: 2024/11/21 14:33:03 by ybouyzem         ###   ########.fr       */
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

size_t get_current_time()
{
	struct timeval tv;
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

