#pragma once

#include <iostream>
#include <cstdint>
#include <utility>
#include "../Logger/Logger.h"

namespace ds 
{
    template <typename T>
    class DataStructure
    {
    public:
        DataStructure() = default;
        DataStructure(const DataStructure<T>& ds) = default;
        DataStructure(DataStructure<T>&& ds) = default;
        virtual ~DataStructure() = default;

    public:
        uint32_t GetSize() { return m_Size; }

    public:
        virtual void Print() = 0;

    protected:
        uint32_t m_Size = 0;
    };
}