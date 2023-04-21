/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 09:14:40 by wdelaros          #+#    #+#             */
/*   Updated: 2023/04/18 12:42:26 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_game	*init_background(t_game *game, int x, int y)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(WALL);
	game->img.back[0] = mlx_texture_to_image(game->mlx, texture);
	mlx_delete_texture(texture);
	texture = mlx_load_png(WOOD);
	game->img.back[1] = mlx_texture_to_image(game->mlx, texture);
	mlx_delete_texture(texture);
	while (y * 75 <= game->win_h - 75)
	{
		x = 0;
		while (x * 75 <= game->win_w - 75)
		{
			if (game->map_t.map[y][x] == '1')
				mlx_image_to_window(game->mlx, game->img.back[0], x * 75 \
				, y * 75);
			else
				mlx_image_to_window(game->mlx, game->img.back[1], x * 75 \
				, y * 75);
			x++;
		}
		y++;
	}
	return (game);
}

static t_game	*init_coll(t_game *game, int x, int y)
{
	mlx_texture_t	*texture;

	if (game->coll == 0)
	{
		texture = mlx_load_png(SUBWAY);
		game->img.coll = mlx_new_image(game->mlx, 75, 75);
		game->img.coll = mlx_texture_to_image(game->mlx, texture);
		mlx_delete_texture(texture);
	}
	mlx_image_to_window(game->mlx, game->img.coll, x * 75, y * 75);
	game->coll++;
	return (game);
}

t_game	*init_coll_and_exit(t_game *game, int x, int y, int exit)
{
	mlx_texture_t	*texture;

	game->coll = 0;
	while (y * 75 <= game->win_h - 75)
	{
		x = 0;
		while (x * 75 <= game->win_w - 75)
		{
			if (game->map_t.map[y][x] == 'C')
				game = init_coll(game, x, y);
			else if (game->map_t.map[y][x] == 'E' && exit == 1)
			{
				texture = mlx_load_png(DOOR);
				game->img.exit = mlx_new_image(game->mlx, 75, 75);
				game->img.exit = mlx_texture_to_image(game->mlx, texture);
				mlx_delete_texture(texture);
				mlx_image_to_window(game->mlx, game->img.exit, x * 75, y * 75);
			}
			x++;
		}
		y++;
	}
	return (game);
}

static t_game	*init_player(t_game *game, int x, int y)
{
	mlx_texture_t	*texture;

	while (y * 75 <= game->win_h - 75)
	{
		x = 0;
		while (x * 75 <= game->win_w - 75)
		{
			if (game->map_t.map[y][x] == 'P')
			{
				texture = mlx_load_png(GOBLIN);
				game->img.player = mlx_new_image(game->mlx, 75, 75);
				game->img.player = mlx_texture_to_image(game->mlx, texture);
				mlx_delete_texture(texture);
				mlx_image_to_window(game->mlx, game->img.player, x * 75 \
				, y * 75);
			}
			x++;
		}
		y++;
	}
	return (game);
}

mlx_t	*init_image(t_game *game)
{
	char	*str;

	str = ft_itoa(game->move);
	game = init_background(game, 0, 0);
	game = init_coll_and_exit(game, 0, 0, 1);
	game = init_player(game, 0, 0);
	if (BONUS)
	{
		mlx_put_string(game->mlx, "Number of movement: ", \
		game->win_w / 2 - 92, 30);
		game->img.move = mlx_put_string(game->mlx, str, \
		game->win_w / 2 + 97, 30);
	}
	else
		ft_putendl_fd(str, 1);
	return (free(str), game->mlx);
}
