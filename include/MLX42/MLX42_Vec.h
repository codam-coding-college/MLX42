/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   MLX42_Vec.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/01 19:23:35 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/01/01 22:15:44 by W2Wizard      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX42_VEC_H
# define MLX42_VEC_H

//= Int =//

// A 2 integer component.
typedef union u_IVec2
{
	struct
	{
		int	x;
		int	y;
	};
	int	raw[2];
}	t_IVec2;

// A 3 integer component.
typedef union u_IVec3
{
	struct
	{
		int	x;
		int	y;
		int	z;
	};
	int	raw[3];
}	t_IVec3;

// A 4 integer component.
typedef union u_IVec4
{
	struct
	{
		int	x;
		int	y;
		int	z;
		int	w;
	};
	int	raw[4];
}	t_IVec4;

//= Float =//

// A 2 float component.
typedef union u_FVec2
{
	struct
	{
		float	x;
		float	y;
	};
	float	raw[2];
}	t_FVec2;

// A 3 float component.
typedef union u_FVec3
{
	struct
	{
		float	x;
		float	y;
		float	z;
	};
	float	raw[3];
}	t_FVec3;

// A 4 float component.
typedef union u_FVec4
{
	struct
	{
		float	x;
		float	y;
		float	z;
		float	w;
	};
	float	raw[4];
}	t_FVec4;

#endif