/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <tle-rhun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 19:18:50 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/10/04 21:10:52 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP
# include <iostream>
# include <map>
# include <utility>
# include <string>
#include <fstream>
#include <cstdlib>
#include <algorithm>

typedef std::map<std::string, float> multimap;
class BitcoinExchange
{
    private:
        multimap _csv;
        multimap _input;
    public:
        BitcoinExchange(void);
        BitcoinExchange(const BitcoinExchange& other);
        BitcoinExchange &operator=(const BitcoinExchange &other);
        ~BitcoinExchange();
        multimap & getContentFile(std::string separator, std::ifstream &ifs, multimap & data, std::string first_line);
        bool checkDate(std::string &str) const;
        bool checkValue(float min, float max, float check) const;
        void display(void);
        void init(char **av);
        float BitcoinPrice(std::string reference);
        void parser(char**av);
};

#endif

