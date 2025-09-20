#pragma once

#include "DataStructure.h"

namespace ds 
{
    template <typename T, uint32_t maxRows, uint32_t maxCols>
    class Matrix : public DataStructure<T>
    {
    public:
        Matrix(T initial);
        Matrix(const Matrix& mat);
        Matrix(Matrix&& mat);
        ~Matrix();

    public:
        void Insert(T elem, uint32_t r, uint32_t c);
        T GetElementAt(uint32_t r, uint32_t c);
        void Reinitialize();
        virtual void DebugDetails() override;

    public:
        T GetInitial() { return this->m_Initial; }
        void SetInitial(T init) { this->m_Initial = init; }
        // T (&GetData())[maxRows][maxCols] { return this->m_Data; } // should this be kept?

    public:
        T* operator[](uint32_t r) { return this->m_Data[r]; }
        Matrix& operator=(const Matrix& mat);
        Matrix& operator=(Matrix&& mat);

    private:
        T m_Data[maxRows][maxCols];
        T m_Initial;
    };

    template <typename T, uint32_t maxRows, uint32_t maxCols>
    Matrix<T, maxRows, maxCols>::Matrix(T initial)
    {
        for(int i = 0; i < maxRows; i++)
        {
            for(int j = 0; j < maxCols; j++)
            {
                this->m_Data[i][j] = initial;
            }
        }

        this->m_Initial = initial;

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

        this->m_Initial = mat.m_Initial;

        LOG_INFO("Matrix COPIED succesfully");
    }

    template <typename T, uint32_t maxRows, uint32_t maxCols>
    Matrix<T, maxRows, maxCols>::Matrix(Matrix&& mat)
    {
		for (uint32_t i = 0; i < maxRows; ++i)
		{
			for (uint32_t j = 0; j < maxCols; ++j)
            {
                this->m_Data[i][j] = std::move(mat.m_Data[i][j]);
            }
		}

        this->m_Initial = std::move(mat.m_Initial);

        mat.Reinitialize();

        // std::swap(this->m_Data, mat.m_Data);
        // std::swap(this->m_Initial, mat.m_Initial);

		LOG_INFO("Matrix MOVED succesfully");
    }

    template <typename T, uint32_t maxRows, uint32_t maxCols>
    Matrix<T, maxRows, maxCols>::~Matrix()
    {
        LOG_INFO("Matrix DELETED succesfully");
    }

    template <typename T, uint32_t maxRows, uint32_t maxCols>
    void Matrix<T, maxRows, maxCols>::Insert(T elem, uint32_t r, uint32_t c)
    {
        if(maxRows <= r)
        {
            LOG_ERROR("Can't insert, row index %u is out of bounds", r);
            return;
        }

        if(maxCols <= c)
        {
            LOG_ERROR("Can't insert, column index %u is out of bounds", c);
            return;
        }

        this->m_Data[r][c] = elem;
        LOG_DEBUG("Inserting at indeces %u, %u was succesful, new size is %u", r, c, this->m_Size);
    }

    template <typename T, uint32_t maxRows, uint32_t maxCols>
    T Matrix<T, maxRows, maxCols>::GetElementAt(uint32_t r, uint32_t c)
    {
        if(maxRows <= r)
        {
            LOG_FATAL("Can't get element, row index %u is out of bounds", r);
            exit(1);
        }

        if(maxCols <= c)
        {
            LOG_FATAL("Can't get element, column index %u is out of bounds", r);
            exit(1);
        }

		LOG_DEBUG("Got element at indeces %u, %u succesfully", r, c);
        return this->m_Data[r][c];
    }

    template <typename T, uint32_t maxRows, uint32_t maxCols>
    void Matrix<T, maxRows, maxCols>::Reinitialize()
    {
        for (uint32_t i = 0; i < maxRows; ++i)
		{
			for (uint32_t j = 0; j < maxCols; ++j)
            {
                this->m_Data[i][j] = this->m_Initial;
            }
		}

        LOG_DEBUG("Matrix has been reinitialized");
    }

    template <typename T, uint32_t maxRows, uint32_t maxCols>
    void Matrix<T, maxRows, maxCols>::DebugDetails()
    {
        std::ostringstream oss;

        oss << "\n";
        for (uint32_t i = 0; i < std::min<uint32_t>(maxRows, MAX_OUTPUT_SIZE); i++)
        {
            oss << "[ ";
            for (uint32_t j = 0; j < std::min<uint32_t>(maxCols, MAX_OUTPUT_SIZE); j++)
            {
                if constexpr (IS_STREAMABLE(T)) { oss << this->m_Data[i][j] << " "; }
                else                            { oss << typeid(this->m_Data[0][0]).name() << " "; }
            }
            oss << "]\n";
        }

        LOG_DEBUG("This is a Matrix\nMax Rows: %u\nMax Cols: %u\nBytes: %u\nData: %s",
            maxRows,
            maxCols,
            maxRows * maxCols * sizeof(T),
            oss.str().c_str()
        );
    }

    template <typename T, uint32_t maxRows, uint32_t maxCols>
	Matrix<T, maxRows, maxCols>& Matrix<T, maxRows, maxCols>::operator=(const Matrix& mat)
	{
		for (uint32_t i = 0; i < maxRows; ++i)
		{
			for (uint32_t j = 0; j < maxCols; ++j)
            {
                this->m_Data[i][j] = mat.m_Data[i][j];
            }
		}

		LOG_INFO("Matrix COPIED succesfully");
		return *this;
	}

	template <typename T, uint32_t maxRows, uint32_t maxCols>
	Matrix<T, maxRows, maxCols>& Matrix<T, maxRows, maxCols>::operator=(Matrix&& mat)
	{
		for (uint32_t i = 0; i < maxRows; ++i)
		{
			for (uint32_t j = 0; j < maxCols; ++j)
            {
                this->m_Data[i][j] = std::move(mat.m_Data[i][j]);
            }
		}
        
        this->m_Initial = std::move(mat.m_Initial);

        mat.Reinitialize();

		LOG_INFO("Matrix MOVED succesfully");
		return *this;
	}
}
