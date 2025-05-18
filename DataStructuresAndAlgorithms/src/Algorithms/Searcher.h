#pragma once

#include "Algorithm.h"
#include "Searcher/ISearchStrategy.h"

namespace alg 
{
    template <typename T>
    class Searcher : public Algorithm
    {
    public:
        Searcher() = default;
        ~Searcher() { delete s_SearchStrategy; }

    public:
        static uint32_t Search(T needle, ds::Iterable<T>* haystack);

    public:
        static void SetSearchStrategy(ISearchStrategy<T>* strat);

    private:
        static ISearchStrategy<T>* s_SearchStrategy;
    };

    template <typename T>
    ISearchStrategy<T>* Searcher<T>::s_SearchStrategy = nullptr;

    template <typename T>
    uint32_t Searcher<T>::Search(T needle, ds::Iterable<T>* haystack)
    {
        if(s_SearchStrategy == nullptr)
        {
            LOG_ERROR("Can't search, no search selected");
            return UINT32_MAX;
        }

        return s_SearchStrategy->Search(needle, haystack);
    }

    template <typename T>
    void Searcher<T>::SetSearchStrategy(ISearchStrategy<T>* strat)
    {
        if(s_SearchStrategy != nullptr)
        {
            LOG_DEBUG("SearchStrategy changed, deleting old");
            delete s_SearchStrategy;
        }

        s_SearchStrategy = strat;
    }
}