/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_controls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aude-la- <aude-la-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:31:05 by aude-la-          #+#    #+#             */
/*   Updated: 2024/12/06 21:55:50 by aude-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "initialisation.h"

void	rotate_right(t_data *data, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->cast->dir_x;
	data->cast->dir_x = data->cast->dir_x * cos(rot_speed)
		- data->cast->dir_y * sin(rot_speed);
	data->cast->dir_y = old_dir_x * sin(rot_speed)
		+ data->cast->dir_y * cos(rot_speed);
	old_plane_x = data->cast->plane_x;
	data->cast->plane_x = data->cast->plane_x * cos(rot_speed)
		- data->cast->plane_y * sin(rot_speed);
	data->cast->plane_y = old_plane_x * sin(rot_speed)
		+ data->cast->plane_y * cos(rot_speed);
}

void	rotate_left(t_data *data, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->cast->dir_x;
	data->cast->dir_x = data->cast->dir_x * cos(-rot_speed)
		- data->cast->dir_y * sin(-rot_speed);
	data->cast->dir_y = old_dir_x * sin(-rot_speed)
		+ data->cast->dir_y * cos(-rot_speed);
	old_plane_x = data->cast->plane_x;
	data->cast->plane_x = data->cast->plane_x * cos(-rot_speed)
		- data->cast->plane_y * sin(-rot_speed);
	data->cast->plane_y = old_plane_x * sin(-rot_speed)
		+ data->cast->plane_y * cos(-rot_speed);
}

void	move_forward(t_data *data, double move_speed)
{
	char	player;
	int		map_x;
	int		map_y;
	char	pos;

	player = data->config->orientation;
	map_x = (int)(data->player_x + data->cast->dir_x * move_speed);
	map_y = (int)(data->player_y);
	pos = data->map[map_y][map_x];
	if (pos == '0' || pos == player)
		data->player_x += data->cast->dir_x * move_speed;
	map_x = (int)(data->player_x);
	map_y = (int)(data->player_y + data->cast->dir_y * move_speed);
	pos = data->map[map_y][map_x];
	if (pos == '0' || pos == player)
		data->player_y += data->cast->dir_y * move_speed;
}

void	move_backward(t_data *data, double move_speed)
{
	char	player;
	int		map_x;
	int		map_y;
	char	pos;

	player = data->config->orientation;
	map_x = (int)(data->player_x - data->cast->dir_x * move_speed);
	map_y = (int)(data->player_y);
	pos = data->map[map_y][map_x];
	if (pos == '0' || pos == player)
		data->player_x -= data->cast->dir_x * move_speed;
	map_x = (int)(data->player_x);
	map_y = (int)(data->player_y - data->cast->dir_y * move_speed);
	pos = data->map[map_y][map_x];
	if (pos == '0' || pos == player)
		data->player_y -= data->cast->dir_y * move_speed;
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == A_KEY || keycode == LEFT_KEY)
		rotate_left(data, data->rot_speed);
	else if (keycode == D_KEY || keycode == RIGHT_KEY)
		rotate_right(data, data->rot_speed);
	else if (keycode == W_KEY || keycode == UP_KEY)
		move_forward(data, data->move_speed);
	else if (keycode == S_KEY || keycode == DOWN_KEY)
		move_backward(data, data->move_speed);
	else if (keycode == ESC_KEY)
		close_window(data);
	else if (keycode == PLUS_KEY || keycode == NUM_PLUS_KEY)
	{
		if (data->move_speed * 1.01 < 1.01)
			data->move_speed *= 1.01;
		if (data->rot_speed * 1.01 < 1.01)
			data->rot_speed *= 1.01;
	}
	else if (keycode == MINUS_KEY || keycode == NUM_MINUS_KEY)
	{
		if (data->move_speed / 1.01 > 0.01)
			data->move_speed /= 1.01;
		if (data->rot_speed / 1.01 > 0.01)
			data->rot_speed /= 1.01;
	}
	return (draw_raycast(data), 0);
}
