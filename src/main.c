/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozlov <ikozlov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 13:47:52 by mtan              #+#    #+#             */
/*   Updated: 2018/03/02 17:15:14 by ikozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

char	*empty_map(int size)
{
	char	*tmp;
	int		x;
	int		y;

	tmp = ft_strnew((size + 1) * size);
	y = -1;
	while (++y < size)
	{
		x = -1;
		while (++x < size)
		{
			tmp[y * (size + 1) + x] = '.';
		}
		tmp[y * (size + 1) + x] = '\n';
	}
	return (tmp);
}

void	print(t_piece *t, int count, int size)
{
	char	*map;
	int		x;
	int		y;

	map = empty_map(size);
	while (count--)
	{
		y = -1;
		while (++y < t->height)
		{
			x = -1;
			while (++x < t->width)
			{
				if ((t->value >> (16 * (y + 1) - 1 - x)) & 1)
					map[(t->y + y) * (size + 1) + x + t->x] = t->id;
			}
		}
		t++;
	}
	ft_putstr(map);
	ft_strdel(&map);
}

int		ft_exit(char *str)
{
	ft_putendl(str);
	return (1);
}

int		main(int ac, char **av)
{
	t_piece		tetris[MAX_PIECES + 1];
	int			count;
	int			size;

	if (ac != 2)
		return (ft_exit("usage: ./fillit [input_file]"));
	bzero(tetris, MAX_PIECES + 1);
	if (!(count = read_pieces(open(av[1], O_RDONLY), tetris)))
		return (ft_exit("error"));
	if (!(size = solve(tetris, count)))
		return (ft_exit("error"));
	print(tetris, count, size);
	return (0);
}
