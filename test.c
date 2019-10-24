/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 21:20:13 by wkorande          #+#    #+#             */
/*   Updated: 2019/10/24 17:45:00 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "../get_next_line/get_next_line.h"

int		check_closed_fd(int *done, int size)
{
	int i;
	int all_closed;

	all_closed = 0;
	i = 0;
	while (i < size)
	{
		//ft_putnbr(done[i]);
		if (done[i] == 1)
			all_closed = 1;
		else
			all_closed = 0;
		i++;
	}
	//ft_putnbr(all_closed);
	//ft_putchar('\n');
	return (all_closed > 0);
}

int		main(int argc, char **argv)
{
	int		file[argc];
	int		done[argc];
	char	*line;
	int		i;

	ft_bzero(done, argc);
	i = 1;
	if (argc == 1)
		file[0] = 0;
	else
	{
		while (i < argc)
		{
			file[i] = open(argv[i], O_RDONLY);
			i++;
		}
	}
	if (argc == 1)
	{
		while (get_next_line(file[0], &line) == 1)
		{
			ft_putendl(line);
			free(line);
		}
	}
	else
	{
		done[0] = 1;
		i = 0;
		while (1)
		{
			if (i == argc)
				i = 0;

			if (get_next_line(file[i], &line) == 1)
			{
				ft_putnbr(i);
				ft_putstr(": ");
				ft_putendl(line);
				free(line);
			}
			else
			{
				done[i] = 1;
				if (check_closed_fd(done, argc))
					break ;
			}
			i++;

		}
		printf("All done.\n");
	}


	i = 1;
	if (argc >= 2)
		while (i < argc)
		{
			close(file[i]);
			i++;
		}

	for (int j = 0; j < argc; j++)
	{
		ft_putnbr(done[i]);
		ft_putchar(' ');
	}
}
