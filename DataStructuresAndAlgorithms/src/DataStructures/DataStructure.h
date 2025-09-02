#pragma once

// TODO: Precompile those headers
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdint>
#include <utility>
#include <memory>

#include "Iterator/Iterator.h"
#include "Iterator/ReverseIterator.h"
#include "Iterator/Iterable.h"
#include "Iterator/ReverseIterable.h"
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
        virtual void DebugDetails() { LOG_DEBUG("This is a data structure, unimplemented, no more information"); };

    public:
        DataStructure& operator=(const DataStructure& ds) = default;
        DataStructure& operator=(DataStructure&& ds) = default;

    protected:
        uint32_t m_Size = 0;
    };
}