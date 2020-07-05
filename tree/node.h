#ifndef _AE_NODE_H_
#define _AE_NODE_H_

#include <algorithm>
#include <cstdint>

namespace base
{
template <class T>
class Node
{
   public:
    Node(Node<T>* parent, T payload)
        : _parent(parent), _left(nullptr), _right(nullptr), _payload(payload), _height(1)
    {
    }

    Node<T>* getParent() { return _parent; }

    Node<T>* getLeftChild() { return _left; }

    Node<T>* getRightChild() { return _right; }

    void setLeftChild(Node<T>* node)
    {
        _left = node;
        updateHeight();
    }

    void setRightChild(Node<T>* node)
    {
        _right = node;
        updateHeight();
    }

    void setParent(Node<T>* node) { _parent = node; }

    void updateHeight()
    {
        uint32_t lh = 0;
        uint32_t rh = 0;
        if (_left != nullptr) lh = _left->getHeight();
        if (_right != nullptr) rh = _right->getHeight();

        _height = std::max<uint32_t>(lh, rh) + 1;
    }

    uint32_t getHeight() { return _height; }

    int32_t getBalance()
    {
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
static Node<T>* getLeftMostNode(Node<T>* old)
{
    if (old == nullptr) return nullptr;

    while (old->getLeftChild() != nullptr)
    {
        old = old->getLeftChild();
    }

    return old;
}

template <class T>
static Node<T>* getRightMostNode(Node<T>* old)
{
    if (old == nullptr) return nullptr;

    while (old->getRightChild() != nullptr)
    {
        old = old->getRightChild();
    }

    return old;
}
}  // namespace base

#endif
