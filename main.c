/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:53:29 by dyodlm            #+#    #+#             */
/*   Updated: 2025/04/08 10:03:49 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_rules	rules;
	int		status;

	status = init_all(&rules, ac, av);
	if (!status)
		return (exit_display(status), 1);
	start_simulation(&rules);
	cleanup(&rules);
	return (0);
}
