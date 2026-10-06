#ifndef RPN_HPP
# define RPN_HPP
# include <iostream>
# include <stack>
# include <string>
# include <cctype>
# include <climits>
# include <cstdlib>
# include <exception>

class RPN
{
    private:
        std::stack<int> _stack;
        std::string _input;
    public:
        //Form canonical
        RPN(void);
        RPN(const RPN& other);
        RPN &operator=(const RPN &other);
        ~RPN();
        //Exception
        class Overflow : public std::exception 
        {
            public:
            char const * what() const throw();
        };
        class DivisionByZero : public std::exception 
        {
            public:
            char const * what() const throw();
        };
        //Operation
        bool CheckOverflow(double result);
        int Addition(int value1, int value2);
        int Multiplication(int value1, int value2);
        int Division(int value1, int value2);
        //Global
        bool isOperator(int i);
        bool parsing();
        void calculate(void);
        void global(char **av);
};

#endif

