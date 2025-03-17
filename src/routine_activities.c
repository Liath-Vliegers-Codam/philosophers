/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine_activities.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: livliege <livliege@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/21 13:50:08 by livliege      #+#    #+#                 */
/*   Updated: 2025/02/28 19:01:49 by livliege      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	eating(t_philosopher *phil)
{
	pthread_mutex_lock(&(phil->phil_mutex));
	phil->eat_count++;
	phil->t_last_meal_ms = gettimeofday_ms();
	pthread_mutex_unlock(&(phil->phil_mutex));
	precise_usleep(phil->table->t_eat_ms * 1000, phil->table);
}

void	sleeping(t_philosopher *phil)
{
	precise_usleep(phil->table->t_sleep_ms * 1000, phil->table);
}

bool	pick_up_forks(t_philosopher *phil)
{
	int	time_left;
	int	time_to_eat;

	if ((phil->table->philo_count % 2 != 0) && (phil->eat_count != 0))
	{
		time_left = phil->table->t_die_ms - \
		((int)(gettimeofday_ms() - phil->t_last_meal_ms));
		time_to_eat = phil->table->t_eat_ms;
		if (time_left > time_to_eat)
			precise_usleep((time_left - time_to_eat) * 1000, phil->table);
	}
	pthread_mutex_lock(phil->fork_r);
	if (!print_safely(phil, "has taken a fork"))
	{
		pthread_mutex_unlock(phil->fork_r);
		return (false);
	}
	pthread_mutex_lock(phil->fork_l);
	if (!print_safely(phil, "has taken a fork"))
	{
		pthread_mutex_unlock(phil->fork_l);
		pthread_mutex_unlock(phil->fork_r);
		return (false);
	}
	return (true);
}

void	let_go_of_forks(t_philosopher *phil)
{
	pthread_mutex_unlock(phil->fork_l);
	pthread_mutex_unlock(phil->fork_r);
}
