#pragma once

#include "ISortStrategy.h"

namespace alg 
{
    template <typename T>
    class BubbleSort : public ISortStrategy<T>
    {
    public:
        ~BubbleSort() = default;
    
    public:
        virtual void Sort(ds::Iterable<T>* data, std::function<bool(T, T)> orderFunc) override;
    };

    template <typename T>
    void BubbleSort<T>::Sort(ds::Iterable<T>* data, std::function<bool(T, T)> orderFunc)
    {
        LOG_DEBUG("Sorting using BubbleSort");

        for (auto it1 = data->CreateIterator(); !it1->IsAtEnd(); it1->Next())
        {
            bool isSorted = true;
            auto it2 = it1->Clone();
            it2->Next();
            for ( ; !it2->IsAtEnd(); it2->Next())
            {
                if (!orderFunc(**it1, **it2))
                {
                    isSorted = false;
                    std::swap(**it1, **it2);
                }
            }

            if (isSorted)
            {
                break;
            }
        }
    }
}