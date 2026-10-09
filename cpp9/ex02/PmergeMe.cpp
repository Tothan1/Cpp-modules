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
    return(JacobsthalNumber(nb - 1) + 2 *JacobsthalNumber(nb - 2));
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
T & PmergeMe::RecursiveSortBigNb(T& pair)
{
    std::vector <int> modif;
    for (size_t i = 0; i < pair.size(); i= i+ 2)
    {
        modif.push_back(pair[i * 2].first);
        modif.push_back(pair[(i * 2) + 1].first);
    }
    PmergeMe::algoVec(modif);
    return pair ;
}
template <typename U>
void PmergeMe::insertOnMain(U& Main, int to_find)
{
    typename U::iterator it;
    it = std::lower_bound(Main.begin(), Main.end(), to_find);
    if(it!= Main.begin())
        --it;
    Main.insert(it, to_find);
}
template <typename T, typename U>
void PmergeMe::Insert(T& containerPair, U& Main, U& Pend)
{
    int n = 3;
    int nb_jacob = 3;
    int old_nb_jacob = 1;
    U jacob;
    Main.push_back(containerPair[0].second);
    for (size_t i = 0; i < Main.size() + 1; i++)
        Main.push_back(containerPair[i].first);
    for (size_t i = 1; i < Main.size() - 1; i++)
        Pend.push_back(containerPair[i].second);
    while (nb_jacob< static_cast<int>(Pend.size()))
    {
        for (int i = 0; i < nb_jacob - old_nb_jacob; i++)
            jacob.push_back(nb_jacob - i);
        old_nb_jacob = nb_jacob;
        nb_jacob = PmergeMe::JacobsthalNumber(n++);
    }
    for (size_t i = 0; i < Pend.size(); i++)
    {
        PmergeMe::insertOnMain(Main, Pend[jacob[i]- 2]);
        Pend.erase( Pend.begin() + (jacob[i] - 2));
    }
    if(this->_is_odd)
        PmergeMe::insertOnMain(Main, _nb_struggler);
}

template <typename T>
T & PmergeMe::algoVec(T& work)
{
    std::vector<std::pair <int, int> > pair;
    std::vector <int> Pend;
    if(work.size() <= 1)
        return work;
    if(work.size()%2 != 0)
    {
        _is_odd = true;
        _nb_struggler = work.back();
        work.pop_back();
    }
    for (size_t i = 0; i < work.size() / 2; i++)
        pair.push_back(std::pair<int, int> (work[i * 2], work[(i * 2) + 1]));
    PmergeMe::SortPairIndividually(pair);
    PmergeMe::RecursiveSortBigNb(pair);
    PmergeMe::Insert(pair, _Main, Pend);
    // for (size_t i = 0; i < work.size(); i++)
        // std::cout << "first: "<<work[i].first << "second: "<<work[i].second << std::endl;
    return _Main;
}

void PmergeMe::global(int ac, char **av)
{
    std::vector<int> Main;
    PmergeMe::parsing(ac, av);
	Main = PmergeMe::algoVec(_vec);
    for (size_t i = 0; i < Main.size(); i++)
        std::cout << Main[i] << std::endl;
}