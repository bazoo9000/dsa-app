#pragma once

#include "ISearchStrategy.h"
#include <cstdint>

namespace alg
{
    template <typename T>
    class LinearSearch : public ISearchStrategy<T>
    {
    public:
        virtual ~LinearSearch() = default;

    public:
        virtual uint32_t Search(T needle, ds::Iterable<T>* haystack) override;
    };

    template <typename T>
    uint32_t LinearSearch<T>::Search(T needle, ds::Iterable<T>* haystack)
    {
        LOG_DEBUG("Searching using LinearSearch");

        uint32_t index = 0;
        for (auto it = haystack->CreateIterator(); !it->IsAtEnd(); it->Next())
        {
            if (it->GetCurrent() == needle)
            {
                LOG_TRACE("Element found");
                return index;
            }
            index++;
        }

        LOG_TRACE("Element NOT found");
        return UINT32_MAX;
    }
}