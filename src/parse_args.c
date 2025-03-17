/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_args.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: livliege <livliege@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/21 13:33:43 by livliege      #+#    #+#                 */
/*   Updated: 2025/02/21 13:33:43 by livliege      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	print_program_usage(void)
{
	printf("\nUsage of the philosophers program: \
Please provide four or five of the following arguments:\n");
	printf("\n");
	printf(" - number_of_philosophers:\n");
	printf("	The number of philosophers sitting at the table. \
(at least 1)\n");
	printf(" - time_to_die (in milliseconds):\n");
	printf("	If a philosopher didn’t start eating time_to_die \
milliseconds since the beginning\n");
	printf("	of their last meal or the beginning of the simulation, \
they die.\n");
	printf(" - time_to_eat (in milliseconds):\n");
	printf("	The time it takes for a philosopher to eat. \
During that time, they will need to hold two forks.\n");
	printf(" - time_to_sleep (in milliseconds):\n");
	printf("	The time a philosopher will spend sleeping.\n");
	printf(" - number_of_times_philosophers_must_eat (optional argument):\n");
	printf("	If all philosophers have eaten at least \
number_of_times_philosophers_must_eat times, the simulation stops.\n");
	printf("	If not specified, the simulation stops when \
a philosopher dies.\n");
	printf("\n");
	printf("Please provide the arguments for this program as follows:\n");
	printf("./philo <number_of_philosophers> <time_to_die> <time_to_eat> \
[number_of_times_philosophers_must_eat]\n\n");
}

void	skip_whitespaces_and_signs(const char *str, int *i, int *sign)
{
	while ((str[*i] >= 9 && str[*i] <= 13) || str[*i] == 32)
		(*i)++;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			*sign = -1;
		(*i)++;
	}
}

bool	ft_atoi_overflow_safe(const char *str, int *nbr)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	if (!str)
		return (false);
	skip_whitespaces_and_signs(str, &i, &sign);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result > (INT_MAX - (str[i] - '0')) / 10)
			return (false);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	result *= sign;
	if (result < INT_MIN || result > INT_MAX)
		return (false);
	*nbr = (int)result;
	return (true);
}

bool	check_args(int argc, char **argv)
{
	int	i;
	int	nbr;

	if (argc != 5 && argc != 6)
	{
		print_program_usage();
		return (false);
	}
	i = 1;
	while (i < 5)
	{
		if (!ft_atoi_overflow_safe(argv[i], &nbr) || nbr < 1)
		{
			printf("Error: one or more arguments is not \
a valid positive number\n");
			return (false);
		}
		i++;
	}
	return (true);
}

bool	init_args(int argc, char **argv, t_table *table)
{
	if (!check_args(argc, argv))
		return (false);
	table->start_time = 0;
	table->philo_died = false;
	ft_atoi_overflow_safe(argv[1], &(table->philo_count));
	ft_atoi_overflow_safe(argv[2], &(table->t_die_ms));
	ft_atoi_overflow_safe(argv[3], &(table->t_eat_ms));
	ft_atoi_overflow_safe(argv[4], &(table->t_sleep_ms));
	if (argc == 6)
	{
		ft_atoi_overflow_safe(argv[5], &(table->times_to_eat));
		if (table->times_to_eat < 0)
		{
			printf("Error: \
one or more arguments is not a valid positive number\n");
			return (false);
		}
	}
	else
		table->times_to_eat = -1;
	return (true);
}
