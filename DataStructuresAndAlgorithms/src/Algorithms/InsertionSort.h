#pragma once

#include "ISort.h"
#include "../DataStructures/DynamicArray.h"

namespace alg
{
    template <typename T>
    class InsertionSort : public ISort<T>
    {
    public:
        virtual void Sort(ds::DataStructure<T>* data) override;
    };

    template <typename T>
    void InsertionSort<T>::Sort(ds::DataStructure<T>* data)
    {
        LOG_DEBUG("Sorting using InsertionSort");

        ds::DynamicArray<T>* arr = dynamic_cast<ds::DynamicArray<T>*>(data);
        if(arr == nullptr)
        {
            LOG_ERROR("Can't sort, casting error");
            return;
        }

        for(uint32_t i = 1; i < arr->GetSize(); i++)
        {
            T key = (*arr)[i];
            uint32_t j = i;

            while (j > 0 && (*arr)[j - 1] > key) 
            {
                (*arr)[j] = (*arr)[j - 1];
                j--;
            }

            (*arr)[j] = key;
        }
    }
}