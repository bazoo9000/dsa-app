#pragma once

#include "Iterator.h"

namespace ds 
{
    template <typename T>
    class Iterable
    {
    public:
        virtual ~Iterable() = default;

    public:
        virtual Iterator<T>* CreateIterator() = 0;
    };
}