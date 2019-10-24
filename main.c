/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 21:20:13 by wkorande          #+#    #+#             */
/*   Updated: 2019/10/24 18:53:51 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "libft.h"
#include "get_next_line.h"

int		check_closed_fd(int *file, int count)
{
	int i;
	int all_closed;

	all_closed = 0;
	i = 0;
	while (i < count)
	{
		if (file[i] == 1)
			all_closed = 1;
		else
			all_closed = 0;
		i++;
	}
	return (all_closed);
}

int		main(int argc, char **argv)
{
	char	*line;
	int		file[argc];
	int 	done[argc-1];
	int		i;
	int 	error;

	error = 0;
	if (argc == 1)
	{
		while ((error = get_next_line(file[0], &line)) == 1)
		{
			ft_putendl(line);
			free(line);
		}
		return (error);
	}

	i = 0;
	while (i < argc)
	{
		file[i] = open(argv[i + 1], O_RDONLY);
		i++;
	}


	i = 0;
	while (1)
	{
		if (done[i] != 1 && (get_next_line(file[i], &line) == 1))
		{
			ft_putnbr(i);
			ft_putstr(": ");
			ft_putstr(line);
			ft_putendl("$");
			free(line);
		}
		else
		{
			done[i] = 1;
			if (check_closed_fd(done, argc))
				break ;
		}
		i++;
		if (i == argc - 1)
			i = 0;
	}
	printf("All done.\n");


	i = 0;
		while (i < argc - 1)
			close(file[i++]);
}
