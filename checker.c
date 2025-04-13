/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 07:45:02 by dyodlm            #+#    #+#             */
/*   Updated: 2025/04/12 10:25:57 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>

#define BSIZE 2048

typedef enum e_state
{
	THINKING,
	LEFT_FORK,
	RIGHT_FORK,
	EATING
} t_state;

char	*get_content(int fd)
{
	char	*buf = malloc(1);
	char	temp[BSIZE + 1];
	ssize_t bytes;
	size_t total = 0;

	if (!buf)
		return (NULL);
	buf[0] = '\0';
	while ((bytes = read(fd, temp, BSIZE)) > 0)
	{
		temp[bytes] = '\0';
		char *new_buf = realloc(buf, total + bytes + 1);
		if (!new_buf)
			return (free(buf), NULL);
		buf = new_buf;
		strcpy(buf + total, temp);
		total += bytes;
	}
	return (buf);
}

bool	is_routine_ok(char *doc)
{
	char	*line = strtok(doc, "\n");
	t_state state[256];
	memset(state, 0, sizeof(state));

	while (line)
	{
		int id;
		char action[32];

		if (strstr(line, "Action :") && sscanf(line, "%*s %*s ID : %d Action : %31s", &id, action) == 2)
		{
			if (strcmp(action, "IS") == 0)
			{
				char subaction[32];
				sscanf(strstr(line, "IS"), "IS %31s", subaction);
				if (strcmp(subaction, "THINKING") == 0)
					state[id] = THINKING;
				else if (strcmp(subaction, "EATING") == 0 && state[id] == RIGHT_FORK)
					state[id] = EATING;
				else if (strcmp(subaction, "SLEEPING") == 0 && state[id] == EATING)
					state[id] = THINKING;
				else if (strcmp(subaction, "EATING") == 0 || strcmp(subaction, "SLEEPING") == 0)
					return (false);
			}
			else if (strcmp(action, "TAKING") == 0)
			{
				char fork[32];
				sscanf(strstr(line, "TAKING"), "TAKING %31s", fork);
				if (strcmp(fork, "LEFT") == 0 && state[id] == THINKING)
					state[id] = LEFT_FORK;
				else if (strcmp(fork, "RIGHT") == 0 && state[id] == LEFT_FORK)
					state[id] = RIGHT_FORK;
				else
					return (false);
			}
		}
		line = strtok(NULL, "\n");
	}
	return (true);
}

int	main(int ac, char **av)
{
	int		fd;
	char	*name;
	char	*doc;

	name = NULL;
	if (ac != 2)
		return (0);
	if (av[1])
		name = av[1];
	doc = NULL;
	fd = open(name, O_RDONLY);
	if (fd <= 0)
		return (printf("Bad file descriptor\n"), 0);
	doc = get_content(fd);
	if (!doc)
		return (0);
	if (!is_routine_ok(doc))
		printf("Routine KO\n");
	else
		printf("Routine OK\n");
	return (free(doc), close(fd), 1);
}

