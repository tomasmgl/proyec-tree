#ifndef _TREE_HPP_
#define _TREE_HPP_
#include <iostream>
#include "ListaSimple.hpp"
#include "NodeN.hpp"

template<class T>
class Tree
{
    protected:
        NodeN<T>* _root;

    public:
        Tree() : _root(NULL) { };
        Tree(NodeN<T> *p) : _root(p) { };
        Tree(const Tree<T>& t) : _root(copyTree(t._root)) { };
        Tree(T e) : _root(new NodeN<T>(e)) { };
        Tree(T, Lista<Tree<T> >);
        ~Tree() { _root = clear(_root); };
        bool isLeaf() {return (this->_root->getLeft() == NULL);}
        bool null() const {return _root == NULL;}
        void push(Tree<T>);
        Lista<Tree<T> > children() const;

        void clear() { _root = clear(_root); }

        void operator=(const Tree<T> &);
        void insert(Lista<T>&);

    private:
		    NodeN<T>* copyTree(NodeN<T>*) const;
        NodeN<T>* clear(NodeN<T>* p);
        void _insert(NodeN<T>*, NodeN<T>*, bool&);
};

template<class T>
Tree<T>::Tree(T e, Lista<Tree<T> > L)
{
	_root = new NodeN<T>(e);
  Tree<T> tree;

	if (!L.es_vacia())
	{
        tree = L.frente();
        L.eliminar_pri();
        _root->setLeft(copyTree(tree._root));

        for (NodeN<T>* silbings = _root->getLeft(); !L.es_vacia(); silbings = silbings->getRight())
          {
            tree = L.frente();
            L.eliminar_pri();
            silbings->setRight(copyTree(tree._root));
          }
	}
}

template<class T>
void Tree<T>::push(Tree<T> t)
{
    if (!t.null())
    {
        NodeN<T> *sil = _root->getLeft();
        while(sil->getRight() != NULL)
            sil = sil->getRight();

        sil->setRight(copyTree(t._root));
    }
}

template<class T>
Lista<Tree<T> > Tree<T>::children() const
{
    Lista<Tree<T> > L;
    for (NodeN<T> *s = _root->getLeft(); s != NULL; s = s->getRight())
    {
        Tree<T> t(new NodeN<T>(s->getKey(), copyTree(s->getLeft())));
        L.insertarFin(t);
    }
    return L;
}

template<class T>
void Tree<T>::operator=(const Tree<T> &tree)
{
    if (this != &tree)
    {
        this->_root = clear(this->_root);
        this->_root = copyTree(tree._root);
    }
}

// =====================================================================

template<class T>
NodeN<T>* Tree<T>::copyTree(NodeN<T>* p) const
{
    if (p != NULL)
        return new NodeN<T>(p->getKey(), copyTree(p->getLeft()), copyTree(p->getRight()));

    return NULL;
}

template<class T>
NodeN<T>* Tree<T>::clear(NodeN<T>* p)
{
    if (p != NULL)
    {
        p->setLeft(clear(p->getLeft()));
        p->setRight(clear(p->getRight()));
        delete p;
    }
    return NULL;
}

template<class T>
void Tree<T>::insert(Lista<T> &L)
{
    NodeN<T> *nuevo;
    int i = 0;
    bool band;


    while(!L.es_vacia())
    {
      band = false;
      i++;
      nuevo = new NodeN<T>(L.frente());
      L.eliminar_pri();
      nuevo->setKey2(i);
      _insert(nuevo, this->_root, band);
    }
}

template<class T>
void Tree<T>::_insert(NodeN<T> *nuevo, NodeN<T> *root, bool &band)
{
    NodeN<T> *p = root;
    NodeN<T> *aux;

      if(nuevo->getKey() == p->getKey2())
      {
        if(!p->getLeft())
          p->setLeft(nuevo);
        else
        {
          aux = p->getLeft();
          while(aux->getRight())
            aux = aux->getRight();

          aux->setRight(nuevo);
        }
        band = true;
      }
      else
      {
        if(p->getRight())
            _insert(nuevo, p->getRight(), band);
        if(!band)
        {
          if(p->getLeft())
            _insert(nuevo, p->getLeft(), band);
        }
      }
}

#endif
