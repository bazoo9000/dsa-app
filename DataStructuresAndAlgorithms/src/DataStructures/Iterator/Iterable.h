#pragma once

#include <memory>
#include "Iterator.h"

namespace ds 
{
    template <typename T>
    class Iterable
    {
    public:
        virtual ~Iterable() = default;

    public:
        virtual std::unique_ptr<Iterator<T>> CreateIterator() = 0;
    };
}