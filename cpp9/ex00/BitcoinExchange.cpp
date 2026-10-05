/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <tle-rhun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 19:19:00 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/10/05 12:09:01 by tle-rhun         ###   ########.fr       */
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
    this->_value = other._value;
    this->_found = other._found;
    this->_date = other._date;
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
bool BitcoinExchange::checkError(void)
{
    if(!this->checkDate(_date))
    {
        std::cout<< "Error: bad input => " << _date<<std::endl;
        return true;
    }
    else if(_found==std::string::npos)
    {
        std::cout<< "Error: No find separator | "<<std::endl;
        return true;
    }
    else if (!BitcoinExchange::checkValue(0, 100, _value))
    {
        if (_value < 0)
            std::cout<< "Error: not a positive number."<<std::endl;
        else
            std::cout<< "Error: too large a number."<<std::endl;
        return true;
    }
    else
        return false;
}
bool BitcoinExchange::getDataFile(std::string separator, std::string first_line)
{
    if(_buffer == first_line || _buffer.empty())
        return false;
    else
    {
        _found = _buffer.find(separator);
        _value = std::atof(&_buffer[_found + separator.size()]);
        _date = _buffer.substr(0, _found);
        return true;
    }
}

void BitcoinExchange::parser(std::ifstream &_ifs_input)
{
    std::ifstream _ifs_csv("data.csv");
    if( _ifs_csv.is_open() != 1 || _ifs_input.is_open() !=1)
    {
        std::cout << "Error: could not open file or the file are no rule for open!" <<std::endl;
        return ;
    }
    while(getline(_ifs_csv, _buffer))
    {
        if(this->getDataFile(",", "date,exchange_rate"))
            _csv.insert(std::pair<std::string, float>(_date,_value ));
    }
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
void BitcoinExchange::display(std::ifstream &_ifs_input)
{
    while(getline(_ifs_input, _buffer))
    {
        if(this->getDataFile(" | ", "date | value") && !BitcoinExchange::checkError())
            std::cout << _date<< " => " << _value << " = " <<  BitcoinExchange::BitcoinPrice(_date)* _value<<std::endl;
    }
    
}

void BitcoinExchange::init(char**av)
{
    std::ifstream _ifs_input(av[1]);
    BitcoinExchange::parser(_ifs_input);
    BitcoinExchange::display(_ifs_input);
    _ifs_input.close();
}
