/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnaulak <lnaulak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 11:47:05 by lnaulak           #+#    #+#             */
/*   Updated: 2024/01/31 13:24:23 by lnaulak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	write_error(char *str)
{
	printf("Error: %s\n", str);
	return (1);
}

int	main(int ac, char **av)
{
	t_rules	rules;
	int		ret;

	ret = 0;
	if (ac == 5 || ac == 6)
	{
		if (ret != init_all(&rules, av))
			return (write_error("something wrong within argument"));
		if (engine(&rules))
			return (write_error("something wrong with threads"));
	}
	else
		return (write_error("wrong argument"));
}
