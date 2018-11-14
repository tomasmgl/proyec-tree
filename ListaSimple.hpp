#ifndef _LISTA_
#define _LISTA_
#include "nodo.hpp"
#include <iostream>
#include <cstdlib>

template <class T>
class Lista
{
private:
    int longt;
    nodo<T> *pri;
    nodo<T> *ult;

public:
    Lista() : longt(0), pri(NULL), ult(NULL) { };
    Lista(const Lista<T>&);   //line 57
    ~Lista() { this->destruir(); };

    bool es_vacia() const { return this->longt == 0; };
    int longitud() const { return longt; };
    T tope() const;     //line 81
    T cola() const;     //line 89
    T consultar(int) const;   //line 97
    int encontrar(T) const;   //line 122
    void insertar(T, int);    //line 145
    void insertar_ord(T);     //line 188
    void insertarFin(T);      //line 230
    void insertarPri(T);      //line 247
    void eliminar(int);       //line 263
    void eliminar_pri();      //line 311
    void eliminar_ult();      //line 332
    void modificar(T, int);   //line 362
    void destruir();          //line 386
    void imprimir() const;    //line 405
    void invertir();          //line 421
    void _invertir(nodo<T>*); //line 434
    void sublista(Lista<T>&, int, int); //line 450
    bool es_sublista_seq(Lista<T>&);    //line 487
    void insertar_especial(long e);     //line 530
    void eliminar_sublista(int, int);   //line 541
    void delete_sublist(T, T);          //line 594
    int contar_sublista(Lista<T>&);     //line 603
    T frente() const { return this->pri->info(); };
    T fin() const { return this->ult->info(); };

    void operator=(const Lista<T> &);
    bool operator>(const Lista<T> &) const;
    bool operator<(const Lista<T> &) const;
    bool operator==(const Lista<T> &) const;
    bool operator>=(const Lista<T> &) const;
    bool operator<=(const Lista<T> &) const;

    template<class Ts>
    friend std::ostream& operator<<(std::ostream&, const Lista<Ts> &);
};

template <class T>
Lista<T>::Lista(const Lista<T>& L)
{
    if(L.pri != NULL)
    {
        pri = new nodo<T>(*L.pri);
        nodo<T> *aux = L.pri->sig();
        nodo<T> *lista = this->pri;
        nodo<T> *nuevo;

        while(aux->sig() != NULL)
        {
            nuevo = new nodo<T>(aux->info());
            lista->modif_sig(nuevo);
            lista = lista->sig();
            aux = aux->sig();
        }
        nuevo = new nodo<T>(aux->info());
        lista->modif_sig(nuevo);
        ult = nuevo;
    }
    this->longt = L.longt;
}

template <class T>
T Lista<T>::tope() const
{
    if(pri) return this->pri->info();

    throw "Lista vacia";
}

template <class T>
T Lista<T>::cola() const
{
    if(ult) return this->ult->info();

    throw "Lista vacia";
}

template <class T>
T Lista<T>::consultar(int pos) const
{
    if(pos > 0 && pos <= longt)
    {
        if(pos == 1)
        {
            return pri->info();
        }
        else if(pos == longt)
            return ult->info();
        else
        {
            nodo<T>  *aux = pri;
            for(int i = 1; i < pos; i++)
            {
                aux = aux->sig();
            }
            return aux->info();
        }
    }
    else
        return -666;
}

template <class T>
int Lista<T>::encontrar(T e) const
{
    if (!es_vacia())
    {
        nodo<T> *aux;
        int i = 1;
        aux = pri;

        while (aux != NULL)
        {
            if (aux->info() == e)
                return i;

            aux = aux->sig();
            i++;
        }
        return i;
    }

    return -1; // No encontrado
}

template <class T>
void Lista<T>::insertar(T e, int pos)
{
    nodo<T> *aux, *nuevo;
    nuevo = new nodo<T>(e);
    int i=2;

    if(es_vacia())
    {
        pri = nuevo;
        ult = nuevo;
        longt++;
    }
    else
    {
        if(pos == 1)
        {
            nuevo->modif_sig(pri);
            pri = nuevo;
        }
        else if(pos > longt)
        {
            ult->modif_sig(nuevo);
            ult = nuevo;
        }
        else
        {
            aux = pri;
            if(pos <= longt)
            {
                while((i < pos) && (aux->sig() != NULL))
                {
                    aux = aux->sig();
                    i++;
                }
                nuevo->modif_sig(aux->sig());
                aux->modif_sig(nuevo);
            }
        }
        longt++;
    }
}

template <class T>
void Lista<T>::insertar_ord(T e)
{
    nodo<T> *aux, *nuevo;
    nuevo = new nodo<T>(e);

    if(es_vacia())
    {
        pri = nuevo;
        ult = nuevo;
    }
    else
    {
        if(nuevo->info() < pri->info())
        {
            nuevo->modif_sig(pri);
            pri = nuevo;
        }
        else
        {
            aux = pri;
            while((aux->sig() != NULL) && (nuevo->info() > aux->sig()->info()))
            {
                aux = aux->sig();
            }

            if(aux->sig() == NULL)
            {
                aux->modif_sig(nuevo);
                ult = nuevo;
            }
            else
            {
                nuevo->modif_sig(aux->sig());
                aux->modif_sig(nuevo);
            }
        }
    }
    longt = longt + 1;
    ult->modif_sig(NULL);
}

