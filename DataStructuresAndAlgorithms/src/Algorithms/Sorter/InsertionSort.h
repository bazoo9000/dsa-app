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
        virtual void Sort(ds::DataStructure<T>* data, std::function<bool(T, T)> orderFunc) override;
    };

    template <typename T>
    void InsertionSort<T>::Sort(ds::DataStructure<T>* data, std::function<bool(T, T)> orderFunc)
    {
        LOG_DEBUG("Sorting using InsertionSort");

        ds::DynamicArray<T>* arr = dynamic_cast<ds::DynamicArray<T>*>(data);
        if(arr == nullptr)
        {
            LOG_ERROR("Can't sort, casting error (TEMPORARY)");
            return;
        }

        for(uint32_t i = 1; i < arr->GetSize(); i++)
        {
            T key = (*arr)[i];
            uint32_t j = i;

            while (j > 0 && !orderFunc((*arr)[j - 1], key))
            {
                (*arr)[j] = (*arr)[j - 1];
                j--;
            }

            (*arr)[j] = key;
        }
    }
}