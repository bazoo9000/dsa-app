#pragma once

#include "DataStructure.h"
#include <cstdint>

namespace ds 
{
    template <typename T>
    class DynamicMatrix : public DataStructure<T>
    {
    public:
        DynamicMatrix(T initial, uint32_t rows = 1, uint32_t cols = 1);
        DynamicMatrix(const DynamicMatrix& mat);
        DynamicMatrix(DynamicMatrix&& mat);
        ~DynamicMatrix();
    
    public:
        void Clear();
        void Insert(T elem, uint32_t r, uint32_t c);
        T GetElementAt(uint32_t r, uint32_t c);
        void Reinitialize();
        void AddRows(uint32_t rows = 1);
        void AddColumns(uint32_t cols = 1);
        void AddCorner(uint32_t amount = 1);
        virtual void Print() override;

    public:
        T** GetData() { return this->m_Data; }
        uint32_t GetRows() { return this->m_Rows; }
        uint32_t GetColumns() { return this->m_Cols; }
        T GetInitial() { return this->m_Initial; }
        void SetInitial(T init) { this->m_Initial = init; }

    public:
        T* operator[](uint32_t r) { return this->m_Data[r]; }
        DynamicMatrix& operator=(const DynamicMatrix& mat);
        DynamicMatrix& operator=(DynamicMatrix&& mat);

    private:
        void resize(uint32_t newRows, uint32_t newCols);

    private:
        T** m_Data;
        T m_Initial;
        uint32_t m_Rows;
        uint32_t m_Cols;
    };
    
    template <typename T>
    DynamicMatrix<T>::DynamicMatrix(T initial, uint32_t rows, uint32_t cols)
        : m_Rows(rows), m_Cols(cols), m_Initial(initial)
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

