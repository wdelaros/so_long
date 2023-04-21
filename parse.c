/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 20:08:59 by wdelaros          #+#    #+#             */
/*   Updated: 2023/04/17 14:00:20 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_and_convert_map(t_map *map, char ***sep_lines, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	malloc_map(map, x, y);
	while (i < y)
	{
		j = 0;
		while (j < x)
		{
			map->map[i][j] = *sep_lines[i][j];
			map->map_tmp[i][j] = *sep_lines[i][j];
			j++;
		}
		free_array(sep_lines[i]);
		i++;
	}
	if (x > 34 || y > 17)
	{
		free(sep_lines);
		free_array(map->map);
		free_array(map->map_tmp);
		if_error("Error\nmap too big <max size: x: 34, y: 17>");
	}
	return (0);
}

static int	get_x(char ***sep_lines, int y)
{
	int	x;
	int	i;
	int	j;

	x = 0;
	i = 0;
	j = 0;
	while (i < y)
	{
		while (sep_lines[i][j] != NULL)
			j++;
		if (i > 0 && j != x)
			if_error("Error\nInvalid map");
		x = j;
		j = 0;
		i++;
	}
	return (x);
}

static int	get_y(char *map)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (map[i] != '\0')
	{
		if (i > 0)
			if (map[i] == '\n' && map[i - 1] != '\n')
				y++;
		i++;
	}
	if (map[i - 1] != '\n')
		y++;
	return (y);
}

static char	*get_map(char *argv[], int i)
{
	char	*str;
	char	*strdef;
	int		fd;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		if_error("Error\nMap does not exist");
	str = "x";
	while (str)
	{
		str = get_next_line(fd);
		if (str == NULL)
			break ;
		if (i == 0)
			strdef = ft_strdup(str);
		else
			strdef = ft_fstrjoin(strdef, str);
		free (str);
		i++;
	}
	close(fd);
	if (!strdef || i < 3)
		if_error("Error\nInvalid map");
	return (strdef);
}

int	parse_map(char *argv[], t_map *map)
{
	char	*map_c;
	char	**lines;
	char	***sep_lines;
	int		i;

	map_c = get_map(argv, 0);
	i = 0;
	map->y = get_y(map_c);
	lines = ft_split(map_c, '\n');
	free(map_c);
	sep_lines = malloc(map->y * sizeof(char *));
	while (i < map->y)
	{
		sep_lines[i] = ft_split_char(lines[i]);
		i++;
	}
	free_array(lines);
	map->x = get_x(sep_lines, map->y);
	check_and_convert_map(map, sep_lines, map->x, map->y);
	free(sep_lines);
	valid_map(map, map->x, map->y);
	flood_fill(map->map_tmp, map);
	return (free_array(map->map_tmp), 0);
}
