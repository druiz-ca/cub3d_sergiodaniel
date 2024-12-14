/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_floor_ceiling.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel <daniel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 10:31:16 by daniel            #+#    #+#             */
/*   Updated: 2024/12/14 10:49:17 by daniel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Ft para pintar el suelo y el techo de dos colores diferentes para
diferenciarlos */
int	print_floor_ceiling(t_data *data)
{
    int	w;
    int	h;

    w = 0;
    while (w < WIDTH)
    {
        h = 0;
        while (h < HEIGHT)
        {
            // si está en la primera mitad del mapa, pinta el suelo de un color
            if (h < HEIGHT / 2)
                mlx_put_pixel(data->background, w, h++, data->textures.c_color);
            // sino, pinta el techo de otro color
            else
                mlx_put_pixel(data->background, w, h++, data->textures.f_color);
        }
        w++;
    }
    return (SUCCESS);
}