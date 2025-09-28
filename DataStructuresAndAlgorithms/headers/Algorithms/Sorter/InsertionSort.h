#pragma once

#include "ISortStrategy.h"
#include "../../DataStructures/DynamicArray.h"
#include <cstdint>

namespace alg
{
    template <typename T>
    class InsertionSort : public ISortStrategy<T>
    {
    public:
        virtual ~InsertionSort() = default;
    
    public:
        virtual void Sort(ds::Iterable<T>* data, std::function<bool(T, T)> orderFunc) override;
    };

    template <typename T>
    void InsertionSort<T>::Sort(ds::Iterable<T>* data, std::function<bool(T, T)> orderFunc)
    {
        LOG_DEBUG("Sorting using InsertionSort");

        uint32_t cnt = 1;
        for (auto it = (*data->CreateIterator()) + 1; !it->IsAtEnd(); it->Next())
        {
            T key = **it;
            uint32_t j = cnt - 1;
            auto compIt = data->CreateIterator();

            while (j != UINT32_MAX && orderFunc(key, (*compIt + j)->GetCurrent()))
            {
                // horrible, terrible, disgusting syntax, but iterators are implemented by me :(
                **(*compIt + (j + 1)) = ((*compIt + j)->GetCurrent());
                j--;
            }

            **(*compIt + (j + 1)) = key;

            cnt++;
        }
    }
}