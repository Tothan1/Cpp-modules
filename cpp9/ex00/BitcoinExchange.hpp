/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <tle-rhun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 19:18:50 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/10/05 11:46:25 by tle-rhun         ###   ########.fr       */
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
        //attribute for collect data
        std::string _buffer;
        float _value;
        std::string _date;
        std::size_t _found;
    public:
        BitcoinExchange(void);
        BitcoinExchange(const BitcoinExchange& other);
        BitcoinExchange &operator=(const BitcoinExchange &other);
        ~BitcoinExchange();
        bool getDataFile(std::string separator, std::string first_line);
        bool checkError(void);
        bool checkDate(std::string &str) const;
        bool checkValue(float min, float max, float check) const;
        void display(std::ifstream &_ifs_input);
        void init(char **av);
        float BitcoinPrice(std::string reference);
        void parser(std::ifstream &_ifs_input);
};

#endif

