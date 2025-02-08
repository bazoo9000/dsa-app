#pragma once

#include <functional>
#include "../../DataStructures/DataStructure.h"

namespace alg
{
    template <typename T>
    class ISortStrategy
    {
    public:
        virtual ~ISortStrategy() = default;

    public:
        virtual void Sort(ds::DataStructure<T>* data, std::function<bool(T, T)> orderFunc) = 0;
    };
}