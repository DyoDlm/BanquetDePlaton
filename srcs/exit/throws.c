/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   throws.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 06:15:16 by dyodlm            #+#    #+#             */
/*   Updated: 2025/03/31 06:51:19 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	exit_display(int status)
{
	if (status)
		printf("OKLM\n");
	else
		printf("SHIT\n");
}

