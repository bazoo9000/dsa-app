#pragma once

#include <memory>
#include "ReverseIterator.h"

namespace ds 
{
    template <typename T>
    class ReverseIterable
    {
    public:
        virtual ~ReverseIterable() = default;

    public:
        virtual std::shared_ptr<ReverseIterator<T>> CreateReverseIterator() = 0;
    };
}