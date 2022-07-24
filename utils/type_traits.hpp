/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:46:06 by jabenjam          #+#    #+#             */
/*   Updated: 2022/07/25 00:37:58 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{
	template<bool B, class T = void>
	struct enable_if {};

	template<class T>
	struct enable_if<true, T> { typedef T type; };

	template<class T>
	struct is_integral { static const bool value = false; };

	template<>
	struct is_integral<bool> { static const bool value = true; };

	template<>
	struct is_integral<char> { static const bool value = true; };

	template<>
	struct is_integral<wchar_t> { static const bool value = true; };

	template<>
	struct is_integral<short> { static const bool value = true; };

	template<>
	struct is_integral<int> { static const bool value = true; };

	template<>
	struct is_integral<long> { static const bool value = true; };

	template<>
	struct is_integral<long long> { static const bool value = true; };
}