/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   explore.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 09:41:53 by wdelaros          #+#    #+#             */
/*   Updated: 2023/04/17 14:00:07 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	explore(char **tab, t_map *map, int y, int x)
{
	if ((y > 0 && y < map->y) && (x > 0 && x < map->x))
	{
		if (tab[y][x] == '1')
			return ;
		if (tab[y][x] == 'P')
			map->nbr_p2++;
		else if (tab[y][x] == 'C')
			map->nbr_c2++;
		else if (tab[y][x] == 'E')
			map->nbr_e2++;
		tab[y][x] = '1';
		explore(tab, map, y, x + 1);
		explore(tab, map, y, x - 1);
		explore(tab, map, y + 1, x);
		explore(tab, map, y - 1, x);
	}
}

void	flood_fill(char **tab, t_map *map)
{
	int	x;
	int	y;

	y = map->yp;
	x = map->xp;
	map->nbr_p2 = 0;
	map->nbr_c2 = 0;
	map->nbr_e2 = 0;
	explore(tab, map, y, x);
	if (map->nbr_c != map->nbr_c2 || map->nbr_e != map->nbr_e2 || \
	map->nbr_p != map->nbr_p2)
	{
		free_array(map->map_tmp);
		if_error("Error\nInvalid map");
	}
}

static t_map	*check_map_value(t_map *map, int i, int j)
{
	if ((i == 0 || j == 0 || i == map->y - 1 || j == map->x - 1) && \
	map->map[i][j] != '1')
		if_error("Error\nInvalid map");
	else if (map->map[i][j] == 'P')
	{
		map->nbr_p++;
		map->xp = j;
		map->yp = i;
	}
	else if (map->map[i][j] == 'C')
		map->nbr_c++;
	else if (map->map[i][j] == 'E')
		map->nbr_e++;
	else if (map->map[i][j] != '0' && map->map[i][j] != '1')
		if_error("Error\nInvalid map");
	return (map);
}

void	valid_map(t_map *map, int x, int y)
{
	int	i;
	int	j;

	map->nbr_p = 0;
	map->nbr_c = 0;
	map->nbr_e = 0;
	i = 0;
	while (i < y)
	{
		j = 0;
		while (j < x)
		{
			map = check_map_value(map, i, j);
			j++;
		}
		i++;
	}
	if (map->nbr_p != 1 || map->nbr_c == 0 || map->nbr_e != 1)
		if_error("Error\nInvalid map");
}
