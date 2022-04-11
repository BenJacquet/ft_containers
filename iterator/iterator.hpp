/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:00:08 by jabenjam          #+#    #+#             */
/*   Updated: 2022/04/11 16:33:20 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{
	template <typename _Category, typename _Tp, typename _Distance = ptrdiff_t,
			  typename _Pointer = _Tp *, typename _Reference = _Tp &>
	struct iterator
	{

	}

	/// Partial specialization for pointer types.
	template <typename _Tp>
	struct iterator_traits<_Tp *>

	/// Partial specialization for const pointer types.
	template <typename _Tp>
	struct iterator_traits<const _Tp *>
};