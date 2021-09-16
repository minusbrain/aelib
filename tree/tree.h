/**
 * @author     Andreas Evers
 *
 * @copyright  Copyright � 2020 Andreas Evers
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this
 * software and associated documentation files (the �Software�), to deal in the Software
 * without restriction, including without limitation the rights to use, copy, modify,
 * merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies
 * or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED �AS IS�, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR
 * THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#pragma once
#include <fstream>
#include <functional>

#include "iterator.h"
#include "node.h"
#include "treehelper.h"

// TODO: Maybe think about offering different
//       sorting strategies:
//       * Day�Stout�Warren_algorithm to balance a tree
//         on demand
//       * Existing AVL tree algorithms to keep tree
//         balanced at all times!?

namespace base {
template <class T>
class Tree {
   public:
    typedef base::Iterator<T> iterator;

    Tree()
        : _root(nullptr),
          _comp(std::less<T>()),
#ifdef _AE_TREE_DEBUGMODE_
          _dbgcb(),
#endif
          _size(0) {
    }
    Tree(std::function<bool(T, T)> compare)
        : _root(nullptr),
          _comp(compare),
#ifdef _AE_TREE_DEBUGMODE_
          _dbgcb(),
#endif
          _size(0) {
    }

    virtual ~Tree() {
        TreeHelper<T>::recursiveDestroyNode(_root);
        _root = nullptr;
        _size = 0;
    }

#ifdef _AE_TREE_DEBUGMODE_
    void setDebugCallback(std::function<void(const Tree<T>&, std::string, iterator)> callback) { _dbgcb = callback; }
#endif

    // Sorted insertion of an item into the tree respecting the comparison
    // function.
    // TODO: Optimize as described here:
    //       http://www.geeksforgeeks.org/avl-tree-set-1-insertion/
    void insert(T item) {
        Node<T>* insertee = new Node<T>(nullptr, item);

        if (_root == nullptr) {  // Tree is empty so insert new node as root
            _root = insertee;
        } else {
            recursiveInsert(_root, insertee);
#ifdef _AE_TREE_DEBUGMODE_
            if (_dbgcb) _dbgcb(*this, "post_insert", iterator(insertee));
#endif
            // TODO: Embed balance into recursiveInsertion
            balance(insertee->getParent());
        }
        ++_size;
#ifdef _AE_TREE_DEBUGMODE_
        if (_dbgcb) _dbgcb(*this, "post_insert_and_balance", end());
#endif
    }

#ifdef _AE_TREE_DEBUGMODE_
    Node<T>* getRootNode() { return _root; }
#endif

    // Precondtiion: extratext must be of format [a-zA-Z0-9_]+
    // TODO: Move these debugging functions into a visitor.
    void streamStructureToDotFormat(std::ostream& out, std::string extratext, iterator highlight) const {
        out << "digraph tree_" << extratext.c_str() << "\n{\n";
        recursiveStreamStructureToDotFormat(_root, out, highlight);
        out << "}\n";
    }

    void recursiveStreamStructureToDotFormat(Node<T>* current, std::ostream& out, iterator highlight) const {
        if (current == nullptr) {
            out << "\tempty [shape=\"rectangle\" label=\"NULL\"];\n";
            return;
        }

        out << "\treal" << current << " [label=\"" << current->getPayload() << "\" xlabel=\"" << current->getBalance()
            << "\"";
        if (iterator(current) == highlight) {
            out << " color=\"red\"";
        }
        out << "];\n";
        if (current->getLeftChild() != nullptr) {
            out << "\treal" << current << " -> real" << current->getLeftChild() << ";\n";
            recursiveStreamStructureToDotFormat(current->getLeftChild(), out, highlight);
        } else {
            out << "\tlc" << current << " [shape=\"rectangle\" label=\"NULL\"];\n";
            out << "\treal" << current << " -> lc" << current << ";\n";
        }
        if (current->getRightChild() != nullptr) {
            out << "\treal" << current << " -> real" << current->getRightChild() << ";\n";
            recursiveStreamStructureToDotFormat(current->getRightChild(), out, highlight);
        } else {
            out << "\trc" << current << " [shape=\"rectangle\" label=\"NULL\"];\n";
            out << "\treal" << current << " -> rc" << current << ";\n";
        }
    }

    void erase(iterator position) {
        if (position == end()) return;

        Node<T>* x = position._current;
        Node<T>* par = x->getParent();
        uint8_t children = 0;
        Node<T>* lc = x->getLeftChild();
        Node<T>* rc = x->getRightChild();
        Node<T>* child = nullptr;  // any child

#ifdef _AE_TREE_DEBUGMODE_
        if (_dbgcb) _dbgcb(*this, "pre_erase", position);
#endif
        if (lc != nullptr) {
            ++children;
            child = lc;
        }
        if (rc != nullptr) {
            ++children;
            child = rc;
        }

        if (children == 0) {
            if (_root == x) _root = nullptr;
            prepareForDelete(x, par, nullptr);
            delete x;
#ifdef _AE_TREE_DEBUGMODE_
            if (_dbgcb) _dbgcb(*this, "post_nochild_erase", iterator(par));
#endif
            balance(par);
            --_size;
#ifdef _AE_TREE_DEBUGMODE_
            if (_dbgcb) _dbgcb(*this, "post_nochild_erase_and_balance", iterator(par));
#endif
        } else if (children == 1) {
            if (_root == x) _root = child;
            prepareForDelete(x, par, child);
            delete x;
#ifdef _AE_TREE_DEBUGMODE_
            if (_dbgcb) _dbgcb(*this, "post_onechild_erase", iterator(par));
#endif
            balance(par);
            --_size;
#ifdef _AE_TREE_DEBUGMODE_
            if (_dbgcb) _dbgcb(*this, "post_onechild_erase_and_balance", iterator(par));
#endif
        } else {
            Node<T>* z = getLeftMostNode(rc);
#ifdef _AE_TREE_DEBUGMODE_
            if (_dbgcb) _dbgcb(*this, "pre_twochild_erase_leftmostnode", iterator(z));
#endif
            x->swapPayload(z);
            erase(iterator(z));
#ifdef _AE_TREE_DEBUGMODE_
            if (_dbgcb) _dbgcb(*this, "post_twochild_erase", iterator(par));
#endif
        }
    }

    iterator find(const T& item) const { return recursiveFind(_root, item); }

    // Checks whether the provided item is contained inside the tree
    bool contains(const T& item) const { return find(item) != end(); }

    std::size_t size() const { return _size; }

    bool empty() const { return size() == 0; }

    void clear() {
        TreeHelper<T>::recursiveDestroyNode(_root);
        _root = nullptr;
        _size = 0;
    }

    iterator begin() const { return Iterator<T>(getLeftMostNode(_root)); }

    iterator end() const { return Iterator<T>(nullptr); }

    uint32_t getHeight() const {
        if (_root != nullptr) {
            return _root->getHeight();
        } else {
            return 0;
        }
    }

    int32_t getBalance() const {
        if (_root != nullptr) {
            return _root->getBalance();
        } else {
            return 0;
        }
    }

   private:
    Tree(const Tree&);

    void prepareForDelete(Node<T>* toDelete, Node<T>* parent, Node<T>* newChild) {
        if (parent != nullptr) {
            if (parent->getLeftChild() == toDelete) parent->setLeftChild(newChild);
            if (parent->getRightChild() == toDelete) parent->setRightChild(newChild);
            if (newChild != nullptr) newChild->setParent(parent);
        }
    }

    iterator recursiveFind(Node<T>* current, const T& item) const {
        if (current == nullptr) return end();
        // Check if item to search is smaller than current node
        // if it is take the left child node...
        if (_comp(item, current->getPayload()) == true) {
            return recursiveFind(current->getLeftChild(), item);
        }
        // ... if it is bigger take the right child node...
        else if (_comp(current->getPayload(), item) == true) {
            return recursiveFind(current->getRightChild(), item);
        }
        return iterator(current);
    }

    void recursiveInsert(Node<T>* current, Node<T>* insertee) {
        if (_comp(insertee->getPayload(), current->getPayload()) == true) {
            // Check if the left child node exists already
            if (current->getLeftChild() == nullptr) {
                // If it does not, add the new node exactly here
                insertee->setParent(current);
                current->setLeftChild(insertee);
            } else {
                // If it does, follow this branch
                recursiveInsert(current->getLeftChild(), insertee);
            }
        } else {
            // Check if the right child node exists already
            if (current->getRightChild() == nullptr) {
                // If it does not, add the new node exactly here
                insertee->setParent(current);
                current->setRightChild(insertee);
            } else {
                // If it does, follow this branch
                recursiveInsert(current->getRightChild(), insertee);
            }
        }
        current->updateHeight();
    }

    void balance(Node<T>* node) {
        Node<T>* newRoot = nullptr;
        Node<T>* parent = nullptr;
        int32_t nodeBalance = 0;

        while (node != nullptr) {
            parent = node->getParent();
            newRoot = nullptr;
            nodeBalance = node->getBalance();
            if (nodeBalance > 1) {
                if (node->getRightChild()->getBalance() < 0) {
                    newRoot = TreeHelper<T>::leftRightRotateSubtree(node);
                    updateParent(parent, node, newRoot);
#ifdef _AE_TREE_DEBUGMODE_
                    if (_dbgcb) _dbgcb(*this, "post_leftRightRotateSubtree", iterator(newRoot));
#endif
                } else {
                    newRoot = TreeHelper<T>::leftRotateSubtree(node);
                    updateParent(parent, node, newRoot);
#ifdef _AE_TREE_DEBUGMODE_
                    if (_dbgcb) _dbgcb(*this, "post_leftRotateSubtree", iterator(newRoot));
#endif
                }
            } else if (nodeBalance < -1) {
                if (node->getLeftChild()->getBalance() > 0) {
                    newRoot = TreeHelper<T>::rightLeftRotateSubtree(node);
                    updateParent(parent, node, newRoot);
#ifdef _AE_TREE_DEBUGMODE_
                    if (_dbgcb) _dbgcb(*this, "post_rightLeftRotateSubtree", iterator(newRoot));
#endif
                } else {
                    newRoot = TreeHelper<T>::rightRotateSubtree(node);
                    updateParent(parent, node, newRoot);
#ifdef _AE_TREE_DEBUGMODE_
                    if (_dbgcb) _dbgcb(*this, "post_rightRotateSubtree", iterator(newRoot));
#endif
                }
            }
            if (newRoot != nullptr) {
                node = newRoot->getParent();
            } else {
                node = node->getParent();
            }
        }
    }

    void updateParent(Node<T>* parent, Node<T>* oldRoot, Node<T>* newRoot) {
        if (parent == nullptr) {
            newRoot->makeRoot();
            _root = newRoot;
        } else {
            if (parent->getLeftChild() == oldRoot) {
                newRoot->setParent(parent);
                parent->setLeftChild(newRoot);
            } else {
                newRoot->setParent(parent);
                parent->setRightChild(newRoot);
            }
        }
    }

    Node<T>* _root;
    std::function<bool(T, T)> _comp;
#ifdef _AE_TREE_DEBUGMODE_
    std::function<void(const Tree<T>&, std::string, iterator)> _dbgcb;
#endif
    std::size_t _size;
};
}  // namespace base
