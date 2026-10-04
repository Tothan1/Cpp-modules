/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <tle-rhun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 19:19:00 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/10/04 21:46:59 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "BitcoinExchange.hpp"

// Default constructor
BitcoinExchange::BitcoinExchange(void)
{
    return ;
}
// Copy constructor
BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
    *this = other;
    return ;
}
// Assignment operator overload
BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
    this->_csv = other._csv;
    this->_input = other._input;
    return (*this);
}
// Destructor
BitcoinExchange::~BitcoinExchange(void)
{
    return ;
}
bool BitcoinExchange::checkValue(float min, float max, float check) const
{
    if(check>max || check<min )
        return false;
    else
        return true;
}
bool BitcoinExchange::checkDate(std::string  &str) const
{
    float day;
    float month;
    float year;

    if(str.size() ==10)
    {
        day = std::atof(str.substr(8, 2).c_str());
        month = std::atof(str.substr(5, 2).c_str());
        year = std::atof(str.substr(0, 4).c_str());
        if(!checkValue(0, 31,day) || !checkValue(0, 12,month) || !checkValue(0, 2026,year) || str[4]!='-' || str[7]!='-')
            return false;
        else
            return true;
    }
    else
        return false;
}
multimap & BitcoinExchange::getContentFile(std::string separator, std::ifstream &ifs, multimap &data, std::string first_line)
{
    std::string buffer;
    std::string date;
	std::string contentFilename;
    std::size_t found;
    float value;
    while(getline(ifs, buffer))
    {
        found = buffer.find(separator);
        if (found!=std::string::npos)
        {
            value = std::atof(&buffer[found + separator.size()]);
            date = buffer.substr(0, found);
            if(!this->checkDate(date))
            {
                date = "Error: bad input";
                value = -1;
            }
            else if (!BitcoinExchange::checkValue(0, 100, value))
            {
                value = -1;
                if (value < 0)
                    date = "Error: not a positive number.";
                else
                    date = "Error: too large a number.";
            }
        }
        else if(buffer != first_line && buffer.empty())
            continue;
        else
        {
            date = "Error: bad input";
            value = -1;
        }
        data.insert(std::pair<std::string, float>(date,value ));
    }
	return data;
}

void BitcoinExchange::parser(char**av)
{
    std::ifstream _ifs_input(av[1]);
    std::ifstream _ifs_csv("data.csv");
    if( _ifs_csv.is_open() != 1 || _ifs_input.is_open() !=1)
    {
        std::cout << "Error: could not open file or the file are no rule for open!" <<std::endl;
        return ;
    }
    this->getContentFile(" | ", _ifs_input, _input, "date | value");
    this->getContentFile(",", _ifs_csv, _csv, "date,exchange_rate");
    
    _ifs_input.close();
    _ifs_csv.close();
}

float BitcoinExchange::BitcoinPrice(std::string reference)
{
    if(_csv[reference])
        return _csv[reference];
    else
    {
        multimap::iterator it = _csv.lower_bound(reference);
        --it;
        return it->second;
    }
}
void BitcoinExchange::display(void)
{
    multimap::iterator it;
    
    for (it = _input.begin(); it != _input.end(); it++)
    {
        std::cout << it->first<< " => " << it->second << " = " <<  BitcoinExchange::BitcoinPrice(it->first)* it->second<<std::endl;
    }
    
}

void BitcoinExchange::init(char**av)
{
    BitcoinExchange::parser(av);
    BitcoinExchange::display();

}
