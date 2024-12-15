/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angles_maker_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel <daniel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 09:57:24 by daniel            #+#    #+#             */
/*   Updated: 2024/12/15 10:56:21 by daniel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

/* configura las variables iniciales necesarias para el cálculo de la 
trayectoria del rayo, incluyendo su posición, dirección y pasos en los ejes 
x e y.*/
void    init_ray_variables(T_data *data, t_ray *ray)
{
    // Inicializa la posición del rayo en el mapa en el eje x con la 
    // posición actual del jugador
    ray->map_x = data->player.map_x;

    // Inicializa la posición del rayo en el mapa en el eje y con la
    // posición actual del jugador
    ray->map_y = data->player.map_y;

    // Inicializa la dirección del rayo en el eje x con el coseno del ángulo
    ray->ray_dir_x = cos(ray->angle);

    // Inicializa la dirección del rayo en el eje y con el seno del ángulo
    ray->ray_dir_y = sin(ray->angle);

    // Calcula la distancia que el rayo debe recorrer en el eje x para 
    // pasar de una línea de cuadrícula a la siguiente.
    ray->delta_dist_x = 1 / fabs(ray->ray_dir_x);

    // Calcula la distancia que el rayo debe recorrer en el eje y para
    // pasar de una línea de cuadrícula a la siguiente.
    ray->delta_dist_y = 1 / fabs(ray->ray_dir_y);

    // Inicializa la posición del rayo en el eje x con la posición actual 
    // del jugador.
    ray->pos_x = data->player.pos_x;

    // Inicializa la posición del rayo en el eje y con la posición actual
    // del jugador.
    ray->pos_y = data->player.pos_y;

    // Inicializa el paso del rayo en el eje x a 0.
    ray->step_x = 0;

    // Inicializa el paso del rayo en el eje y a 0.
    ray->step_y = 0;

    // Determina la dirección del paso en el eje x:
    // Si la dirección del rayo en el eje x es negativa, el paso es -1
    if (ray->ray_dir_x < 0)
        ray->step_x = -1;
    
    // Si la dirección del rayo en el eje x es positiva, el paso es 1
    else
        ray->step_x = 1;

    // Determina la dirección del paso en el eje y:
    // Si la dirección del rayo en el eje y es negativa, el paso es -1
    if (ray->ray_dir_y < 0)
        ray->step_y = -1;

    // Si la dirección del rayo en el eje y es positiva, el paso es 1
    else
        ray->step_y = 1;
    ray->flag = 0;
}