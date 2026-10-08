#include "PmergeMe.hpp"

// Default constructor
PmergeMe::PmergeMe(void)
{
    _is_odd = false;
    return ;
}

// Copy constructor
PmergeMe::PmergeMe(const PmergeMe &other)
{
    (void) other;
    return ;
}

// Assignment operator overload
PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    (void) other;
    return (*this);
}

// Destructor
PmergeMe::~PmergeMe(void)
{
    return ;
}

// template <typename T, typename U>
// U & PmergeMe::FillContainer(T& original, U& newcontainer, int size, bool original_is_paired)
// {
//     if( !original_is_paired)
//     {
//         for (size_t i = 0; i < size; i++)
//             newcontainer.push_back(std::pair<int, int> (original[i * 2], original[(i * 2) + 1]));
//     }
//     else
//     {
//         for (size_t i = 0; i < size; i=i+2)
//             newcontainer.push_back( original[i].first, original[i + 1].second);
//     }
//     return newcontainer;
// }
int PmergeMe::JacobsthalNumber (int nb)
{
    if (nb == 0)
        return 0;
    if (nb == 1)
        return 1;
    return(JacobsthalNumber(nb - 1) + 2 *JacobsthalNumber(nb - 2))
}
void PmergeMe::parsing(int ac, char **av)
{
    int nb;
    for (int i = 1; i < ac; i++)
    {
        nb = std::atof(av[i]);
        if( nb >= 0)
        {
            _vec.push_back(nb);
            _deq.push_back(nb);
        }
        else
        {
            std::cerr << "Error" <<std::endl;
            exit(EXIT_FAILURE);
        }
    }
}
template <typename T>
T & PmergeMe::SortPairIndividually(T& container)
{
    int tmp;
    for (size_t i = 0; i < container.size(); i++)
    {
        if(container[i].second > container[i].first)
        {
            tmp = container[i].first;
            container[i].first = container[i].second; 
            container[i].second = tmp; 
        }
    }
    return container;
}

template <typename T>
T & PmergeMe::RecursiveSortBigNb(T& original)
{
    T& modif;
    for (size_t i = 0; i < original.size() / 2; i++)
        modif.push_back(std::pair<int, int> (_vec[i * 2].first, _vec[(i * 2) + 1].first));
    return  PmergeMe::algoVec(modif);
}

template <typename T, typename U>
T & PmergeMe::Insert(T& containerPair, U& containerMain, U& containerPend)
{
    containerMain.push_back()= containerPair[0].second;
    for (size_t i = 0; i < containerMain.size() + 1; i++)
        containerMain.push_back(containerPair[i].first);
    for (size_t i = 1; i < containerMain.size() - 1; i++)
        containerPend.push_back(containerPair[i].second);
}
std::vector<int> PmergeMe::algoVec(std::vector<std::pair <int, int> > work)
{
    std::vector <int> Main;
    std::vector <int> Pend;
    if(_vec.size()%2 != 0)
    {
        _is_odd = true;
        _nb_struggler = _vec.back();
        _vec.pop_back();
    }
    for (size_t i = 0; i < _vec.size() / 2; i++)
        work.push_back(std::pair<int, int> (_vec[i * 2], _vec[(i * 2) + 1]));
    PmergeMe::SortPairIndividually(work);
    PmergeMe::RecursiveSortBigNb(work);
    PmergeMe::Insert(work, Main, Pend);
    for (size_t i = 0; i < work.size(); i++)
        std::cout << "first: "<<work[i].first << "second: "<<work[i].second << std::endl;
    
    return _vec;
}

void PmergeMe::global(int ac, char **av)
{
    PmergeMe::parsing(ac, av);
	PmergeMe::algoVec(_work);

}