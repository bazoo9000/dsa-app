#pragma once

#include "DataStructure.h"
#include "DynamicArray.h"

namespace ds 
{
    template <typename T>
    class DynamicMatrix : public DataStructure<T>
    {
    public:
        DynamicMatrix();
        DynamicMatrix(const T** mat);
        DynamicMatrix(const DynamicMatrix& mat);
        DynamicMatrix(DynamicMatrix&& mat);
        ~DynamicMatrix();
    
    public:
        DynamicMatrix& operator=(const T** mat);
        DynamicMatrix& operator=(const DynamicMatrix &);
        DynamicMatrix& operator=(DynamicMatrix &&);

    private:
        
    };
    
    template <typename T>
    DynamicMatrix<T>::DynamicMatrix()
    {
    }
    
    template <typename T>
    DynamicMatrix<T>::~DynamicMatrix()
    {
    }
}