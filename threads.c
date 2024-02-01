/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnaulak <lnaulak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:10:36 by lnaulak           #+#    #+#             */
/*   Updated: 2024/01/31 15:21:11 by lnaulak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sleeping(t_rules *rules, t_philosopher *philo)
{
	pthread_mutex_unlock(&rules->read_fork);
	pthread_mutex_lock(&rules->dieded_lock);
	if (philo->rules->dieded)
	{
		pthread_mutex_unlock(&rules->dieded_lock);
		return (0);
	}
	pthread_mutex_unlock(&rules->dieded_lock);
	action_print(rules, philo->id, "is sleeping");
	smart_sleep(rules->time_tsleep, rules);
	philo->state = 'e';
	usleep(1000);
	return (1);
}

void	eating(t_rules *rules, t_philosopher *philo)
{
	rules->avail[philo->right_fork_id] = false;
	rules->avail[philo->left_fork_id] = false;
	philo->t_last_meal = timestamp();
	philo->x_ate += 1;
	pthread_mutex_unlock(&rules->read_fork);
	action_print(rules, philo->id, "is eating");
	smart_sleep(rules->time_teat, rules);
	pthread_mutex_lock(&rules->read_fork);
	rules->avail[philo->right_fork_id] = true;
	rules->avail[philo->left_fork_id] = true;
	pthread_mutex_unlock(&rules->read_fork);
	philo->state = 's';
	philo->print_think = false;
}

void	thinking(t_rules *rules, t_philosopher *philo)
{
	pthread_mutex_unlock(&rules->read_fork);
	if (philo->print_think == false)
		action_print(rules, philo->id, "is thinking");
	philo->print_think = true;
}

int	threads(t_rules *rules, t_philosopher *philo)
{
	bool	mine_avail;
	bool	next_avail;

	pthread_mutex_lock(&rules->read_fork);
	mine_avail = rules->avail[philo->right_fork_id];
	next_avail = rules->avail[philo->left_fork_id];
	if (philo->state == 's')
	{
		if (sleeping(rules, philo) == 0)
			return (0);
	}
	else if (philo->state == 'e' && (mine_avail && next_avail))
		eating(rules, philo);
	else
		thinking(rules, philo);
	usleep(100);
	return (1);
}
