#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <cstdio>
#include <cstdint>
#include <utility>
#include <memory>
#include <algorithm>
#include <type_traits>

#include "Iterator/Iterator.h"
#include "Iterator/ReverseIterator.h"
#include "Iterator/Iterable.h"
#include "Iterator/ReverseIterable.h"
#include "../Logger/Logger.h"

#define MAX_OUTPUT_SIZE 10

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
        virtual void DebugDetails() { LOG_DEBUG("This is an unimplemented data structure, no information"); };

    public:
        DataStructure& operator=(const DataStructure& ds) = default;
        DataStructure& operator=(DataStructure&& ds) = default;

    protected:
        uint32_t m_Size = 0;
    };
}