#pragma once

// TODO: Precompile those headers
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdint>
#include <utility>

#include "Iterator/Iterator.h"
#include "Iterator/Iterable.h"
#include "../Logger/Logger.h"

namespace ds 
{
    template <typename T>
    class DataStructure
    {
    public:
        DataStructure() = default;
        DataStructure(const DataStructure& ds) = default;
        DataStructure(DataStructure&& ds) = default;
        virtual ~DataStructure() = default;

    public:
        uint32_t GetSize() { return m_Size; }

    public:
        virtual void Print() { LOG_DEBUG("This is a data structure"); };

    public:
        DataStructure& operator=(const DataStructure& ds) = default;
        DataStructure& operator=(DataStructure&& ds) = default;

    protected:
        uint32_t m_Size = 0;
    };
}