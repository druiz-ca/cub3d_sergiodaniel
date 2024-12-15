/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angles_maker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel <daniel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 11:24:31 by daniel            #+#    #+#             */
/*   Updated: 2024/12/15 09:56:51 by daniel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



/* determina el punto de impacto de un rayo con una pared, maneja el impacto 
y calcula las distancias necesarias para renderizar correctamente la escena 
en el juego. */
void    find_ray_hit_pont(t_data *data, t_ray *ray)
{
    // FT que inicializa las variables del rayo
    init_ray_variables(data, ray);

    // FT que calcula la distancia lateral entre el jugador y la pared más cercana
    calculate_side_distance(data, ray);

    // FT que calcula el punto de impacto del rayo en el mapa
    dda_loop(data, ray);

    // Si el rayo impacta en una pared vertical
    if (ray->flag == 0)
    {
        ray->hit = ray->pos_y + (ray->perp_wall_dist * ray->ray_dir_y);
        ver_pixel_impact(ray); // PTE cambiar el nombre a vertical
    }
    // Si el rayo impacta en una pared horizontal
    else
    {
        ray->hit = ray->pos_x + (ray->perp_wall_dist * ray->ray_dir_x);    
        hor_pixel_impact(ray); // PTE cambiar el nombre a horizontal
    }
    // FT que calcula la distancia hipotenusa entre el jugador y la pared más cercana
    calculate_hypotenuse_distance(ray);

    // FT que calcula la distancia vertical entre el jugador y la pared más cercana
    calculate_vertical_distance(data, ray);
}

/* Ft q imprime los rayos que el jugador lanza en el juego, los cuales se 
utilizan para determinar lo que el jugador ve en la pantalla */
void    print_ray(t_data *data, t_player *player)
{
    int i;

    // Inicializa los rayos del jugador
    ray_init(data);
    i = 0;

    // Mientras el rayo no haya llegado al final (WIDTH) de la pantalla
    while (i < WIDTH)
    {
        // FT que busca el punto de impacto del rayo en el mapa
        find_ray_hit_point(data, &player->ray[i]);

        // FT que pinta la columna de la pared correspondiente al rayo en la 
        //posición i.
        print_wall_column(data, &player->ray[i], i);
        i++;
    }
}