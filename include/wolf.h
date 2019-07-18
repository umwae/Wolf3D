/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:55:16 by jsteuber          #+#    #+#             */
/*   Updated: 2019/07/18 18:38:08 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H
# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"
# include "../minilibx_macos/mlx.h"

# define WIN_WIDTH 1500
# define WIN_HIGHT 1200

typedef struct		s_coo
{
	int				x;//Для ужимания под норму
	int				y;
}					t_coo;

typedef struct		s_minimap//Для миникарты
{
	int				x_i;
	int				y_i;
	int				x2_i;
	int				y2_i;
	int				dx;//Для брезенхема
	int				dy;
	int				x_offset;
	int				y_offset;
	int				vcolor;
	int				mmsize;
	int				mmsize_y;
	int				gridsize;
}									t_minimap;

typedef struct		s_dda
{
	int				mapx;
	int				mapy;
	double			sidedx;
	double			sidedy;
	double			deltadx;
	double			deltady;
	int				stepx;
	int				stepy;
	int				hit;
	int				side;
	double			wx;
	double			flxwll;
	double			flywll;
}									t_dda;

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
	char			*mm_img_ptr;//Для минимапы
	void			*mm_image;//Для минимапы
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
	void			*img_switcher;//Указатель в какой имейдж печатать пиксель
	void			(*print_func)(void *cr, int x, int y, int color);//Указатель на то какой функцией печатать
	int				dodraw;//1 если рисовать куб, 0 если не рисовать
	int				**textrash;//Сохраняем сюда указатели на имейджи чтобы не выглядело как утечка
	double			tmp_p_x;
	double			tmp_p_y;//Для actions
	int				fd3;
	int				fd4;
	int				count;
}									t_core;

# define PLAYER_START_X 1.5//Положение игрока
# define PLAYER_START_Y 1.5//Положение игрока
# define ROTATION -0.1
# define SPEED 0.1
# define MAXDIST 30//Дальность прорисовки
# define TEXSIZE 700
# define TEXOBJSIZE 592
# define TEXNUM 11//Число текстур
# define SPRITESNUM 6//Число спрайтов
# define FLOORTEX 2//Номер текстуры пола
# define CEILTEX 8 //Текстура потолка
# define MM_COLOR 0x34495E //Цвет карты
# define VIEWDIST 2//Расстояние, с которого начинается затемнение
# define MMSIZE 300//Размер миникарты
void				init(char *argv, t_core *cr);
int					hooks(t_core *cr);
void				get_map(int fd0, int fd, t_core *cr);
void				visual(t_core *cr);
void				img_new(t_core *cr);
void				img_pxl(void *td, int x, int y, int color);
int					key_action(int keycode, t_core *cr);
void				err_ex(int pr);
int					getgrad(int color1, int color2, double passed);
void				make_cast(t_core *cr);
void				ddainit(t_core *cr, t_dda *dda);
void				ddafour(t_core *cr, t_dda *dda);
void				ddathree(t_core *cr, t_dda *dda, int i);
void				dda2(t_core *cr);
void				sprite(t_core *cr);
void				bresenham(t_core *cr);
void				transform(t_core *cr, double *x0, double *y0, char dir);
void				draw_rectangle(t_core *cr, t_coo xy, int xlen, int ylen);
void				minimap(t_core *cr);
void				minimap_init(t_core *cr);
void				vector_init(t_core *cr);
void				draw(t_core *cr, int ray);
void				calc_dist(t_core *cr);
void				sort_obj(t_core *cr);
void				check_obj(t_core *cr);
void				draw_gui(t_core *cr);
void				obj_init(t_core *cr);
void				get_obj(t_core *cr, char *argv);
int					getgrad(int color1, int color2, double passed);
void				img_minimap_new(t_core *cr);
void				pxl_put_wrap(void *td, int x, int y, int color);
int					red_button(t_core *pr);
void				draw_objects(t_core *cr);
void				draw_player(t_core *cr);
void				check_borders(t_core *cr);

#endif
