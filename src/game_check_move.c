/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_check_move.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel <daniel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 09:23:51 by daniel            #+#    #+#             */
/*   Updated: 2024/12/14 10:24:17 by daniel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Comprueba si el movimiento que quiere hacer es posible, es decir, que no
choque con nigún muro. Para ello calcula una variación en las 4 direcciones
de 0,25 para evitar que se quede en los bordes de las celdas, por lo tanto, 
calcula alrededor del movimiento que quiere hacer que no haya nada a 0,25 de
distancia */
bool	check_move_is_valid(t_data *data, double move_x, double move_y)
{
    int	check_x;
    int	check_x2;
    int	check_y;
    int	check_y2;

    // Calcula la posición en x e y con un margen de 0,25 en las 4 direcciones
    // Usa la función floor para redondear al entero más cercano hacia abajo
    // divide el movimiento entre 64 (tamaño de cada celda del mapa)
    check_x = (int)floor((data->player.pos_x + 0.25) + (move_x / 64));
    check_x2 = (int)floor((data->player.pos_x - 0.25) + (move_x / 64));
    check_y = (int)floor((data->player.pos_y + 0.25) + (move_y / 64));
    check_y2 = (int)floor((data->player.pos_y - 0.25) + (move_y / 64));

    // Comprueba si la posición donde quiere moverse en el mapa es un muro, lo 
    // hace en las 4 direcciones posibles con el margen de 0,25
    if (data->map.map[check_y][check_x] == '1')
        return (false);
    if (data->map.map[check_y2][check_x] == '1')
        return (false);
    if (data->map.map[check_y][check_x2] == '1')
        return (false);
    if (data->map.map[check_y2][check_x2] == '1')
        return (false);
    return (true);
}

/* Actualizar el movimiento en el mapa, comporbando antes que sea correcto */
bool	update_move(t_data *data, double move_x, double move_y)
{
    // Comprueba primero si el movimiento es válido
    if (!check_move_is_valid(data, move_x, move_y))
        return (false);
    
    // Actualiza la posición en el mapa en x e y, y dividiendo el movimiento
    // entre 64 (tamaño de cada cuadro del mapa)
    data->player.map_x = data->player.pos_x + move_x / 64;
    data->player.map_y = data->player.pos_y + move_y / 64;
    return (true);
}