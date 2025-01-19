#pragma once

#include "ISort.h"
#include "../DataStructures/DynamicArray.h"

namespace alg
{
    template <typename T>
    class SelectionSort : public ISort<T>
    {
    public:
        virtual void Sort(ds::DataStructure<T>* data) override;
    };

    template <typename T>
    void SelectionSort<T>::Sort(ds::DataStructure<T>* data)
    {
        LOG_DEBUG("Sorting using SelectionSort");

        ds::DynamicArray<T>* arr = dynamic_cast<ds::DynamicArray<T>*>(data);
        if(arr == nullptr)
        {
            LOG_ERROR("Can't sort, casting error");
            return;
        }

        for(uint32_t i = 0; i < arr->GetSize() - 1; i++)
        {
            uint32_t selected = i;
            for(uint32_t j = i + 1; j < arr->GetSize(); j++)
            {
                if((*arr)[selected] > (*arr)[j])
                {
                    selected = j;
                }
            }
            std::swap((*arr)[i], (*arr)[selected]);
        }
    }
}