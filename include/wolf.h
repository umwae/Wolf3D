/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoyle <adoyle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:55:16 by jsteuber          #+#    #+#             */
/*   Updated: 2019/07/06 20:12:23 by adoyle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H
# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"
# include "../minilibx_macos/mlx.h"

# define WIN_WIDTH 1000
# define WIN_HIGHT 1000

typedef struct		s_minimap//Для миникарты1
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
}									t_minimap;

typedef struct		s_vec
{
	double			x;
	double			y;
	double			dx;
	double			dy;
	double			len;
}									t_vec;

typedef struct		s_flc
{
	double			c_dist;
	double			wght;
	double			c_flrx;
	double			c_flry;
	int				flrtx;
	int				flrty;
	int				c;
}									t_flc;

typedef struct		s_sprq
{
	double			sprx;
	double			spry;
	double			invd;
	double			tx;
	double			ty;
	double			mv;
	int				mvspr;
	int				sprh;
	int				sprw;
	int				bspr;
	int				sprscrx;
	int				u;
	int				v;
	int				i;
	int				st;
	int				nd;
	int				espr;
	int				strp;
}									t_sprq;

typedef struct		s_obj
{
	double		x;
	double		y;
	int			tex;
	double		dist;
}									t_obj;

typedef struct		s_core
{
	void			*mlx;
	void			*win;
	int				map_w;
	int				map_h;
	t_minimap	*vs;
	double		rotation;
	char			*img_ptr;
	void			*image;
	int				linesize;
	int     	bts;
	// int				dragl;
	// int				dragr;
	// double			x_mem;
	// double			y_mem;
	int				**tiles;//Карта
	t_vec			player;//Вектор игрока
	t_vec			dir;//Вектор направления взгляда
	t_vec			plane;//Вектор плоскости экрана
	double		dist;//Расстояние до места попадания луча
	int				objcl;//Цвет для режима подсветки граней
	double		castx;//Место на плоскости экрана через которое кастуется луч
	double		casty;//Место на плоскости экрана через которое кастуется луч
	void			*text;
	int				rcurr;//Номер текущего луча (справа налево)
	char			wall;
	int     	*addr;
	double		hitx;//Место попадания луча
	double		hity;//Место попадания луча
	int				endian;
	int				bpp;
	double		mdist[WIN_WIDTH];
	t_obj			*objarr;//Массив объектов/спрайтов по дальности
	int				coins;//Бонусные очки
	int				spritesnum;//Текущее число спрайтов
	int				**textures;//Все текстуры разом
	int				wtexnum;//Номер текстуры стены, в которую попал луч
}									t_core;

# define ROTATION -0.1
# define SPEED 0.3
# define MAX_DIST 35//!!!!!!!!!!!!!!!!!!!!
# define TEXSIZE 700
# define TEXOBJSIZE 592
# define TEXNUM 11//Число текстур
# define SPRITESNUM 3//Число спрайтов
# define FLOORTEX 2//Номер текстуры пола
# define CEILTEX 8 //Текстура потолка

int					init(char *argv, t_core *cr);
int					hooks(t_core *cr);
void				get_map(int fd0, int fd, t_core *cr);
void				visual(t_core *cr);
void				img_new(t_core *cr);
void				img_pxl(t_core *cr, int x, int y, int color);
int					key_action(int keycode, t_core *cr);
void				err_ex(int pr);
int					getgrad(int color1, int color2, double passed);
int					mouse_press(int button, int x, int y, t_core *cr);
int					mouse_release(int button, int x, int y, t_core *cr);
int					mouse_move(int x, int y, t_core *cr);
void				make_cast(t_core *cr);
void				bresenham(t_core *cr);
void				dda2(t_core *cr);
void				sprite(t_core *cr);
void				bresenham(t_core *cr);
int					wall_check(t_core *cr, double x, double y);
void				transform(t_core *cr, double *x0, double *y0, char dir);
void				tile_color(int wt, t_core *cr);
void				calc_line(t_core *cr);
void				draw_rectangle(t_core *cr, int x, int y, int xlen, int ylen);
void				minimap(t_core *cr);
void				minimap_init(t_core *cr);
void				vector_init(t_core *cr);
char				checker(t_core *cr, double x, double y, int **tiles);
void				draw(t_core *cr, int ray);
void				sort_obj(t_core *cr);
void				check_obj(t_core *cr);
void				draw_gui(t_core *cr);
void				obj_init(t_core *cr);
//
int				getgrad(int color1, int color2, double passed);
void			get_obj(t_core *cr, char *argv);

#endif
