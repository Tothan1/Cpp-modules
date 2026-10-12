#include "PmergeMe.hpp"

// Default constructor
PmergeMe::PmergeMe(void)
{
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
		for (int index = 0; index < av[i][index]; index++)
		{
			if(!std::isdigit(av[i][index]))
			{
				nb=-1;
				break;
			}
		}
        if( nb >= 0 && av[i][0]!='\0')
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

template <typename T, typename P>
void PmergeMe::rebuildPair( T&Winners, P&pair, P&sortpair)
{
	for (typename T::iterator it = Winners.begin(); it != Winners.end(); it++)
	{
		for (typename P::iterator pit = pair.begin(); pit != pair.end(); pit++)
		{
			if (*it == pit->first)
			{
				sortpair.push_back(*pit);
				break;
			}
		}
	}
	
}
template <typename U>
void PmergeMe::insertOnMain(U& Main, int &to_find)
{
    typename U::iterator it;
    it = std::lower_bound(Main.begin(), Main.end(), to_find);
    // if(it!= Main.begin())
        // --it;
    Main.insert(it, to_find);
}

template <typename T, typename P>
void PmergeMe::prepareContainer(P& containerPair, T& Main, T& Pend)
{
	Main.push_back(containerPair[0].second);
	Main.push_back(containerPair[0].first);
	for (size_t i = 1; i < containerPair.size(); i++)
		Pend.push_back(containerPair[i].second);
	for (size_t i = 1; i < containerPair.size(); i++)
		Main.push_back(containerPair[i].first);
}
template <typename T>
void PmergeMe::Insert(T& Main, T& Pend, bool _is_odd, int _nb_struggler)
{
    int len_Pend;
    int nb_jacob = 1;
    int old_nb_jacob = 0;
	int a = 0;
    T jacob;
    len_Pend = static_cast<int>(Pend.size());
    if (len_Pend > 1)
        jacob.push_back(3);
    jacob.push_back(2);
    while (nb_jacob - 2 < len_Pend)
    {
        for (int i = 0; i < nb_jacob - old_nb_jacob; i++)
            jacob.push_back(nb_jacob - i);
        old_nb_jacob = nb_jacob;
        nb_jacob = JacobsthalNumber(nb_jacob) + 2 *JacobsthalNumber(nb_jacob -1);
    }
	for (int i = 0; i < nb_jacob - old_nb_jacob; i++)
		jacob.push_back(nb_jacob - i);
    for (int i = 0; i < len_Pend; i++)
    {
        while (jacob[i+a]-2 >= len_Pend)
			a++;
        PmergeMe::insertOnMain(Main, Pend[jacob[i+a]-2]);
    }
    if(_is_odd)
        PmergeMe::insertOnMain(Main, _nb_struggler);
}
template <typename T, typename P>
void  PmergeMe::algo(T& work, P& useless)
{
	bool _is_odd;
    int _nb_struggler;
    P pair;
    P sortpair;
    std::vector <int> Winners;
	
    (void) useless;
    if(work.size() <= 1)
        return;
    if(work.size()%2 != 0)
    {
        _is_odd = true;
        _nb_struggler = work.back();
        work.pop_back();
    }
	else
		_is_odd =false;
    for (size_t i = 0; i < work.size() / 2; i++)
        pair.push_back(std::pair<int, int> (work[i * 2], work[(i * 2) + 1]));
    PmergeMe::SortPairIndividually(pair);
	for (size_t i = 0; i < pair.size(); i++)
    	Winners.push_back(pair[i].first);


	PmergeMe::algo(Winners, pair);
	PmergeMe::rebuildPair(Winners, pair, sortpair);
    T Pend;
    T Main;
	PmergeMe::prepareContainer(sortpair, Main, Pend);
    PmergeMe::Insert(Main, Pend,_is_odd, _nb_struggler);
    work = Main;
}

void PmergeMe::global(int ac, char **av)
{
    clock_t start;
    clock_t end;
    std::vector<std::pair <int, int> > p_vec;
    std::deque<std::pair <int, int> > p_deq;
    PmergeMe::parsing(ac, av);
    std::cout << "before: ";
	for (size_t i = 0; i < _vec.size(); i++)
        std::cout << _vec[i] << " ";
    start = clock();
	PmergeMe::algo(_vec, p_vec);
    end = clock();
    std::cout << std::endl <<"after: ";
	for (size_t i = 0; i < _vec.size(); i++)
        std::cout << _vec[i] << " ";
    std::cout << std::endl <<"Time to process a range of "<< ac - 1<<" elements with std::vector : "<< (((double)(end -start)))* 1000.0 / CLOCKS_PER_SEC << "ms" << std::endl;
    
    start = clock();
	PmergeMe::algo(_deq, p_deq);
    end = clock();
    std::cout <<"Time to process a range of "<< ac - 1<<" elements with std::deque : "<< (((double)(end -start)))* 1000.0 / CLOCKS_PER_SEC << "ms" << std::endl;

	// std::cout << std::endl << "_deq: ";
    // for (size_t i = 0; i < _deq.size(); i++)
    //     std::cout << _deq[i] << " ";
}