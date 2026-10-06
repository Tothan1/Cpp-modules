#include "RPN.hpp"

// Default constructor
RPN::RPN(void)
{
    return ;
}

// Copy constructor
RPN::RPN(const RPN &other)
{
    (void) other;
    return ;
}

// Assignment operator overload
RPN &RPN::operator=(const RPN &other)
{
    (void) other;
    return (*this);
}

// Destructor
RPN::~RPN(void)
{
    return ;
}
 //Exception
char const * RPN::Overflow::what(void) const throw()
{
    return "This calcul done Overflow for the type int!";
}
char const * RPN::DivisionByZero::what(void) const throw()
{
    return "This calcul done division by zero!";
}
bool RPN::CheckOverflow(double result)
{
    if (result>= INT_MIN && result<= INT_MAX)
        return true;
    else
        return false;
}
//Operator
int RPN::Addition(int value1, int value2)
{
    if(CheckOverflow(value1 + value2))
        return (value1 + value2);
    else
        throw RPN::Overflow();
}
int RPN::Multiplication(int value1, int value2)
{
    if(CheckOverflow(value1 * value2))
        return (value1 * value2);
    else
        throw RPN::Overflow();
}
int RPN::Division(int value1, int value2)
{
    if( value2 == 0)
        throw RPN::DivisionByZero();
    else if(!CheckOverflow(value1 / value2))
        throw RPN::Overflow();
    else
        return (value1 / value2);
}
//Other
bool RPN::isOperator(int i)
{
    if(_input[i] == '+' ||_input[i] == '-' || _input[i] == '/' || _input[i] == '*')
        return true;
    else
        return false;
}
bool RPN::parsing()
{
    for (size_t i = 0; i < _input.size(); i++)
    {
        if(std::isdigit(_input[i]) || RPN::isOperator(i))
        {
            if(_input[i+1] != ' ' && i + 1 != _input.size())
            {
                std::cout<< "Error"<<std::endl;
                return false;
            }
            else
                i++;
        }
        else
        {
            std::cout<< "Error" <<std::endl;
            return false;
        }
    }
    return true;
}

void RPN::calculate(void)
{
    int value1;
    int value2;
    char sign[4];
    int (RPN::*ptr[4]) (int value1, int value2);
    
    sign[0] = '+';
    sign[1] = '-';
    sign[2] = '*';
    sign[3] = '/';
    ptr[0] = &RPN::Addition;
    ptr[1] = &RPN::Addition;
    ptr[2] = &RPN::Multiplication;
    ptr[3] = &RPN::Division;
    for (size_t i = 0; i < _input.size(); i++)
    {
        if (!RPN::isOperator(i))
        {
            // std::cout << "stack add: " << _input[i]<<std::endl;
            _stack.push(_input[i] - '0'); // mines '0' for give real value of int and not the value int of ascii
            i++;
        }
        else if(_stack.size() > 1)
        {
            try
            {
                value1 = _stack.top();
                _stack.pop();
                value2 = _stack.top();
                _stack.pop();
                // std::cout << "value1: "<< value1 <<std::endl;
                // std::cout << "value2: "<< value2 <<std::endl;
        // std::cout << "value1 * value2: "<< value1 * value2 <<std::endl;
                if (_input[i] == '-')
                    value1*=-1;
                for (size_t y = 0; y < 4; y++)
                {
                    if(_input[i] == sign[y])
                    {
                        _stack.push( (this->*ptr[y])(value1, value2));
                    }
                }
                i++;
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
                exit(EXIT_FAILURE);
            }
        }
    }
    std::cout << _stack.top() <<std::endl;
}
void RPN::global(char **av)
{
    _input = static_cast<std::string> (av[1]);
    if(!RPN::parsing())
        return;
    RPN::calculate();
}