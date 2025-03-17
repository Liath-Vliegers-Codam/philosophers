/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleanup.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: livliege <livliege@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/21 13:33:32 by livliege      #+#    #+#                 */
/*   Updated: 2025/02/21 13:33:32 by livliege      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	clean_philos(t_philosopher *philos, int nbr)
{
	int	i;

	if (philos == NULL)
		return ;
	i = 0;
	while (i < nbr)
	{
		pthread_mutex_destroy(&(philos[i]).phil_mutex);
		i++;
	}
	free(philos);
}

void	clean_forks(pthread_mutex_t *forks, int nbr)
{
	int	i;

	if (forks == NULL)
		return ;
	i = 0;
	while (i < nbr)
	{
		pthread_mutex_destroy(&(forks[i]));
		i++;
	}
	free(forks);
}

void	clear_dining_table(t_table *table)
{
	pthread_mutex_destroy(&(table->table_mutex));
	pthread_mutex_destroy(&(table->print_mutex));
	clean_forks(table->forks, table->philo_count);
	clean_philos(table->philos, table->philo_count);
}
