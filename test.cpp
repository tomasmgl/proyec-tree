#include <iostream>
#include "tree.hpp"
#include "NodeN.hpp"
#include "ListaSimple.hpp"

using namespace std;

int main()
{
  Tree<int> t = Tree<int>(0);
  Lista<int> l;
  int n, k;

  cin >> n;

  for(int i = 0; i < n; i++)
  {
    cin >> k;
    l.insertarFin(k);
  }
    t.insert(l);

  return 0;
}
