#pragma once

#include "Algorithm.h"
#include "Sorter/ISortStrategy.h"

namespace alg
{
    template <typename T>
    class Sorter : public Algorithm
    {
    public:
        Sorter() = default;
        ~Sorter() { delete s_SortStrategy; }

    public:
        static void Sort(ds::DataStructure<T>* data);

    public:
        static void SetSortStrategy(ISortStrategy<T>* strat);

    private:
        static ISortStrategy<T>* s_SortStrategy;
    };

    template<typename T>
    ISortStrategy<T>* Sorter<T>::s_SortStrategy = nullptr;

    template <typename T>
    void Sorter<T>::Sort(ds::DataStructure<T>* data)
    {
        if(s_SortStrategy == nullptr)
        {
            LOG_ERROR("Can't sort, no sort selected");
            return;
        }

        s_SortStrategy->Sort(data);
    }

    template <typename T>
    void Sorter<T>::SetSortStrategy(ISortStrategy<T>* strat) 
    { 
        if(s_SortStrategy != nullptr)
        {
            LOG_DEBUG("SortStrategy changed, deleting old");
            delete s_SortStrategy;
        }

        s_SortStrategy = strat; 
    }
}