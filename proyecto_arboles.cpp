#include <iostream>
#include "tree.hpp"
#include "ListaSimple.hpp"

using namespace std;

int main()
{
    Tree<int> t;
    Lista<int> l;
    int n, k, percent;

    while (cin >> n)
    {
        cin >> percent;

        if(percent != 0 && n != 0)
        {
            t = Tree<int>(0);
            for(int i = 0; i < n; i++)
            {
                cin >> k;
                l.insertarFin(k);
            }
            t.insert(l);

            //t.evaluar(); Aqui metodo asombroso de solucion
            t.clear();
        }
        else
            break;
    }
    return 0;
}
