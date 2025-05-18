#pragma once

#include <memory>
namespace ds 
{
    template <typename T>
    class Iterator
    {
    public:
        virtual ~Iterator() = default;

    public:
        virtual void Reset() = 0;
        virtual const T& GetCurrent() = 0;
        virtual void Next() = 0;
        virtual bool IsAtEnd() = 0;
        virtual std::shared_ptr<Iterator> Clone() = 0;

    public:
        virtual T& operator*() = 0;
        virtual Iterator& operator++() = 0;
    };
}