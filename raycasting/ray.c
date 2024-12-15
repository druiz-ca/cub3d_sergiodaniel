/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel <daniel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 11:51:53 by daniel            #+#    #+#             */
/*   Updated: 2024/12/15 14:14:57 by daniel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* establecer el angulo del jugador: parece que segun a la dir donde apunte
se establece un ángulo en concreto, empezando en 0 cuando apunta al ESTE ? y
va aumentando en el sentido de las agujas del reloj */
void	set_player_angle(t_data *data, char c)
{
	if (c == 'N')
		data->player.angle = 270;
	if (c == 'S')
		data->player.angle = 90;
	if (c == 'W')
		data->player.angle = 180;
	if (c == 'E')
		data->player.angle = 0;
}

/* inicializa los ángulos de los rayos del jugador, distribuyéndolos 
uniformemente a lo largo del campo de visión del jugador y asegurándose de que
todos los ángulos estén dentro del rango adecuado.*/
void    ray_init(t_data *data)
{
    double  fov_rad;
    double  angle_rad;
    int     i;

    fov_rad = FOV * M_PI / 180;
    angle_rad = data->player.angle * M_PI / 180;
    i = 0;
    while (i < WIDTH)
    {
        data->player.ray[i].angle = angle_rad - (fov_rad / 2) \
            + ((fov_rad / WIDTH) * i);
        data->player.ray[i].angle_ret = data->player.ray[i].angle;
        if (data->player.ray[i].angle < 0)
            data->player.ray[i].angle += 2 * M_PI;
        i++;
    }
}