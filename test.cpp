#include <iostream>
#include "tree.hpp"
#include "NodeN.hpp"
#include "ListaSimple.hpp"

using namespace std;

int main()
{
  Tree<int> t = Tree<int>(0);
  Lista<NodeN<int>*> l;
  NodeN<int>* temp;
  int n, k;

  cin >> n;

  for(int i = 0; i < n; i++)
  {
    cin >> k;
    temp = new NodeN<int>(k);
    l.insertarFin(temp);
  }
    t.insert(l);

  return 0;
}
