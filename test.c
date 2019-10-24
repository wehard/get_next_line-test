/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 21:20:13 by wkorande          #+#    #+#             */
/*   Updated: 2019/10/24 12:03:40 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "../get_next_line/get_next_line.h"

int		check_closed_fd(int *file, int size)
{
	int i;
	int all_closed;

	all_closed = 0;
	i = 1;
	while (i < size)
	{
		all_closed = 0;
		if (file[i] == -2)
		{
			all_closed = 1;
			//ft_putstr("closing ");
			//ft_putnbr(i);
			//ft_putchar('\n');
		}
		i++;
	}
	return (all_closed);
}

int		main(int argc, char **argv)
{
	int		file[argc];
	char	*line;
	int		i;

	i = 1;
	ft_bzero(file, argc);
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
		i = 1;
		while (1)
		{
			if (i == argc)
				i = 1;
			if (file[i] != -2 && get_next_line(file[i], &line) == 1)
			{
				ft_putnbr(i);
				ft_putstr(": ");
				ft_putendl(line);
				free(line);
			}
			else
			{
				close(file[i]);
				file[i] = -2;
			}
			if (check_closed_fd(file, argc))
					break ;
			i++;

		}
		printf("All done.\n");
	}

	i = 1;
	if (argc >= 2)
		while (i < argc)
			close(file[i++]);
	//ft_putstr("Press any key");
	//system("read -n99 -p ' ' key");
}
