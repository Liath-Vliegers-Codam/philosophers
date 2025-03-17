/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: livliege <livliege@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/21 13:33:45 by livliege      #+#    #+#                 */
/*   Updated: 2025/02/21 13:33:45 by livliege      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	philos_routine(t_philosopher *phil)
{
	while (1)
	{
		if (!pick_up_forks(phil))
			return ;
		if (!print_safely(phil, "is eating"))
			return (let_go_of_forks(phil));
		eating(phil);
		let_go_of_forks(phil);
		if (!print_safely(phil, "is sleeping"))
			return ;
		sleeping(phil);
		if (!print_safely(phil, "is thinking"))
			return ;
	}
}

void	dinner_for_one(t_philosopher *phil)
{
	pthread_mutex_lock(phil->fork_l);
	print_safely(phil, "has taken a fork");
	pthread_mutex_unlock(phil->fork_l);
	precise_usleep((phil->table->t_die_ms) * 1000, phil->table);
	pthread_mutex_lock(&phil->table->table_mutex);
	phil->table->philo_died = true;
	pthread_mutex_unlock(&phil->table->table_mutex);
}

void	*routine(void *philosopher)
{
	t_philosopher	*phil;

	phil = (t_philosopher *)philosopher;
	pthread_mutex_lock(&phil->table->table_mutex);
	pthread_mutex_unlock(&phil->table->table_mutex);
	if (phil->table->philo_count == 1)
	{
		dinner_for_one(phil);
		return (NULL);
	}
	if (phil->id % 2 == 0)
	{
		if (!print_safely(phil, "is thinking"))
			return (NULL);
		usleep((phil->table->t_eat_ms / 2) * 1000);
	}
	philos_routine(phil);
	return (NULL);
}
