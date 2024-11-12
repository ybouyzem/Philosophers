/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouyzem <ybouyzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 06:29:51 by ybouyzem          #+#    #+#             */
/*   Updated: 2024/11/11 08:07:50 by ybouyzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    *ft_monitor(void    *arg)
{
    int    i;
    size_t passtime;
    t_philo *philos;

    philos = (t_philo *)arg;
    while (1)
    {
        i = -1;
        while (++i < philos[0].program->num_of_philos)
        { 
            // monitor lock
            passtime = get_current_time() - philos[i].last_meal;
            if (passtime > philos[i].program->time_to_die)
            {
                pthread_mutex_lock(&philos[i].program->dead_lock);
                philos->program->dead_flag = 1;
                pthread_mutex_unlock(&philos[i].program->dead_lock);
                printer(&philos[i], DEAD);
                return (NULL);
            }
            
            
            // monitor unlock
        }
    }
}
