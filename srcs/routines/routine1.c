/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 08:21:43 by dyodlm            #+#    #+#             */
/*   Updated: 2025/03/31 06:51:10 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat(void *data)
{
	t_locks	*locks;

	locks = (t_locks *)data;
	pthread_mutex_lock(&locks->lock_1);
}
