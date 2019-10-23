/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 21:20:13 by wkorande          #+#    #+#             */
/*   Updated: 2019/10/23 19:18:18 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "../get_next_line/get_next_line.h"

int		main(int argc, char **argv)
{
	int		fd[argc];
	char	*line;
	int		i;
	int		closed;
	i = 1;
	if (argc == 1)
		fd[0] = 0;
	else
	{
		while (i < argc)
		{
			fd[i] = open(argv[i], O_RDONLY);
			i++;
		}
	}
	if (argc == 1)
	{
		while (get_next_line(fd[0], &line) == 1)
		{
			ft_putendl(line);
			free(line);
		}
	}
	else
	{
		i = 1;
		closed = 0;
		while (i < argc)
		{
			if (get_next_line(fd[i], &line) == 1)
			{
				ft_putendl(line);
				free(line);
				i++;
				if (i == argc)
				i = 1;
				continue ;
			}
			else
			{
				break;
			}
		}
	}

	i = 1;
	if (argc >= 2)
		while (i++ < argc)
			close(fd[i]);
	ft_putstr("Press any key");
	system("read -n1 -p ' ' key");
}
