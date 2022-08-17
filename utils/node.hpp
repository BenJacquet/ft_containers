/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 17:30:47 by jabenjam          #+#    #+#             */
/*   Updated: 2022/08/17 11:35:14 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include "utils.hpp"
#include "enums.hpp"

namespace ft
{
	template <class value_type>
	struct node
	{
		node(const value_type &key) : key_val(key) {}

		node		*parent;
		node		*left;
		node		*right;
		int			color;
		value_type	key_val;
	};
}