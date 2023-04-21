/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 08:39:23 by wdelaros          #+#    #+#             */
/*   Updated: 2023/04/18 15:01:21 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include "MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>

# define MOVE 75

# define TITLE "Subway"

# define WOOD "img/wood.png"
# define WALL "img/wall.png"
# define DOOR "img/door.png"
# define GOBLIN "img/goblin.png"
# define SUBWAY "img/subway.png"

# ifndef BONUS
#  define BONUS 0
# endif

typedef struct s_map
{
	int		x;
	int		xp;
	int		y;
	int		yp;
	int		back;
	int		nbr_e;
	int		nbr_e2;
	int		nbr_p;
	int		nbr_p2;
	int		nbr_c;
	int		nbr_c2;
	char	**map;
	char	**map_tmp;
}				t_map;

typedef struct s_img
{
	mlx_image_t	**back;
	mlx_image_t	*exit;
	mlx_image_t	*coll;
	mlx_image_t	*player;
	mlx_image_t	*move;
}				t_img;

typedef struct s_game
{
	mlx_t	*mlx;
	t_map	map_t;
	t_img	img;
	int		move;
	int		oldmove;
	int		coll;
	int		win_h;
	int		win_w;
	int		x;
	int		y;
}				t_game;

/*so_long.c*/
void	keyhook(mlx_key_data_t keydata, void *param);

/*parse.c*/
int		parse_map(char *argv[], t_map *map);

/*init.c*/
mlx_t	*init_image(t_game *game);
t_game	*init_coll_and_exit(t_game *game, int x, int y, int exit);

/*flood_fill.c*/
void	flood_fill(char **tab, t_map *map);
void	valid_map(t_map *map, int x, int y);

/*so_long_utils.c*/
void	movement_number(t_game *game);
void	if_error(char *str);
void	ft_exit(t_game *game);
void	free_array(char **array);
void	malloc_map(t_map *map, int x, int y);

#endif