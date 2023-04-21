/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 07:21:12 by wdelaros          #+#    #+#             */
/*   Updated: 2023/04/18 12:50:22 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	movement_number(t_game *game)
{
	char	*str;

	str = ft_itoa(game->move);
	if (BONUS)
	{
		mlx_delete_image(game->mlx, game->img.move);
		game->img.move = mlx_put_string(game->mlx, str, \
		game->win_w / 2 + 100, 30);
	}
	else if (game->move > 0 && game->move != game->oldmove)
	{
		ft_putendl_fd(str, 1);
		game->oldmove = game->move;
	}
	free(str);
}

void	if_error(char *str)
{
	ft_putendl_fd(str, 2);
	exit(1);
}

void	malloc_map(t_map *map, int x, int y)
{
	int	i;

	i = 0;
	map->map = ft_calloc(y + 1, sizeof(char *));
	map->map_tmp = ft_calloc(y + 1, sizeof(char *));
	while (i < y)
	{
		map->map[i] = ft_calloc(x + 1, sizeof(char));
		map->map_tmp[i] = ft_calloc(x + 1, sizeof(char));
		i++;
	}
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	ft_exit(t_game *game)
{
	free_array(game->map_t.map);
	mlx_delete_image(game->mlx, game->img.player);
	mlx_delete_image(game->mlx, game->img.coll);
	mlx_delete_image(game->mlx, game->img.exit);
	mlx_delete_image(game->mlx, game->img.back[0]);
	mlx_delete_image(game->mlx, game->img.back[1]);
	mlx_terminate(game->mlx);
	exit(0);
}
