#pragma once

#include "ISearchStrategy.h"
#include "../../DataStructures/BinarySearchTree.h"

namespace alg
{
    template <typename T>
    class BinarySearch : public ISearchStrategy<T>
    {
    public:
        virtual ~BinarySearch() = default;

    public:
        virtual uint32_t Search(T needle, ds::Iterable<T>* haystack) override;
    };

    template <typename T>
    uint32_t BinarySearch<T>::Search(T needle, ds::Iterable<T>* haystack)
    {
        LOG_DEBUG("Searching using BinarySearch");

        // this is O(n) operation since we create a bst from the iterable
        ds::BinarySearchTree<T> tree;
        for (auto it = haystack->CreateIterator(); !it->IsAtEnd(); it->Next())
        {
            tree.Insert(it->GetCurrent());
        }

        uint32_t index = 0;
        for (auto it = tree.CreateIterator(); !it->IsAtEnd(); it->Next())
        {
            if (it->GetCurrent() == needle)
            {
                LOG_TRACE("Element found");
                return index;
            }
            index++;
        }

        LOG_TRACE("Element NOT found");
        return UINT32_MAX;
    }
}