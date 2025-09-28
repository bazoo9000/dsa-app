#pragma once

#include "ISearchStrategy.h"
#include <cstdint>

namespace alg
{
    template <typename T>
    class BinarySearch : public ISearchStrategy<T>
    {
    public:
        virtual ~BinarySearch() = default;

    public:
        virtual uint32_t Search(T needle, ds::Iterable<T>* haystack) override;
    };

    template <typename T>
    uint32_t BinarySearch<T>::Search(T needle, ds::Iterable<T>* haystack)
    {
        LOG_DEBUG("Searching using BinarySearch");

        uint32_t size = dynamic_cast<ds::DataStructure<T>*>(haystack)->GetSize();

        auto it = haystack->CreateIterator();
        uint32_t first = 0;
        uint32_t last = size - 1;

        while(first <= last)
        {
            uint32_t mid = first + (last - first) / 2;
        
            if ((*it + mid)->GetCurrent() == needle)
            {
                LOG_TRACE("Element found");
                return mid;
            }

            if ((*it + mid)->GetCurrent() < needle)
            {
                first = mid + 1;
            }
            else
            {
                last = mid - 1;
            }
        }

        LOG_TRACE("Element NOT found");
        return NOT_FOUND;
    }
}