#pragma once

#include "ISortStrategy.h"
#include "../../DataStructures/DynamicArray.h"

namespace alg 
{
    template <typename T>
    class BubbleSort : public ISortStrategy<T>
    {
    public:
        virtual void Sort(ds::DataStructure<T>* data) override;
    };

    template <typename T>
    void BubbleSort<T>::Sort(ds::DataStructure<T>* data)
    {
        LOG_DEBUG("Sorting using BubbleSort");

        ds::DynamicArray<T>* arr = dynamic_cast<ds::DynamicArray<T>*>(data);
        if(arr == nullptr)
        {
            LOG_ERROR("Can't sort, casting error (TEMPORARY)");
            return;
        }

        for(uint32_t i = 0; i < arr->GetSize(); i++)
        {
            bool isSorted = true;
            for(uint32_t j = i + 1; j < arr->GetSize(); j++)
            {
                if((*arr)[i] > (*arr)[j])
                {
                    isSorted = false;
                    std::swap((*arr)[i], (*arr)[j]);
                }
            }

            if(isSorted)
            {
                break;
            }
        }
    }
}