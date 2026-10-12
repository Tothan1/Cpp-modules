#ifndef PMERGEME_HPP
# define PMERGEME_HPP
# include <iostream>
# include <cstdlib>
# include <vector>
# include <deque>
#include <utility>
#include <ctime>
class PmergeMe
{
    private:
        std::vector<int> _vec;
        std::deque<int> _deq;
    public:
        //Form canonical
        PmergeMe(void);
        PmergeMe(const PmergeMe& other);
        PmergeMe &operator=(const PmergeMe &other);
        ~PmergeMe();

        void global(int ac, char **av);
        void parsing(int ac, char **av);

        template <typename T, typename P>
        void algo(T& work, P& pair);

        template <typename T>
        T & SortPairIndividually(T & container);

        template <typename T>
        T & RecursiveSortBigNb(T& container);

        template <typename T>
        void Insert(T& containerMain, T& containerPend, bool _is_odd, int _nb_struggler);

        int JacobsthalNumber (int nb);

        // template <typename T, typename P>
        // U & FillContainer(T& original, P& newcontainer, int size, bool original_is_paired);

        template <typename U>
        void insertOnMain(U& Main, int &to_find);

        template <typename T, typename P>
        void prepareContainer(P& containerPair, T& Main, T& Pend);

        template <typename T, typename P>
        void rebuildPair( T&Winners, P&pair, P&sortpair);
};

#endif

