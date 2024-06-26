/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sezequie <sezequie@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:23:04 by sezequie          #+#    #+#             */
/*   Updated: 2024/06/03 14:23:15 by sezequie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	find_player(void)
{
	int	x;
	int	y;

	y = 0;
	while (y < map()->size_y)
	{
		x = 0;
		while (x < map()->size_x)
		{
			if (map()->matrix[y][x] == 'P')
			{
				if (!field()->x_p && !field()->y_p)
				{
					field()->x_p = x;
					field()->y_p = y;
				}
				break ;
			}
			x++;
		}
		y++;
	}
}

void	flood_fill(char **matrix, int x, int y)
{
	if (check_fill(matrix, x - 1, y))
		flood_fill(matrix, x - 1, y);
	if (check_fill(matrix, x + 1, y))
		flood_fill(matrix, x + 1, y);
	if (check_fill(matrix, x, y - 1))
		flood_fill(matrix, x, y - 1);
	if (check_fill(matrix, x, y + 1))
		flood_fill(matrix, x, y + 1);
}

int	check_fill(char **matrix, int x, int y)
{
	if (y < 0 || y >= map()->size_y || x < 0 || x >= map()->size_x)
		return (0);
	if (matrix[y][x] == 'E' && ++field()->exit_2)
		matrix[y][x] = '1';
	if (matrix[y][x] == '1' || matrix[y][x] == '_')
		return (0);
	if (matrix[y][x] == 'C')
		field()->collect_2++;
	matrix[y][x] = '_';
	return (1);
}

int	playable_map(void)
{
	find_player();
	flood_fill(map()->matrix, field()->x_p, field()->y_p);
	if (field()->collect != field()->collect_2 || field()->exit_2 != 1)
		return (1);
	return (0);
}