        LOG_INFO("DynamicMatrix CREATED succesfully");
    }
    
    template <typename T>
    DynamicMatrix<T>::DynamicMatrix(const DynamicMatrix& mat)
        : m_Rows(mat.m_Rows), m_Cols(mat.m_Cols), m_Initial(mat.m_Initial)
    {
        this->m_Data = new T*[this->m_Rows];
        for(int i = 0; i < this->m_Rows; i++)
        {
            this->m_Data[i] = new T[this->m_Cols];
            for(int j = 0; j < this->m_Cols; j++)
            {
                this->m_Data[i][j] = mat.m_Data[i][j];
            }
        }

        LOG_INFO("DynamicMatrix COPIED succesfully");
    }

    template <typename T>
    DynamicMatrix<T>::DynamicMatrix(DynamicMatrix&& mat)
        : m_Rows(mat.m_Rows), m_Cols(mat.m_Cols), m_Initial(mat.m_Initial)
    {
        this->m_Data = mat.m_Data;

        mat.m_Data = nullptr;
        mat.m_Rows = 0;
        mat.m_Cols = 0;

        LOG_INFO("DynamicMatrix MOVED succesfully");
    }

    template <typename T>
    DynamicMatrix<T>::~DynamicMatrix()
    {
        Clear();
        LOG_INFO("DynamicMatrix DELETED succesfully");
    }

    template <typename T>
    void DynamicMatrix<T>::Clear()
    {
        if(m_Data == nullptr)
        {
            LOG_DEBUG("m_Data is nullptr");
            return;
        }

        for(int i = 0; i < this->m_Rows; i++)
        {
            delete[] this->m_Data[i];
        }

        delete[] this->m_Data;
        this->m_Data = nullptr;
        this->m_Rows = 0;
        this->m_Cols = 0;

        LOG_DEBUG("DynamicMatrix has been cleared");
    }

    template <typename T>
    void DynamicMatrix<T>::Insert(T elem, uint32_t r, uint32_t c)
    {
        if(this->m_Rows <= r)
        {
            LOG_ERROR("Can't insert. Row index is out of bounds.");
            return;
        }

        if(this->m_Cols <= c)
        {
            LOG_ERROR("Can't insert. Column index is out of bounds.");
            return;
        }

        this->m_Data[r][c] = elem;
    }

    template <typename T>
    T DynamicMatrix<T>::GetElementAt(uint32_t r, uint32_t c)
    {
        if(this->m_Rows <= r)
        {
            LOG_FATAL("Can't get element. Row index is out of bounds.");
            exit(1);
        }

        if(this->m_Cols <= c)
        {
            LOG_FATAL("Can't get element. Column index is out of bounds.");
            exit(1);
        }

        return m_Data[r][c];
    }

    template <typename T>
    void DynamicMatrix<T>::Reinitialize()
    {
        for (uint32_t i = 0; i < this->m_Rows; ++i)
		{
			for (uint32_t j = 0; j < this->m_Cols; ++j)
            {
                this->m_Data[i][j] = this->m_Initial;
            }
		}
    }

    template <typename T>
    void DynamicMatrix<T>::AddRows(uint32_t rows)
    {
        resize(this->m_Rows + rows, this->m_Cols);
    }

    template <typename T>
    void DynamicMatrix<T>::AddColumns(uint32_t cols)
    {
        resize(this->m_Rows, this->m_Cols + cols);
    }

    template <typename T>
    void DynamicMatrix<T>::AddCorner(uint32_t amount)
    {
        resize(this->m_Rows + amount, this->m_Cols + amount);
    }

    template <typename T>
    void DynamicMatrix<T>::Print()
    {
        LOG_DEBUG("This is a DynamicMatrix");

        if(m_Data == nullptr)
        {
            LOG_DEBUG("Can't print, m_Data is nullptr");
            return;
        }

        for(int i = 0; i < this->m_Rows; i++)
        {
            for(int j = 0; j < this->m_Cols; j++)
            {
                std::cout << this->m_Data[i][j] << " ";
            }
            std::cout << "\n";
        }
    }

    template <typename T>
	DynamicMatrix<T>& DynamicMatrix<T>::operator=(const DynamicMatrix& mat) 
	{
		Clear();

        this->m_Rows = mat.m_Rows;
        this->m_Cols = mat.m_Cols;
        this->m_Initial = mat.m_Initial;

		this->m_Data = new T*[this->m_Rows];
        for(int i = 0; i < this->m_Rows; i++)
        {
            this->m_Data[i] = new T[this->m_Cols];
            for(int j = 0; j < this->m_Cols; j++)
            {
                this->m_Data[i][j] = mat.m_Data[i][j];
            }
        }

        LOG_INFO("DynamicMatrix COPIED succesfully");
		return *this;
	}
	
	template <typename T>
	DynamicMatrix<T>& DynamicMatrix<T>::operator=(DynamicMatrix&& mat) 
	{
		this->m_Data = mat.m_Data;
        this->m_Rows = mat.m_Rows;
        this->m_Cols = mat.m_Cols;
        this->m_Initial = mat.m_Initial;

		mat.m_Data = nullptr;
        mat.m_Rows = 0;
        mat.m_Cols = 0;

		LOG_INFO("DynamicMatrix MOVED succesfully");
		return *this;
	}

    template <typename T>
    void DynamicMatrix<T>::resize(uint32_t newRows, uint32_t newCols)
    {
        T** newData = new T*[newRows];
        for(int i = 0; i < newRows; i++)
        {
            newData[i] = new T[newCols];
            for(int j = 0; j < newCols; j++)
            {
                newData[i][j] = this->m_Initial;
            }
        }

        for(int i = 0; i < this->m_Rows; i++)
        {
            for(int j = 0; j < this->m_Cols; j++)
            {
                newData[i][j] = this->m_Data[i][j];
            }
        }

        Clear();
        this->m_Data = newData;
        this->m_Rows = newRows;
        this->m_Cols = newCols;

        LOG_DEBUG("DynamicMatrix has been resized");
    }
}