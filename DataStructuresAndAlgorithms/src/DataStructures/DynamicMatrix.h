#pragma once

#include "DataStructure.h"

namespace ds 
{
    template <typename T>
    class DynamicMatrix : public DataStructure<T>
    {
    public:
        DynamicMatrix(T initial, uint32_t rows = 1, uint32_t cols = 1);
        DynamicMatrix(const T** mat);
        DynamicMatrix(const DynamicMatrix& mat);
        DynamicMatrix(DynamicMatrix&& mat);
        ~DynamicMatrix();
    
    public:
        DynamicMatrix& operator=(const T** mat);
        DynamicMatrix& operator=(const DynamicMatrix &);
        DynamicMatrix& operator=(DynamicMatrix &&);

    private:
        T** m_Data;
        T m_Initial;
        uint32_t m_Rows;
        uint32_t m_Cols;
    };
    
    template <typename T>
    DynamicMatrix<T>::DynamicMatrix(T initial, uint32_t rows, uint32_t cols)
        : m_Rows(rows), m_Cols(cols)
    {
        if(this->m_Rows == 0)
		{
			LOG_ERROR("Row count of DynamicArray is 0! Setting it back to 1");
			this->m_Rows = 1;
		}

        if(this->m_Cols == 0)
		{
			LOG_ERROR("Column count of DynamicArray is 0! Setting it back to 1");
			this->m_Cols = 1;
		}

        this->m_Data = new T*[rows];
        for(int i = 0; i < rows; i++)
        {
            this->m_Data[i] = new T[cols];
            for(int j = 0; j < cols; j++)
            {
                this->m_Data[i][j] = initial;
            }
        }

        this->m_Initial = initial;

        LOG_INFO("DynamicMatrix CREATED succesfully");
    }
    
    template <typename T>
    DynamicMatrix<T>::~DynamicMatrix()
    {
    }
}