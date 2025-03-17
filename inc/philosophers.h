/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: livliege <livliege@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/21 13:33:59 by livliege      #+#    #+#                 */
/*   Updated: 2025/02/21 13:33:59 by livliege      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <limits.h>

# define DEFAULT	"\033[0m"
# define BLACK		"\033[30m"
# define RED		"\033[31m"
# define GREEN		"\033[32m"
# define YELLOW		"\033[33m"
# define BLUE		"\033[34m"
# define MAGENTA	"\033[35m"
# define CYAN		"\033[36m"
# define WHITE		"\033[37m"
# define BOLD		"\033[1m"
# define UNDERLINE	"\033[4m"
# define REVERSED	"\033[7m"

typedef struct s_philosopher
{
	int					id;
	int					eat_count;
	uint64_t			t_last_meal_ms;

	pthread_mutex_t		phil_mutex;
	pthread_mutex_t		*fork_l;
	pthread_mutex_t		*fork_r;
	pthread_t			thread;

	bool				done_eating;

	struct s_table		*table;
}	t_philosopher;

typedef struct s_table
{
	t_philosopher	*philos;
	pthread_mutex_t	*forks;

	pthread_mutex_t	table_mutex;
	pthread_mutex_t	print_mutex;

	int				philo_count;
	int				t_die_ms;
	int				t_eat_ms;
	int				t_sleep_ms;
	int				times_to_eat;

	uint64_t		start_time;
	bool			philo_died;
}	t_table;

// cleanup.c
void		clean_philos(t_philosopher *philos, int nbr);
void		clean_forks(pthread_mutex_t *forks, int nbr);
void		clear_dining_table(t_table *table);

// dinner_monitor.c
bool		all_courses_served(t_table *table);
bool		death_check(t_table *table);
bool		death_monitor(t_philosopher *phil);
bool		philosopher_died(t_table *table);
void		dinner_party(t_table *table);

// parse_args.c
void		print_program_usage(void);
bool		ft_atoi_overflow_safe(const char *str, int *nbr);
bool		check_args(int argc, char **argv);
bool		init_args(int argc, char **argv, t_table *table);

// routine_activities.c
void		eating(t_philosopher *phil);
void		sleeping(t_philosopher *phil);
bool		pick_up_forks(t_philosopher *phil);
void		let_go_of_forks(t_philosopher *phil);

// routine.c
void		dinner_for_one(t_philosopher *phil);
void		*routine(void *philosopher);

// set_dining_table.c
void		choose_forks(t_philosopher *phil, t_table *table);
bool		init_philosopher(t_table *table);
bool		init_forks(t_table *table);
bool		set_dining_table(t_table *table);

// threads.c
void		join_threads(t_table *table, int nbr);
bool		create_threads(t_table *table);
bool		start_dinner(t_table *table);

// utils.c
uint64_t	gettimeofday_ms(void);
uint64_t	timestamp_ms(uint64_t start);
bool		print_safely(t_philosopher *phil, char	*activity);
void		precise_usleep(long usec, t_table *table);

#endif
