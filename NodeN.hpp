#ifndef _NODE_N_TREE_HPP_
#define _NODE_N_TREE_HPP_
#include <iostream>

template<class T>
class NodeN
{
    private:
        T _key, _key2;
        NodeN<T> *_left, *_right;

    public:
        NodeN() : _key(0), _key2(0), _left(NULL), _right(NULL) { };
        NodeN(const NodeN<T>& e) : _key(e._key), _key2(e._key2), _left(NULL), _right(NULL) { };
        NodeN(T e) : _key(e), _key2(0), _left(NULL), _right(NULL) { };
        NodeN(T e, NodeN<T> *c) : _key(e), _left(c), _right(NULL) { };
        NodeN(T e, NodeN<T>* a, NodeN<T>* b) : _key(e), _left(a), _right(b) { };

        T getKey() const { return _key; }
        T getKey2() const { return _key2; }
        NodeN<T>* getLeft() const { return _left; }
        NodeN<T>* getRight() const { return _right; }

        void setKey(const T);
        void setKey2(const T);
        void setLeft(NodeN<T>*);
        void setRight(NodeN<T>*);
};

/**
 * Key setter.
 * */
template<class T>
void NodeN<T>::setKey(const T item)
{
    _key = item;
}

template<class T>
void NodeN<T>::setKey2(const T item)
{
    _key2 = item;
}

/**
 * Left child setter.
 * */
template<class T>
void NodeN<T>::setLeft(NodeN<T>* l)
{
    _left = l;
}

/**
 * Right Silbing setter.
 * */
template<class T>
void NodeN<T>::setRight(NodeN<T>* r)
{
    _right = r;
}

#endif
