#pragma once

#include "ISortStrategy.h"
#include "../../DataStructures/DynamicArray.h"

namespace alg
{
    template <typename T>
    class SelectionSort : public ISortStrategy<T>
    {
    public:
        virtual ~SelectionSort() = default;

    public:
        virtual void Sort(ds::Iterable<T>* data, std::function<bool(T, T)> orderFunc) override;
    };

    template <typename T>
    void SelectionSort<T>::Sort(ds::Iterable<T>* data, std::function<bool(T, T)> orderFunc)
    {
        LOG_DEBUG("Sorting using SelectionSort");
        
        for (auto it1 = data->CreateIterator(); !it1->IsAtEnd(); it1->Next())
        {
            auto it2 = it1->Clone();
            it2->Next();

            auto selected = it1->Clone();
            for ( ; !it2->IsAtEnd(); it2->Next())
            {
                if (!orderFunc(**selected, **it2))
                {
                    selected = it2->Clone();
                }
            }

            std::swap(**it1, **selected);
        }
    }
}