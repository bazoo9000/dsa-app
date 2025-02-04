#pragma once

#include "../../DataStructures/DataStructure.h"

namespace alg
{
    template <typename T>
    class ISearchStrategy
    {
    public:
        virtual ~ISearchStrategy();

    public:
        virtual uint32_t Search(T needle, ds::DataStructure<T>* haystack) = 0;
    };
}