/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fii.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:05:14 by dyodlm            #+#    #+#             */
/*   Updated: 2025/04/07 12:08:11 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	fii(void)
{
	printf("FII\n");
}

/*
	*thread : un pointeur vers une variable de type pthread_t 
	* pour stocker l’identifiant du thread qu’on va créer.
	*attr : un argument qui permet de changer 
	* les attributs par défaut du nouveau thread lors de sa création.
	* Ceci va au-delà de la portée de cet article, et en général
	* il suffira d’indiquer NULL ici.
	*start_routine : la fonction par laquelle le thread
	* commence son exécution. Cette fonction doit avoir pour
	* prototype void *nom_de_fonction_au_choix(void *arg);.
	* Lorsque le thread arrive à la fin de cette fonction, 
	* il aura terminé toutes ses tâches.
	*arg : le pointeur vers un argument à transmettre à la fonction
	* start_routine du thread. Si l’on souhaite passer plusieurs
	* paramètres à cette fonction,
	* il n’y a pas d’autre choix que de lui renseigner ici
	* un pointeur vers une structure de données.
*/
//int	pthread_create(pthread_t *restrict_thread,
//	const pthread_attr_t *restrict attr,
//	void *(*start_routine)(void *),
//	void *restrict arg);
/*
	*thread : l’identifiant du thread qu’on attend.
	* Le thread spécifié ici doit être joignable
	* (c’est à dire non détaché - voir ci-dessous).
	*retval : un pointeur vers une variable
	* qui peut contenir la valeur de retour
	* de la fonction routine du thread 
	* la fonction start_routine qu’on a fournie
	* lors de la création du thread).
	* Si on n’a pas besoin de cette valeur,
	* on peut simplement renseigner NULL.
*/
//int	pthread_join(pthread_t thread, void **retval);

//int	pthread_detach(pthread_t thread);
