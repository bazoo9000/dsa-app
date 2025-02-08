#pragma once

#include "ISearchStrategy.h"
#include "../../DataStructures/DynamicArray.h"

namespace alg
{
    template <typename T>
    class LinearSearch : public ISearchStrategy<T>
    {
    public:
        virtual ~LinearSearch() = default;

    public:
        virtual uint32_t Search(T needle, ds::DataStructure<T>* haystack) override;
    };

    template <typename T>
    uint32_t LinearSearch<T>::Search(T needle, ds::DataStructure<T>* haystack)
    {
        LOG_DEBUG("Searching using LinearSearch");

        ds::DynamicArray<T>* arr = dynamic_cast<ds::DynamicArray<T>*>(haystack);
        if(arr == nullptr)
        {
            LOG_ERROR("Can't search, casting error (TEMPORARY)");
            return haystack->GetSize();
        }

        for(uint32_t i = 0; i < arr->GetSize(); i++)
        {
            if((*arr)[i] == needle)
            {
                LOG_TRACE("Element found");
                return i;
            }
        }

        LOG_TRACE("Element NOT found");
        return arr->GetSize();
    }
}