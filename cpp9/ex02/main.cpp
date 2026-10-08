/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <tle-rhun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 16:28:51 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/10/08 17:46:53 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main (int ac, char **av)
{
	if(ac > 2)
	{
		PmergeMe sort;
		sort.global(ac, av);
	}
	else
	{
		std::cerr<< "Please enter minimum 2 argument!" <<std::endl;
		return 1;
	}
}