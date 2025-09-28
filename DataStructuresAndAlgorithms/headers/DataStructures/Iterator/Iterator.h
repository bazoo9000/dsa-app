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
        virtual std::unique_ptr<Iterator> Clone() = 0;

    public:
        virtual T& operator*() = 0;
        virtual std::unique_ptr<Iterator> operator++() = 0;
        virtual std::unique_ptr<Iterator> operator++(int) = 0;
        virtual std::unique_ptr<Iterator> operator+(uint32_t idx) = 0;
        virtual std::unique_ptr<Iterator> operator=(std::unique_ptr<Iterator> it) = 0;
    };
}