template<class T>
void Lista<T>::insertarFin(T e)
{
    nodo<T> *nuevo = new nodo<T>(e);
    if(!es_vacia())
    {
        ult->modif_sig(nuevo);
        ult = nuevo;
    }
    else
    {
        pri = nuevo;
        ult= nuevo;
    }
    longt++;
}

template<class T>
void Lista<T>::insertarPri(T e)
{
    nodo<T> *nuevo = new nodo<T>(e);
    if (!es_vacia())
    {
        nuevo->modif_sig(pri);
        pri = nuevo;
    }
    else
    {
        pri = nuevo;
        ult = nuevo;
    }
    longt++;
}
template<class T>
void Lista<T>::eliminar(int pos)
{
    if(pos > 0 && pos <= longt)
    {
        if (!es_vacia())
        {
            nodo<T> *aux, *target;
            target = pri;
            int i = 2;
            if (pos == 1)
            {
                if(pri->sig() != NULL)
                    pri = target->sig();
                else
                {
                    pri = ult = NULL;  //caso cuando la lista tiene un solo elemento
                    longt = 0;
                }
            }
            else
            {
                aux = target;
                target = aux->sig();
                while( i < pos)
                {
                    aux = aux->sig();
                    target = aux->sig();
                    i++;
                }
                if(target->sig() == NULL)
                {
                    ult = aux;
                    aux->modif_sig(NULL);
                }
                else
                {
                    aux->modif_sig(aux->sig()->sig());
                }

                delete target;
            }
            longt--;
        }
    }

}

template<class T>
void Lista<T>::eliminar_pri()
{
    if(!es_vacia())
    {
        nodo<T> *aux;
        aux = pri;
        if(longt > 1)
        {
            pri = pri->sig();
            longt--;
        }
        else
        {
            pri = ult = NULL;
            longt = 0;
        }
        delete aux;
    }
}

template<class T>
void Lista<T>::eliminar_ult()
{
    if (pri->sig() != NULL)
    {
        nodo<T> *ant, *act;
        act = pri;
        for(int i = 0; i < longt; i++)
        {
            if(act->sig() != NULL)
            {
                ant = act;
                act = act->sig();
            }
        }
        ant->modif_sig(NULL);
        ult = ant;
        delete act;
        longt--;
    }
    else
    {
        nodo<T> *aux = pri;
        delete aux;
        pri = ult = NULL;
        longt = 0;
    }
}

template <class T>
void Lista<T>::modificar(T e, int pos)
{
    if(!es_vacia())
    {
        if (pos == 1)
            pri->set_info(e);

        else if (pos == longt)
            ult->set_info(e);

        else
        {
            nodo<T> *aux = pri;
            int i = 1;
            while(i < pos)
            {
                aux = aux->sig();
                i++;
            }
            aux->set_info(e);
        }
    }
}

template<class T>
void Lista<T>::destruir()
{
    if(!es_vacia())
    {
        nodo<T> *aux = pri;
        while(aux->sig() != NULL)
        {
            aux = aux->sig();
            delete pri;
            pri = aux;
        }
        delete aux;
    }
    pri = NULL;
    ult = NULL;
    longt = 0;
}

template <class T>
void Lista<T>::imprimir() const
{
    nodo<T> *aux;
    if(es_vacia())
    {
        std::cout << "la lista es vacia" << std::endl;
    }
    else
    {
        aux = pri;
        while(aux->sig() != NULL)
        {
            std::cout << aux->info() << "->";
            aux = aux->sig();
        }
        std::cout << aux->info();
        std::cout << std::endl;
    }

}

template<class T>
void Lista<T>::invertir()
{
    if(!es_vacia())
        _invertir(this->pri);
}

template <class T>
void Lista<T>::_invertir(nodo<T> *act)
{
    if(act->sig() == NULL)
    {
        ult = pri;
        pri = act;
    }
    else
    {
        _invertir(act->sig());
        act->sig()->modif_sig(act);
        act->modif_sig(NULL);
    }
}

template<class T>
void Lista<T>::sublista(Lista<T>& L, int A, int B)
{
    if (A > B)
    {
        int aux = A;
        A = B;
        B = aux;
    }

    if ((A >= 1 && A <= L.longt) && (B >= 1 && B <= L.longt))
    {
        nodo<T> *aux = L.pri;
        nodo<T> *aux2 = NULL;
        nodo<T> *nuevo;

        for (int i = 1; i <= B; i++)
        {
            if (i >= A)
            {
                nuevo = new nodo<T>(aux->info());

                if (i == A)
                    this->pri = nuevo;
                else
                    aux2->modif_sig(nuevo);

                aux2 = nuevo;
            }
            aux = aux->sig();
        }
        this->ult = nuevo;
        this->longt = abs(B - A) + 1;
    }

}

