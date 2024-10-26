#pragma once

#include <iostream>
#include "DataStructure.h"
#include "DynamicArray.h"

namespace ds 
{
    template <typename T>
    class DynamicMatrix : public DataStructure<T>
    {
    public:
        DynamicMatrix();
        DynamicMatrix(DynamicMatrix &&) = default;
        DynamicMatrix(const DynamicMatrix &) = default;
        DynamicMatrix &operator=(DynamicMatrix &&) = default;
        DynamicMatrix &operator=(const DynamicMatrix &) = default;
        ~DynamicMatrix();
    
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