#pragma once

#include <iostream>
#include "DataStructure.h"
#include "Array.h"

namespace ds 
{
    template <typename T, uint32_t maxRows, uint32_t maxCols>
    class Matrix : public DataStructure<T>
    {
    public:
        Matrix();
        Matrix(const T** mat);
        Matrix(const Matrix& mat);
        Matrix(Matrix&& mat);
        ~Matrix();

    public:
        virtual void Print() override;

    private:
        Array<Array<T, maxRows>, maxCols> m_Data;
    };

    template <typename T, uint32_t maxRows, uint32_t maxCols>
    Matrix<T, maxRows, maxCols>::Matrix()
    {
    }

    template <typename T, uint32_t maxRows, uint32_t maxCols>
    Matrix<T, maxRows, maxCols>::Matrix(const T** mat)
    {
    }

    template <typename T, uint32_t maxRows, uint32_t maxCols>
    Matrix<T, maxRows, maxCols>::Matrix(const Matrix& mat)
    {
    }

    template <typename T, uint32_t maxRows, uint32_t maxCols>
    Matrix<T, maxRows, maxCols>::Matrix(Matrix&& mat)
    {
    }

    template <typename T, uint32_t maxRows, uint32_t maxCols>
    Matrix<T, maxRows, maxCols>::~Matrix()
    {
    }
}
