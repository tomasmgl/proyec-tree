#include <iostream>
#include "tree.hpp"
#include "ListaSimple.hpp"
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
int peticiones_minimas(Tree<int> current, float percent);

int main()
{
    Lista<int> l;
    int n, k;
    float percent;
    int result;
    while (cin >> n)
    {
        cin >> percent;

        if(percent != 0 && n != 0)
        {
          Tree<int> t = Tree<int>(0);
            for(int i = 0; i < n; i++)
            {
                cin >> k;
                l.insertarFin(k);
            }
            t.insert(l);
            cout << peticiones_minimas(t, percent) << endl;
            t.clear();
            l.destruir();
        }
        else
            break;
    }
    return 0;
}

int peticiones_minimas(Tree<int> current, float percent) {
  //Si no es hoja, entra a la recursion
  if(!current.isLeaf())
  {
      vector<int> results;
      Lista< Tree<int> > hijos;
      hijos = current.children();
      while (!hijos.es_vacia())
      {
        results.push_back(peticiones_minimas(hijos.frente(), percent));
        hijos.eliminar_pri();
      }

    sort(results.begin(), results.end());
    float totalChilden = results.size();
    float needed = ceil(totalChilden * percent / 100);

    int i = 0;
    int toReturn = 0;
    for (vector<int>::iterator it = results.begin(); it != results.end() && i < needed; it++)
    {
      toReturn += *it;
      i++;
    }
    //Devuelve la suma mínima que generan los empleados necesarios
    return toReturn;
  }
  //Si es hoja, devuelve 1, simplemente cuenta un empleado.
  else return 1;
}
