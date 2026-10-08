#ifndef PMERGEME_HPP
# define PMERGEME_HPP
# include <iostream>
# include <cstdlib>
# include <vector>
# include <deque>
#include <utility>

class PmergeMe
{
    private:
        std::vector<int> _vec;
        std::vector<std::pair <int, int> > _work;
        std::deque<int> _deq;
        bool _is_odd;
        int _nb_struggler;
    public:
        //Form canonical
        PmergeMe(void);
        PmergeMe(const PmergeMe& other);
        PmergeMe &operator=(const PmergeMe &other);
        ~PmergeMe();
        void global(int ac, char **av);
        void parsing(int ac, char **av);
        std::vector<int> algoVec(std::vector<std::pair <int, int> >);
        template <typename T>
        T & SortPairIndividually(T & container);
        template <typename T>
        T & PmergeMe::RecursiveSortBigNb(T& container);
        template <typename T, typename U>
        T & PmergeMe::Insert(T& containerPair, U& containerMain, U& containerPend);
        int JacobsthalNumber (int nb);
        template <typename T, typename U>
        U & FillContainer(T& original, U& newcontainer, int size, bool original_is_paired);

};

#endif

