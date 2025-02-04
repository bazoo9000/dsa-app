#pragma once

#include "../../DataStructures/DataStructure.h"

namespace alg
{
    template <typename T>
    class ISortStrategy
    {
    public:
        virtual ~ISortStrategy();

    public:
        virtual void Sort(ds::DataStructure<T>* data) = 0;
    };
}