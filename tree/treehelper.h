#ifndef _AE_TREEHELPER_H_
#define _AE_TREEHELPER_H_

#include "node.h"

namespace base
{
template <class T>
class TreeHelper
{
   public:
    /* What is done:
     *  Situation before ...
     *             root
     *                 \
     *                 r1
     *                /  \
     *             rl2    r2
     *
     * ...and after leftRotating over "root"
     *           r1
     *          /  \
     *       root    r2
     *         \
     *         rl2
     * Preconditions:
     * root must be a right heavy subtree with an existing
     * right child (must not be null!!!)
     */
    static Node<T>* leftRotateSubtree(Node<T>* root)
    {
        Node<T>* r1 = root->getRightChild();
        Node<T>* rl2 = r1->getLeftChild();
        if (rl2 != nullptr) rl2->setParent(root);
        root->setRightChild(rl2);
        // We need to temporarily set null as parent to r1
        // in order to prevent loops in updateMetaData when
        // setting the new child of r1.
        // It is the callers responsibility to set
        // the parent of r1 to the correct value after-
        // wards.
        // r1->makeRoot();
        root->setParent(r1);
        r1->setLeftChild(root);

        return r1;
    }

    /* What is done:
     * Situation before ...
     *             root
     *            /
     *          l1
     *         /  \
     *       l2    lr2
     *
     * ...and after rightRotating over "root"
     *           l1
     *          /  \
     *        l2    root
     *             /
     *          lr2
     * Preconditions:
     * root must be a left heavy subtree with an existing
     * left child (must not be null!!!)
     */
    static Node<T>* rightRotateSubtree(Node<T>* root)
    {
        Node<T>* l1 = root->getLeftChild();
        Node<T>* lr2 = l1->getRightChild();
        if (lr2 != nullptr) lr2->setParent(root);
        root->setLeftChild(lr2);
        // We need to temporarily set null as parent to l1
        // in order to prevent loops in updateMetaData when
        // setting the new child of l1.
        // It is the callers responsibility to set
        // the parent of l1 to the correct value after-
        // wards.
        // l1->makeRoot();
        root->setParent(l1);
        l1->setRightChild(root);

        return l1;
    }

    // Preconditions:
    // root must be a right heavy subtree with an existing
    // right child (must not be null!!!) which is left heavy
    // and must have an existing left child
    static Node<T>* leftRightRotateSubtree(Node<T>* root)
    {
        Node<T>* newRoot = root->getRightChild();
        newRoot = rightRotateSubtree(newRoot);
        if (newRoot != nullptr) newRoot->setParent(root);
        root->setRightChild(newRoot);
        return leftRotateSubtree(root);
    }

    // Preconditions:
    // root must be a left heavy subtree with an existing
    // left child (must not be null!!!) which is right heavy
    // and must have an existing right child
    static Node<T>* rightLeftRotateSubtree(Node<T>* root)
    {
        Node<T>* newRoot = root->getLeftChild();
        newRoot = leftRotateSubtree(newRoot);
        if (newRoot != nullptr) newRoot->setParent(root);
        root->setLeftChild(newRoot);
        return rightRotateSubtree(root);
    }

    static void recursiveDestroyNode(Node<T>* node)
    {
        if (node == nullptr) return;

        recursiveDestroyNode(node->getLeftChild());
        recursiveDestroyNode(node->getRightChild());
        delete node;
    }

   private:
    TreeHelper() = delete;
    ~TreeHelper() = delete;
    TreeHelper(const TreeHelper&) = delete;
    const TreeHelper& operator=(const TreeHelper&) = delete;
};
}  // namespace base

#endif
