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
        virtual std::shared_ptr<Iterator<T>> CreateIterator() = 0;
    };
}