/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouyzem <ybouyzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:17:07 by ybouyzem          #+#    #+#             */
/*   Updated: 2024/11/23 03:10:56 by ybouyzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <limits.h>

# define FORK "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DEAD "died"

typedef struct s_program
{
	int				num_of_philos;
	int				required_meals;
	int				program_finished;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	pthread_t		monitor;
	pthread_mutex_t	monitor_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
}	t_program;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				meals_eaten;
	int				finish_eating;
	size_t			last_meal;
	size_t			start_time;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	t_program		*program;
}	t_philo;

int		ft_isdigit(char c);
int		ft_isspace(char c);
int		check_args(char **argv);
int		check_is_num(char *str);
long	ft_atoi(char *str);
int		init_forks(pthread_mutex_t *forks, t_program *program);
int		init_philos(t_program *program,
			t_philo *philos, pthread_mutex_t *forks);
int		check_args(char **argv);
int		init_forks(pthread_mutex_t *forks, t_program *program);
int		allocate_utils(t_philo **philo,
			pthread_mutex_t **forks, t_program program);
int		init_program(t_program *program,
			t_philo **philos, pthread_mutex_t **forks, char **argv);
size_t	get_current_time(void);
void	*ft_monitor(void *arg);
void	*ft_philo(void *arg);
void	my_sleep(size_t time, t_philo *philo);
int		is_dead(t_philo *philo);
int		is_holding_forks(t_philo *philo);
void	eating(t_philo *philo);
int		all_philos_finished(t_philo *philos);
int		ft_write(t_philo *philo, char *str);
void	ft_mutex(pthread_mutex_t *mutex, int mode);
void	*ft_malloc(size_t size, int mode);
#endif