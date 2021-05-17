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

#include <algorithm>
#include <cstdint>

namespace base {
template <class T>
class Node {
   public:
    Node(Node<T>* parent, T payload)
        : _parent(parent), _left(nullptr), _right(nullptr), _payload(payload), _height(1) {}

    Node<T>* getParent() { return _parent; }

    Node<T>* getLeftChild() { return _left; }

    Node<T>* getRightChild() { return _right; }

    void setLeftChild(Node<T>* node) {
        _left = node;
        updateHeight();
    }

    void setRightChild(Node<T>* node) {
        _right = node;
        updateHeight();
    }

    void setParent(Node<T>* node) { _parent = node; }

    void updateHeight() {
        uint32_t lh = 0;
        uint32_t rh = 0;
        if (_left != nullptr) lh = _left->getHeight();
        if (_right != nullptr) rh = _right->getHeight();

        _height = std::max<uint32_t>(lh, rh) + 1;
    }

    uint32_t getHeight() { return _height; }

    int32_t getBalance() {
        uint32_t lh = 0;
        uint32_t rh = 0;
        if (_left != nullptr) lh = _left->getHeight();
        if (_right != nullptr) rh = _right->getHeight();
        return rh - lh;
    }

    void swapPayload(Node<T>* other) { std::swap(_payload, other->_payload); }

    void makeRoot() { _parent = nullptr; }

    bool isRoot() { return _parent == nullptr; }

    T getPayload() { return _payload; }

   private:
    Node();
    Node(const Node<T>&);

    Node<T>* _parent;
    Node<T>* _left;
    Node<T>* _right;
    T _payload;

    uint32_t _height;
};

template <class T>
static Node<T>* getLeftMostNode(Node<T>* old) {
    if (old == nullptr) return nullptr;

    while (old->getLeftChild() != nullptr) {
        old = old->getLeftChild();
    }

    return old;
}

template <class T>
static Node<T>* getRightMostNode(Node<T>* old) {
    if (old == nullptr) return nullptr;

    while (old->getRightChild() != nullptr) {
        old = old->getRightChild();
    }

    return old;
}
}  // namespace base
