#pragma once

#include "ISearchStrategy.h"
#include "../../DataStructures/BinarySearchTree.h"
#include <memory>

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
        
        std::unique_ptr<ds::BinarySearchTree<T>> tree = std::unique_ptr<ds::BinarySearchTree<T>>(dynamic_cast<ds::BinarySearchTree<T>*>(haystack));
        if (tree == nullptr)
        {
            LOG_WARN("haystack is not a BinarySearchTree");
            tree = std::make_unique<ds::BinarySearchTree<T>>();
            for (auto it = haystack->CreateIterator(); !it->IsAtEnd(); it->Next())
            {
                tree->Insert(it->GetCurrent());
            }
        }

        uint32_t index = 0;
        for (auto it = tree->CreateIterator(); !it->IsAtEnd(); it->Next())
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