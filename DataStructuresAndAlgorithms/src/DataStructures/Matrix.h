#pragma once

#include "DataStructure.h"
#include "Array.h"
#include <algorithm>
#include <cstdint>

namespace ds 
{
    /*
    THIS IS STILL UNDER IMPLEMENTATION
    */
    template <typename T, uint32_t maxRows, uint32_t maxCols>
    class Matrix : public DataStructure<T>
    {
    public:
        Matrix();
        Matrix(const Matrix& mat);
        Matrix(Matrix&& mat);
        ~Matrix();

    public:
        virtual void Print() override;

    public:
        Matrix& operator=(const Matrix& mat);
        Matrix& operator=(Matrix&& mat);

    private:
        Array<T[maxRows], maxCols> m_Data;
    };

    template <typename T, uint32_t maxRows, uint32_t maxCols>
    Matrix<T, maxRows, maxCols>::Matrix()
    {
        LOG_INFO("Matrix CREATED succesfully");
    }

    template <typename T, uint32_t maxRows, uint32_t maxCols>
    Matrix<T, maxRows, maxCols>::Matrix(const Matrix& mat)
    {
        for(uint32_t i = 0; i < maxRows; i++)
        {
            for(uint32_t j = 0; j < maxCols; j++)
            {
                this->m_Data[i][j] = mat.m_Data[i][j];
            }
        }

        LOG_INFO("Matrix COPIED succesfully");
    }

    template <typename T, uint32_t maxRows, uint32_t maxCols>
    Matrix<T, maxRows, maxCols>::Matrix(Matrix&& mat)
    {
        this->m_Size = mat.m_Size;

		for (uint32_t i = 0; i < mat.m_Size; ++i)
		{
			this->m_Data[i] = std::move(mat.m_Data[i]);
		}

		mat.m_Size = 0;

		LOG_INFO("Matrix MOVED succesfully");
    }

    template <typename T, uint32_t maxRows, uint32_t maxCols>
    Matrix<T, maxRows, maxCols>::~Matrix()
    {
        LOG_INFO("Matrix DELETED succesfully");
    }

    template <typename T, uint32_t maxRows, uint32_t maxCols>
    void Matrix<T, maxRows, maxCols>::Print()
    {
        LOG_DEBUG("This is a Matrix");

        if(this->m_Size == 0)
        {
            LOG_DEBUG("Matrix is empty");
        }

        for(int i = 0; i < maxRows; i++)
        {
            for(int j = 0 ; j < maxCols; j++)
            {
                std::cout << this->m_Data[i][j] << " ";
            }
            std::cout << "\n";
        }
    }
}
