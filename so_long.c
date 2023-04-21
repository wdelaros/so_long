/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:14:38 by wdelaros          #+#    #+#             */
/*   Updated: 2023/04/18 13:53:27 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	replace_coll(t_game *game, int x, int y)
{
	game->coll--;
	x /= MOVE;
	y /= MOVE;
	game->map_t.map[y][x] = '0';
	mlx_delete_image(game->mlx, game->img.coll);
	game = init_coll_and_exit(game, 0, 0, 0);
}

static void	move(t_game *game, t_img img, int x, int y)
{
	int	i;

	i = 0;
	if (game->map_t.map[(img.player->instances[0].y + (y * MOVE)) / MOVE] \
	[(img.player->instances[0].x + (x * MOVE)) / MOVE] != '1')
	{
		img.player->instances[0].x += x * MOVE;
		img.player->instances[0].y += y * MOVE;
		game->move++;
	}
	if (game->coll >= 1)
	{
		while (i < game->coll && (img.player->instances[0].x != img.coll-> \
		instances[i].x || img.player->instances[0].y != \
		img.coll->instances[i].y))
			i++;
		if (img.player->instances[0].x == img.coll->instances[i].x \
		&& img.player->instances[0].y == img.coll->instances[i].y)
			replace_coll(game, img.coll->instances[i].x, \
			img.coll->instances[i].y);
	}
	if (img.player->instances[0].x == img.exit->instances[0].x && \
	img.player->instances[0].y == img.exit->instances[0].y && !game->coll)
		ft_exit(game);
}

void	keyhook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = param;
	movement_number(game);
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if ((keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP))
			move(game, game->img, 0, -1);
		else if ((keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT))
			move(game, game->img, -1, 0);
		else if ((keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN))
			move(game, game->img, 0, 1);
		else if ((keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT))
			move(game, game->img, 1, 0);
		else if (keydata.key == MLX_KEY_ESCAPE)
			ft_exit(game);
	}
}

static t_game	init_value(t_game game)
{
	game.win_w = (game.map_t.x) * MOVE;
	game.win_h = (game.map_t.y) * MOVE;
	game.img.back = ft_calloc(3, sizeof(t_img *));
	game.move = 0;
	return (game);
}

int	main(int argc, char *argv[])
{
	t_game	game;

	if (argc != 2 || ft_isfile(argv[1]) != 3)
		if_error("Error\nWrong input: [./so_long <map/mapname.ber>]");
	parse_map(argv, &game.map_t);
	game = init_value(game);
	game.mlx = mlx_init(game.win_w, game.win_h, TITLE, false);
	if (!game.mlx)
		exit(EXIT_FAILURE);
	game.mlx = init_image(&game);
	mlx_key_hook(game.mlx, keyhook, &game);
	mlx_loop(game.mlx);
	ft_exit(&game);
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}
