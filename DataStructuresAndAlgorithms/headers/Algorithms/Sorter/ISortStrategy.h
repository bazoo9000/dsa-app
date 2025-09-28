#pragma once

#include <functional>
#include "../../DataStructures/Iterator/Iterable.h"

namespace alg
{
    template <typename T>
    class ISortStrategy
    {
    public:
        virtual ~ISortStrategy() = default;

    public:
        virtual void Sort(ds::Iterable<T>* data, std::function<bool(T, T)> orderFunc) = 0;
    };
}