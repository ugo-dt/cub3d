/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 15:23:54 by ugdaniel          #+#    #+#             */
/*   Updated: 2023/11/26 16:13:02 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include "mlx.h"
# include "config.h"
# include <math.h>

# define RED	0xff0000
# define GREEN	0x00ff00
# define BLUE	0x0000ff
# define WHITE	0xffffff
# define BLACK	0x000000
# define GRAY	0x3b3b3b
# define YELLOW	0xfffb00

typedef struct s_image
{
	char	*img;
	void	*addr;
	int		bpp;
	int		size_line;
	int		endian;
}				t_image;

typedef struct s_window
{
	void	*mlx_ptr;
	void	*window;
	t_image	screen;
	t_pos	size;
	t_pos	half;
}				t_window;

typedef struct s_ray
{
	int		column;
	int		row;
	double	distance;
	int		direction;
	int		side;
	int		height;
	t_pos	ray_pos;
	t_pos	ray_dir;
	t_pos	map_pos;
	t_pos	side_dist;
	t_pos	delta_dist;
	t_pos	step;
	double	wall_x;
	t_pos	floor_wall;
	t_pos	c_floor;
}				t_ray;

typedef struct s_texture
{
	char	*path;
	void	*tex;
	void	*addr;
	t_pos	start;
	t_pos	end;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
}				t_texture;

typedef struct s_sprite_draw
{
	int			sprite_screen;
	t_pos		pos;
	t_pos		transform;
	t_pos		spr_s;
	t_pos		draw_x;
	t_pos		draw_y;
	t_pos		tex_pos;
	int			fact;
	int			draw_y_org;
}				t_sprite_draw;

typedef struct s_sprite
{
	t_pos			pos;
	double			distance;
	t_texture		*tex;
	struct s_sprite	*next;
	struct s_sprite	*sorted;
}				t_sprite;

typedef struct s_keys
{
	int		key_w;
	int		key_a;
	int		key_s;
	int		key_d;
	int		key_left;
	int		key_right;
}				t_keys;

typedef struct s_game
{
	t_window	window;
	t_config	config;
	t_camera	camera;
	t_keys		keys;
	t_texture	textures[TEXTURES];
	t_sprite	*sprites;
	double		camera_x[1920];
	double		depth[1920];
	double		sf_dist[1080];
	double		cos[2];
	double		sin[2];
	int			shadows;
	int			ui;
}				t_game;

int				init_window(t_window *window, t_config *config);
void			clear_window(t_window *window);
void			update_window(t_game *game);

int				draw_rectangle(t_window *window,
					t_pos *p1, t_pos *p2, int color);
void			draw_line(t_window *window, t_pos *p1, t_pos *p2, int color);
int				draw_vertical_line(t_window *win,
					t_pos *start, int length, int color);

void			draw_pixel(t_window *window, t_pos *pos, int color);

int				move_camera_y(t_game *game, int direction);
int				move_camera_x(t_game *game, int direction);
int				rotate_camera(t_game *game, int dir);

void			update_screen(t_game *game);

void			ray_cast(t_game *game, t_ray *ray, int column);

char			get_value_in_map(t_pos *p, t_config *config);
int				in_map(t_pos *p, t_config *config);
char			map_xy(int x, int y, t_config *config);
char			get_value_minimap(t_pos *p, t_config *config);

int				max(int a, int b);
void			draw_wall(t_game *g, t_ray *r);

void			update_ui(t_game *game);

int				distance_shade(int options, int color, double distance);
int				shade_color(int color, double divide);
int				get_tex_color(t_texture *tex, t_pos *pos);

void			draw_sky_floor(t_game *game, t_ray *ray);

void			calculate(t_game *game);

int				load_textures(t_game *game);
void			clear_textures(t_game *game);

void			draw_sprites(t_game *game);

void			clear_sprites(t_sprite **sprites);
void			delete_sprite(t_sprite **sprites, t_pos *pos);
t_sprite		*sort_sprites(t_game *game, t_sprite *sprites);
t_sprite		*add_sorted_sprite(t_sprite **sorted, t_sprite *sprite);
t_sprite		*add_front_sprite(t_sprite **sprites, double distance,
					t_pos *pos, t_texture *tex);
#endif

/*
**  ENGINE_H
*/
