/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 12:01:35 by yingzhan          #+#    #+#             */
/*   Updated: 2026/01/08 12:01:38 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTION_H
# define INTERSECTION_H

# include "minirt_bonus.h"

typedef struct s_intersection
{
	int		valid;
	double	t1;
	double	t2;
}	t_intersection;

typedef struct s_uv
{
	double	u;
	double	v;
}			t_uv;

typedef struct s_axis
{
	t_vec3	u_axis;
	t_vec3	v_axis;
}			t_axis;

typedef struct s_hit
{
	int				hit;
	t_intersection	intersection_points;
	double			t;
	t_vec3			point;
	t_vec3			normal;
	t_object		*object;
	t_color			color;
	t_uv			uv;
}	t_hit;

typedef struct s_cyl_work
{
	t_ray		ray;
	t_cylinder	cy;
	t_vec3		oc;
	double		a;
	double		b;
	double		c;
	double		t1;
	double		t2;
	double		half_h;
}				t_cyl_work;

typedef struct s_cone_work
{
	t_ray	ray;
	t_cone	cone;
	double	cos2;
	double	sin2;
	t_vec3	oc;
	double	a;
	double	b;
	double	c;
	double	t1;
	double	t2;
}		t_cone_work;

t_intersection	ray_sphere_intersection(t_ray ray, t_sphere sphere);
double			define_valid_t_for_sphere(double t1, double t2);
t_hit			intersect_object(t_ray ray, t_object *obj);
void			object_loop(t_object *current, t_hit *hit_point, t_ray *ray);
t_intersection	ray_plane_intersection(t_ray ray, t_plane plane);
t_intersection	ray_cylinder_intersect(t_ray ray, t_cylinder cylinder);
t_vec3			cylinder_normal(t_vec3 point, t_cylinder cylinder);
t_vec3			position(t_ray ray, double t);
void			check_caps(t_cyl_work *w, t_intersection *intersect);
t_intersection	ray_cone_intersect(t_ray ray, t_cone cone);
t_vec3			cone_normal(t_vec3 point, t_cone cone);

// Lighting and shade
t_color			calculate_color(t_hit *hit, t_scene *scene);
void			calculate_ambient(t_color *color, t_scene *scene);
void			add_diffuse(t_color *c, double cosine, t_light *l);
int				in_shadow(t_vec3 hit_to_light,
					t_scene *scene, t_hit *hit, t_light *l);
double			calc_intensity(double cosine, t_hit *h,
					t_vec3 hit_to_light, t_scene *s);
void			add_specular(t_color *c, t_light *l,
					t_hit *h, double intensity);

// Checkerboard, bump texture
t_color			get_cb_color(t_hit *hit);
t_uv			calculate_uv(t_hit *hit);
t_color			sample_xpm_texture(t_hit *hit);

#endif