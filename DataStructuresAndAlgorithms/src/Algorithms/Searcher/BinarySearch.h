#pragma once
//#define CHECK_SORTED
#include "ISearchStrategy.h"
#include "../../DataStructures/DynamicArray.h"

namespace alg
{
    template <typename T>
    class BinarySearch : public ISearchStrategy<T>
    {
    public:
        virtual uint32_t Search(T needle, ds::DataStructure<T>* haystack) override;
    };

    template <typename T>
    uint32_t BinarySearch<T>::Search(T needle, ds::DataStructure<T>* haystack)
    {
        LOG_DEBUG("Searching using BinarySearch");

        ds::DynamicArray<T>* arr = dynamic_cast<ds::DynamicArray<T>*>(haystack);
        if(arr == nullptr)
        {
            LOG_ERROR("Can't search, casting error (TEMPORARY)");
            return haystack->GetSize();
        }

    #ifdef CHECK_SORTED
        LOG_DEBUG("BinarySearch condition check: is list sorted?");
        for(uint32_t i = 1; i < arr->GetSize(); i++)
        {
            if((*arr)[i - 1] > (*arr)[i])
            {
                LOG_ERROR("Can't search, BinarySearch condition fail: list must be sorted");
                return arr->GetSize();
            }
        }
        LOG_INFO("BinarySearch condition succes: list is sorted");
    #endif // CHECK_SORTED

        uint32_t low = 0;
        uint32_t high = arr->GetSize() - 1;

        while (low <= high) 
        {
            uint32_t mid = low + (high - low) / 2;

            if ((*arr)[mid] == needle)
            {
                LOG_TRACE("Element found");
                return mid;
            }

            if ((*arr)[mid] < needle)
            {
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }
        }

        LOG_TRACE("Element NOT found");
        return arr->GetSize();
    }
}