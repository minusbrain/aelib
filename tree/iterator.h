/**
 * @author     Andreas Evers
 *
 * @copyright  Copyright © 2020 Andreas Evers
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this
 * software and associated documentation files (the “Software”), to deal in the Software
 * without restriction, including without limitation the rights to use, copy, modify,
 * merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies
 * or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR
 * THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#pragma once

#include <stdexcept>

#include "node.h"

namespace base
{
template <class T>
class Tree;

template <class T>
class Iterator
{
   public:
    Iterator() : _current(nullptr) {}
    Iterator(const Iterator& other) : _current(other._current) {}
    Iterator(Node<T>* current) : _current(current) {}

    const T operator*() const
    {
        if (_current == nullptr)
            throw std::out_of_range(
                "Iterator reached end of container, no dereferencing possible");
        return (const T)_current->getPayload();
    }

    const Iterator<T>& operator=(const Iterator<T>& other)
    {
        _current = other._current;
        return *this;
    }

    bool operator==(const Iterator<T>& other) const { return _current == other._current; }

    bool operator!=(const Iterator<T>& other) const { return !operator==(other); }

    const Iterator& operator++()
    {
        // If we are already beyond the end do nothing.
        if (_current == nullptr)
        {
            return *this;
        }

        // If the current node has a right child, then this is always
        // the correct node to go to next and traverse it to the leftmost
        // child and leave the increment function
        if (_current->getRightChild() != nullptr)
        {
            _current = getLeftMostNode(_current->getRightChild());
            return *this;
        }

        while (true)
        {
            Node<T>* parent = _current->getParent();
            // If there is no parent (and no right child) we are done iterating.
            // Set iterator beyond end
            if (parent == nullptr)
            {
                _current = nullptr;
                return *this;
            }

            // If we are the left child of our parent the parent is the next node
            // to go to.
            if (parent->getLeftChild() == _current)
            {
                _current = parent;
                return *this;
            }

            _current = parent;
        }
    }

    const Iterator& operator--()
    {
        // If we are already beyond the end do nothing.
        if (_current == nullptr)
        {
            return *this;
        }

        // If the current node has a left child, then this is always
        // the correct node to go to next and traverse it to the rightmost
        // child and leave the increment function
        if (_current->getLeftChild() != nullptr)
        {
            _current = getRightMostNode(_current->getLeftChild());
            return *this;
        }

        while (true)
        {
            Node<T>* parent = _current->getParent();
            // If there is no parent (and no left child) we are done iterating.
            // Set iterator beyond end
            if (parent == nullptr)
            {
                _current = nullptr;
                return *this;
            }

            // If we are the right child of our parent the parent is the next node
            // to go to.
            if (parent->getRightChild() == _current)
            {
                _current = parent;
                return *this;
            }

            _current = parent;
        }
    }

    const Iterator operator--(int)
    {
        Iterator temp(*this);
        --(*this);
        return temp;
    }

    const Iterator operator++(int)
    {
        Iterator temp(*this);
        ++(*this);
        return temp;
    }

    friend Tree<T>;

   private:
    Node<T>* _current;
};
}  // namespace base
