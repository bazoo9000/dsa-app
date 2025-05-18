#pragma once

#include "ISortStrategy.h"
#include "../../DataStructures/DynamicArray.h"

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

        // i think a reverse iterator would be better for this sort

        // for(uint32_t i = 1; i < arr->GetSize(); i++)
        // {
        //     T key = (*arr)[i];
        //     uint32_t j = i;

        //     while (j > 0 && !orderFunc((*arr)[j - 1], key))
        //     {
        //         (*arr)[j] = (*arr)[j - 1];
        //         j--;
        //     }

        //     (*arr)[j] = key;
        // }

        // THIS WONT WORK!!
        auto prev = data->CreateIterator();
        auto it1 = prev->Clone();
        it1->Next();
        for ( ; !it1->IsAtEnd(); it1->Next())
        {
            T key = **it1;
            auto it2 = prev->Clone();

            while (!it2->IsAtEnd() && !orderFunc(**it2, key))
            {
                it2->Next();
            }
        }
    }
}