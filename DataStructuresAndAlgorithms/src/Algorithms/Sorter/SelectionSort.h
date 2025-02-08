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
        virtual void Sort(ds::DataStructure<T>* data, std::function<bool(T, T)> orderFunc) override;
    };

    template <typename T>
    void SelectionSort<T>::Sort(ds::DataStructure<T>* data, std::function<bool(T, T)> orderFunc)
    {
        LOG_DEBUG("Sorting using SelectionSort");

        ds::DynamicArray<T>* arr = dynamic_cast<ds::DynamicArray<T>*>(data);
        if(arr == nullptr)
        {
            LOG_ERROR("Can't sort, casting error (TEMPORARY)");
            return;
        }

        for(uint32_t i = 0; i < arr->GetSize() - 1; i++)
        {
            uint32_t selected = i;
            for(uint32_t j = i + 1; j < arr->GetSize(); j++)
            {
                if(!orderFunc((*arr)[selected], (*arr)[j]))
                {
                    selected = j;
                }
            }
            std::swap((*arr)[i], (*arr)[selected]);
        }
    }
}