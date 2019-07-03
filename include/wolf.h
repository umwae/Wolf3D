/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:55:16 by jsteuber          #+#    #+#             */
/*   Updated: 2019/07/02 22:01:49 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H
# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"
# include "../minilibx_macos/mlx.h"

# define WIN_WIDTH 1000
# define WIN_HIGHT 1000

typedef struct		s_visual//Для миникарты1
{
	int				x_i;
	int				y_i;
	int				x2_i;
	int				y2_i;
	int				x_offset;
	int				y_offset;
	int				vcolor;
	int				mmsize;
	int				gridsize;
}					t_visual;

typedef struct		s_vec
{
	double			x;
	double			y;
	double			dx;
	double			dy;
	double			len;
}					t_vec;

typedef struct		s_spr
{
	double			x;
	double			y;
	int				tex;
	int				texsize;
	//
	double			sprdist;
	char			type;
	int				val;
}					t_spr;

typedef struct		s_win
{
	void			*mlx;
	void			*win;
	int				x_len;//заменить на m_width
	int				y_len;//заменить на m_hight
	t_visual		*vs;
	double			rotation;
	char			*img_ptr;
	void			*image;
	int				linesize;
	int     		bts;
	// int				dragl;
	// int				dragr;
	// double			x_mem;
	// double			y_mem;
//
	// int				zoom;
	int				**tiles;//Карта
	t_vec			player;//Вектор игрока
	t_vec			dir;//Вектор направления взгляда
	t_vec			plane;//Вектор плоскости экрана
	double			dist;//Расстояние до места попадания луча
	int				objcl;//Цвет для режима подсветки граней
	double			castx;//Место на плоскости экрана через которое кастуется луч
	double			casty;//Место на плоскости экрана через которое кастуется луч
	//
	void	*text;
	int		*addrtext;
	int		*floortext;//текстура пола
	int		rcurr;//Номер текущего луча (справа налево)
	char		wall;
	int     *addr;
	double		hitx;//Место попадания луча
	double		hity;//Место попадания луча
	int			endian;
	int			bpp;
	//
	double		mdist[WIN_WIDTH];
	//
	t_spr			*sprOrder;//Массив спрайтов по дальности
	int			coins;//Бонусные очки
	int			spritesnum;//Реальное число спрайтов
	int			**textures;//Все текстуры разом
	int			trash;
}					t_win;

# define ROTATION -0.1
# define SPEED 0.1
# define MAX_DIST 35
//
# define TEXSIZE 720
# define TEXNUM 2//Число текстур
# define SPRITESNUM 3//Начальное число спрайтов
// # define MAXHP 100

int					init(char *argv, t_win *cr);
int					hooks(t_win *cr);
void				get_map(int fd0, int fd, t_win *cr);
void				visual(t_win *cr);
void				img_new(t_win *cr);
void				img_pxl(t_win *cr, int x, int y, int color);
int					key_action(int keycode, t_win *cr);
void				err_ex(int pr);
int					mouse_press(int button, int x, int y, t_win *cr);
int					mouse_release(int button, int x, int y, t_win *cr);
int					mouse_move(int x, int y, t_win *cr);
void				make_cast(t_win *cr);
void				bresenham(t_win *cr);
void				dda2(t_win *cr);
void				sprite(t_win *cr);
void				bresenham(t_win *cr);
int					wall_check(t_win *cr, double x, double y);
void				transform(t_win *cr, double *x0, double *y0, char dir);
void				tile_color(int wt, t_win *cr);
void				calc_line(t_win *cr);
void				draw_rectangle(t_win *cr, int x, int y, int xlen, int ylen);
void				minimap(t_win *cr);
void				minimap_init(t_win *cr);
void				vector_init(t_win *cr);
//
char	checker(t_win *cr, double x, double y, int **tiles);
// void	render(t_map *map);
void	draw(t_win *cr, int ray);
void				sort_sprites(t_win *cr);
void				check_obj(t_win *cr);
void				draw_gui(t_win *cr);
void				obj_init(t_win *cr);

#endif
