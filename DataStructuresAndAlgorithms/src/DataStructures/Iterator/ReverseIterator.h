#pragma once

#include <memory>
namespace ds 
{
    template <typename T>
    class ReverseIterator
    {
    public:
        virtual ~ReverseIterator() = default;

    public:
        virtual void Reset() = 0;
        virtual const T& GetCurrent() = 0;
        virtual void Prev() = 0;
        virtual bool IsAtBegin() = 0;
        virtual std::shared_ptr<ReverseIterator> Clone() = 0;

    public:
        virtual T& operator*() = 0;
        virtual ReverseIterator& operator++() = 0;
    };
}