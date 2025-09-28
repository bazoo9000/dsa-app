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
        virtual std::unique_ptr<ReverseIterator> Clone() = 0;

    public:
        virtual T& operator*() = 0;
        virtual std::unique_ptr<ReverseIterator> operator++() = 0;
        virtual std::unique_ptr<ReverseIterator> operator++(int) = 0;
        virtual std::unique_ptr<ReverseIterator> operator+(uint32_t idx) = 0;
        virtual std::unique_ptr<ReverseIterator> operator=(std::unique_ptr<ReverseIterator> it) = 0;
    };
}