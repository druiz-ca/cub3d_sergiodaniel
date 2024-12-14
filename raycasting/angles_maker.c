/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angles_maker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel <daniel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 11:24:31 by daniel            #+#    #+#             */
/*   Updated: 2024/12/14 11:50:37 by daniel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Ft q renderiza los rayos que el jugador lanza en el juego, los cuales se 
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