template <class T>
bool Lista<T>::es_sublista_seq(Lista<T>& L)
{
    bool band = false;
    if(!L.es_vacia() && !this->es_vacia() && (L.longt >= this->longt))
    {
        nodo<T> *aux = L.pri;
        nodo<T> *aux2 = pri;
        int count = 0;

        band = true;
        while (band)
        {
            if(aux->info() == aux2->info())
            {
                count++;
                if(count < this->longt)
                {
                    if(aux->sig() != NULL)
                    {
                        aux = aux->sig();
                        aux2 = aux2->sig();
                    }
                    else band = false;
                }
                else break;
            }
            else
            {
                if(count == 0)
                {
                    if(aux->sig() != NULL)
                        aux = aux->sig();
                    else
                        band = false;
                }
                else band = false;
            }
        }
    }
    return band;
}

template <class T>
void Lista<T>::insertar_especial(long e)
{
    while(e > 10)
    {
        this->insertarPri(e % 100);
        e = e/100;
    }
    this->insertarPri(e);
}

template <class T>
void Lista<T>::eliminar_sublista(int a, int b)
{
    if(!es_vacia() && (a > 0) && (b > 0) && (a <= longt) && (b <= longt))
    {
        nodo<T> *aux, *aux2;
        int i = 1;

        if(b < a) i = a, a = b, b = i;

        aux = pri;
        aux2 = aux->sig();
        if(a == 1)
        {
            while (i <= b)
            {
                delete aux;
                aux = aux2;
                if(aux2->sig() != NULL)
                    aux2 = aux2->sig();
                i++;
            }
            pri = aux;
        }
        else
        {
            i = 2;
            while (i <= b)
            {
                if(i < a)
                {
                    aux = aux2;
                    aux2 = aux2->sig();
                }
                else
                {
                    if(aux2->sig() != NULL)
                    {
                        aux->modif_sig(aux2->sig());
                    }
                    else
                        aux->modif_sig(NULL);
                    delete aux2;
                    aux2 = aux->sig();
                }
                i++;
            }
        }
        if(b == this->longt) ult = aux;
        this->longt = this->longt - (b - a + 1);
    }
}

template <class T>
void Lista<T>::delete_sublist(T a, T b)
{
    int i, j;
    i = this->encontrar(a);
    j = this->encontrar(b);
    this->eliminar_sublista(i,j);
}

template <class T>
int Lista<T>::contar_sublista(Lista<T>& L)
{
    int count = 0;
    Lista<T> lista;
    nodo<T> *aux;

    if(!L.es_vacia() && !this->es_vacia() && (L.longt >= this->longt))
    {
        lista = L;
        do
        {
            aux = lista.pri;
            if(aux->info() == this->pri->info())
            {
                if(this->es_sublista_seq(lista))
                    count++;
            }
            lista.eliminar_pri();
        }
        while(this->longt <= lista.longt);
    }
    return count;
}

template<class T>
void Lista<T>::operator=(const Lista<T> & lista)
{
    if (this != &lista)
    {
        nodo<T> *listaPivot = lista.pri;
        nodo<T> *thisPivot = this->pri;
        nodo<T> *nuevo;
        for (int i = 1; i <= lista.longt; i++, listaPivot = listaPivot->sig())
        {
            nuevo = new nodo<T>();
            nuevo->set_info(listaPivot->info());

            if (i == 1)
            {
                this->pri = nuevo;
                thisPivot = nuevo;
            }
            else
            {
                thisPivot->modif_sig(nuevo);
                thisPivot = thisPivot->sig();
            }
        }
        ult = nuevo;
        this->longt = lista.longt;
    }
}

template<class T>
bool Lista<T>::operator>(const Lista<T> &l) const
{
    if (this != &l)
        return (this->longt > l.longt);

    return false;
}

template<class T>
bool Lista<T>::operator<(const Lista<T> &l) const
{
    return !(*this > l);
}

template<class T>
bool Lista<T>::operator==(const Lista<T> &l) const
{
    if (this != &l)
    {
        if (this->longth == l.longth)
        {
            nodo<T> *this_apt = this->pri;
            nodo<T> *l_apt = l.pri;
            bool esIgual;
            int i = 1;

            do
            {
                esIgual = (this_apt->info() == l_apt->info());
                i++;
                this_apt = this_apt->sig();
                l_apt = l_apt->sig();
            }
            while (i <= this->longt && esIgual);

            return esIgual;
        }

        return false;
    }

    return true;
}

template<class T>
bool Lista<T>::operator>=(const Lista<T> &l) const
{
    if (this != &l)
        return (*this > l || *this == l);

    return true;
}

template<class T>
bool Lista<T>::operator<=(const Lista<T> &l) const
{
    if (this != &l)
        return (*this < l || *this == l);

    return true;
}

template<class T>
std::ostream& operator<<(std::ostream& out, const Lista<T> &lista)
{
    nodo<T> *aux;
    aux = lista.pri;
    for (int i = 0; i < lista.longt; i++, aux = aux->sig())
    {
        if (aux != lista.ult)
            out << aux->info() << " ";
        else
            out << aux->info();
    }
    return out;
}
#endif
