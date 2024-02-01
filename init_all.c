/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnaulak <lnaulak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:17:27 by lnaulak           #+#    #+#             */
/*   Updated: 2024/02/01 12:38:15 by lnaulak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_rules *rules)
{
	int				i;
	t_philosopher	*philo;

	rules->philosophers = malloc(sizeof(t_philosopher) * rules->nb_philo);
	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->nb_philo);
	rules->avail = malloc(sizeof(bool) * rules->nb_philo);
	philo = rules->philosophers;
	i = -1;
	pthread_mutex_init(&rules->read_fork, NULL);
	pthread_mutex_init(&rules->writing, NULL);
	pthread_mutex_init(&rules->dieded_lock, NULL);
	rules->dieded = false;
	while (++i < rules->nb_philo)
	{
		philo[i].id = i + 1;
		philo[i].right_fork_id = i;
		if (i == rules->nb_philo - 1 && rules->nb_philo != 1)
			philo[i].left_fork_id = 0;
		else
			philo[i].left_fork_id = i + 1;
		philo[i].t_last_meal = 0;
		philo[i].rules = rules;
		rules->avail[i] = true;
		pthread_mutex_init(&rules->forks[i], NULL);
	}
}

int	init_all(t_rules *rules, char **av)
{
	rules->nb_philo = ft_atoi(av[1]);
	rules->time_tdeath = ft_atoi(av[2]);
	rules->time_teat = ft_atoi(av[3]);
	rules->time_tsleep = ft_atoi(av[4]);
	if (rules->nb_philo <= 0 || rules->time_tdeath < 0 || rules->time_teat
		< 0 || rules->time_tsleep < 0 || rules->nb_philo > 200)
		return (1);
	if (av[5] != NULL)
		rules->nb_to_eat = ft_atoi(av[5]);
	else
		rules->nb_to_eat = -1;
	init_philo(rules);
	return (0);
}
