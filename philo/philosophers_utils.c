/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouyzem <ybouyzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:05:30 by ybouyzem          #+#    #+#             */
/*   Updated: 2024/11/10 01:23:31 by ybouyzem         ###   ########.fr       */
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
