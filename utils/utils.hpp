/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 14:18:40 by jabenjam          #+#    #+#             */
/*   Updated: 2022/07/29 21:41:04 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <limits>
#include <vector>
#include <functional>
#include <memory>
#include <stdexcept>
#include <limits>

#define RESET		"\033[0m"			/* Reset*/
#define N_BLACK		"\033[30m"			/* Black */
#define N_RED		"\033[31m"			/* Red */
#define N_GREEN		"\033[32m"			/* Green */
#define N_YELLOW	"\033[33m"			/* Yellow */
#define N_BLUE		"\033[34m"			/* Blue */
#define N_MAGENTA	"\033[35m"			/* Magenta */
#define N_CYAN		"\033[36m"			/* Cyan */
#define N_WHITE		"\033[37m"			/* White */
#define B_BLACK		"\033[1m\033[30m"	/* Bold Black */
#define B_RED		"\033[1m\033[31m"	/* Bold Red */
#define B_GREEN		"\033[1m\033[32m"	/* Bold Green */
#define B_YELLOW	"\033[1m\033[33m"	/* Bold Yellow */
#define B_BLUE		"\033[1m\033[34m"	/* Bold Blue */
#define B_MAGENTA	"\033[1m\033[35m"	/* Bold Magenta */
#define B_CYAN		"\033[1m\033[36m"	/* Bold Cyan */
#define B_WHITE		"\033[1m\033[37m"	/* Bold White */
#define L_RED		"\033[91m"			/* Light Red */
#define L_GREEN		"\033[92m"			/* Light Green */
#define L_YELLOW	"\033[93m"			/* Light Yellow */
#define L_BLUE		"\033[94m"			/* Light Blue */
#define L_MAGENTA	"\033[95m"			/* Light Magenta */
#define L_CYAN		"\033[96m"			/* Light Cyan */

enum color {
	E_BLACK,
	E_RED
};

enum direction {
	E_LEFT,
	E_RIGHT
};

#define COUT(COLOR, DATA) (std::cout << COLOR << DATA << std::endl << RESET)
#define COUT_NC(DATA) (std::cout << DATA << std::endl)
#define CERR(COLOR, DATA) (std::cerr << COLOR << DATA << "\n" << RESET)