#pragma once

#include "../../DataStructures/Iterator/Iterable.h"
#include <memory>
#include <cstdint>

#define NOT_FOUND UINT32_MAX

namespace alg
{
    template <typename T>
    class ISearchStrategy
    {
    public:
        virtual ~ISearchStrategy() = default;

    public:
        virtual uint32_t Search(T needle, ds::Iterable<T>* haystack) = 0;
    };
}