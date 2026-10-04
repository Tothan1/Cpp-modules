/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <tle-rhun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 19:17:44 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/10/04 18:49:23 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
int main (int ac, char **av)
{
	if(ac == 2)
	{
		BitcoinExchange exchange;
		exchange.init(av);
	}
	else
	{
		std::cout << "Please enter one argument!" <<std::endl;
	}
}