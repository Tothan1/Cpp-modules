/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <tle-rhun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 16:40:41 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/10/05 16:49:58 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
int main (int ac, char **av)
{
	if(ac==2)
	{
		RPN calcul;
		calcul.global(av);
	}

	else
	{
		std::cout<< "Please enter one argument!" <<std::endl;
		return 1;
	}
}