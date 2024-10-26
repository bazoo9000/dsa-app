#pragma once

#include "DataStructure.h"
#include "LinkedList.h"
#include "Matrix.h"

namespace ds 
{
    enum class GraphRepresentOption
    {
        NONE = 0,
        LIST, MATRIX
    };

    template <typename T>
    class Graph : public DataStructure<T>
    {
    public:
        Graph(GraphRepresentOption option = GraphRepresentOption::NONE);
        Graph(const Graph& graph) = default;
        Graph(Graph&& graph) = default;
        ~Graph();
    
    public:
        virtual void Print() override;

    public:
        GraphRepresentOption GetRepresentation() { return m_Option; }

    public:
        Graph& operator=(const Graph& graph) { return Graph(graph); }

    private:
        uint32_t m_EdgeCount;
        DataStructure<T>* m_Data; // this can either be a matrix or list
        GraphRepresentOption m_Option = GraphRepresentOption::NONE; // what representation option it has at the momement, to avoid using the wrong DS
    };
    
    template <typename T>
    Graph<T>::Graph(GraphRepresentOption option)
    {
        m_Option = option;
        switch (option) 
        {
            case GraphRepresentOption::LIST:
            {
                m_Data = new LinkedList<T>();
                m_Data = dynamic_cast<LinkedList<T>*>(m_Data);
                break;
            }
            case GraphRepresentOption::MATRIX:
            {
                //m_Data = new Matrix<T, rows, cols>(); // need a dynamic array
                //m_Data = dynamic_cast<Matrix<T>*>(m_Data); // need a dynamic array
                break;
            }
            case ds::GraphRepresentOption::NONE:
            {
                std::cout << "No representation option has been selected! It should be selected\n";
                exit(1);
            }
        }
    }
    
    template <typename T>
    Graph<T>::~Graph()
    {
        delete m_Data;
    }

    template <typename T>
    void Graph<T>::Print()
    {
        std::cout << "ceva\n";
    }
    
}