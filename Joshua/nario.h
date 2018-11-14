
/*	
,---. 
,.'-.   \ 
( (   ,'"""""-. 
`  ,X          `. 
  /` `           `._ 
 (            ,   ,_\ 
 |          ,---.,'o `. 
 |         / o   \     ) 
 \ ,.    (      .____, 
  \| \    \____,'     \ 
'`'\  \        _,____,' 
    \  ,--      ,-'     \ 
	( C     ,'         \ 
	`--'  .'           | 
      |   |         .O | 
__  |    \        ,-'_ 
   / `L     `._  _,'  ' `. 
 /    `--.._  `',.   _\  ` 
  -.       /\  | `. ( ,\  \ 
 /  `-._  /  \ |--'  (     \ 
'  `-.   `'    \/\`.   `.    ) 
\  -hrr-    \ `.  |    | 

*/
/*termina los pre pos orden */



#ifndef NARIO
#define NARIO
#include<iostream>
#include"nodoarbol.h"
#include "lista.h"
#include <list>
using std::cout;
using std::list;
template <class T>
class Nario
{
	private:
	Nodoarbol<T> *raiz;
	int peso;
	void agregarHIzq(Nario<T> &hIzq);
	void agregarHDer(Nario<T> &hder);
	void inorden(Nodoarbol<T> *aux);
	void postorden(Nodoarbol<T> *aux);
	void preorden(Nodoarbol<T> *aux);
	void destruir(Nodoarbol<T> *apRaiz);
	void cortar(Nodoarbol<T> *aux,Nodoarbol<T> *aux2,int cont,int pos);
	
	public:
	Nario& operator=(const Nario<T> &orig);
	Nario();
	Nario(const Nario &c);	
	~Nario();
	T root(){return raiz->consultare();}
	Nario(T e,list<Nario<T> > x);
	Nario(T e,list<T> x);
	int consultarp(){return peso;}
	void preorden();
	void eliminar(int pos);
	void eliminarpre(int pos);
	bool vacio(){return raiz==NULL;}
	Nario(const T &infoRaiz){ raiz = new Nodoarbol<T>(infoRaiz); peso=1;}
	
	void insertar(Nario<T> nuevo);
	void insertarp(Nodoarbol<T> *nuevo);
	void agregar(Nodoarbol<T> *destino, Nodoarbol<T> *origen);
	Nodoarbol<T> *copiar(Nodoarbol<T> *p);
	void invertir(){invertir(raiz);}
	void invertir(Nodoarbol<T> *p);
	list<T> niveles(Nario<T> a);
	list<T> niveles(){Nario<T> aux;
						aux.raiz=copiar(raiz);
						return(niveles(aux));}
	list<Nario<T> >	hijos(Nodoarbol<T> *a);
	list<Nario<T> > hijos();
};
/*******************************constructores***********************************/
template <class T>
Nario<T>::Nario()
{
	raiz=NULL;
	peso=0;
}


template <class T>
Nario<T>::Nario(const Nario<T> &c)
{
	raiz=copiar(c.raiz);
	peso=c.peso;
}

template<class T>
Nodoarbol<T> *Nario<T>::copiar(Nodoarbol<T> *p)
{
	if(p!=NULL)
	{
		return(new Nodoarbol<T>(p->consultare(),copiar(p->consultarls()),copiar(p->consultarrb())));
		
	}else
		{
			return (NULL);
		}
	
}




template <class T>/*crea el arbol a partir de una lista de arboles*/
Nario<T>::Nario(T e,list< Nario<T> > x)
{
	Nodoarbol<T> *creado,*a;
	
	if(!x.empty()){
		raiz= new  Nodoarbol<T>(e);
		creado=copiar(x.front().raiz);
		raiz->modifls(creado);
		x.pop_front();
		peso=2;
		a=creado;
		while(!x.empty())
		{
			
			creado=copiar(x.front().raiz);
			a->modifrb(creado);
			x.pop_front();
			a=creado;
		}
	}
}
template <class T>/*crea el arbol a partir de una lista de elementos*/
Nario<T>::Nario(T e,list<T> x)
{
	Nodoarbol<T> *creado;
	if(!x.empty()){
		raiz= new  Nodoarbol<T>(e);
		creado=new Nodoarbol<T>(x.front());
		raiz->modifls(creado);
		x.pop_front();
		peso=2;
		while(!x.empty())
		{
			creado->modifrb(new Nodoarbol<T>(x.front()));
			x.pop_front();
			creado=creado->consultarrb();
			peso++;
		}
	}
	
	
	
}

/**********************************recorridos*********************************/
template <class T>
void Nario<T>:: preorden(Nodoarbol<T> *aux)
{
	if(aux!=NULL)
	{
		cout<<aux->consultare();
		preorden(aux->consultarls());
		preorden(aux->consultarrb());
	}
}
template <class T>
void Nario<T>:: postorden(Nodoarbol<T> *aux)
{
	if(aux!=NULL)
	{	
		postorden(aux->consultarls());
		postorden(aux->consultarrb());
		cout<<aux->consultare();
	}
}

template <class T>
void Nario<T>:: inorden(Nodoarbol<T> *aux)
{
	if(aux!=NULL)
	{
		inorden(aux->consultarls());
		cout<<aux->consultare();
		inorden(aux->consultarrb());
		
	}
}
/**********************************destructor***********************************/
template <class T>
Nario<T>::~Nario()
{	
	if(raiz!=NULL){
	destruir(raiz);
	}
}

template<class T>
void Nario<T>::destruir(Nodoarbol<T> *apRaiz)
{
	// Recorrido en Postorden
	if (apRaiz != NULL)
	{
		destruir(apRaiz->consultarls());
		destruir(apRaiz->consultarrb());
		delete apRaiz;
		apRaiz = NULL;
		peso--;
	}
}
/*******************************sobrecarga ************************************/
template<class T>
Nario<T> &Nario<T>::operator=(const Nario<T> &orig)
{
	if (this != &orig)
	{  destruir(raiz);
	raiz=copiar(orig.raiz);
	}
	return *this;
}


/************************************privados****************************/
template<class T>
void Nario<T>::agregarHIzq(Nario<T> &hIzq)
{
	if (raiz != NULL && raiz->consultarls()== NULL)
		{
			raiz->modifls(hIzq.raiz);
			hIzq.raiz = NULL;
		}
}

template<class T>
void Nario<T>::agregarHDer(Nario<T> &hder)
{
	if (raiz != NULL && raiz->consultarrb()== NULL)
	{
		raiz->modifrb(hder.raiz);
		hder.raiz = NULL;
	}
}
template<class T>
void Nario<T>::preorden()
{
	preorden(raiz);
	cout<<std::endl;
	
}
/*******************************eliminar***************************/
template <class T>
void Nario<T>::cortar(Nodoarbol<T> *aux,Nodoarbol<T> *aux2,int cont,int pos)
{
	if(aux2!=NULL)
	{
		cout<<"cont="<<cont<<std::endl;
		cout<<"visitado"<<aux2->consultare()<<std::endl;
		if(pos==cont)
		{
			cout<<aux2->consultare()<<"sera eliminado"<<std::endl;
			aux->modifrb(aux2->consultarrb());
			aux2->modifrb(NULL);
			destruir(aux2);
		}
		else{
			cont++;
			cortar(aux2,aux2->consultarls(),cont,pos);
			cont++;
			cortar(aux2,aux2->consultarrb(),cont,pos);
			}
		
	}
	
	
}
template <class T>
void Nario<T>::eliminarpre(int pos)
{
	Nodoarbol<T> *aux,*aux2;
	
	if(raiz!=NULL &&pos!=0){
		if(pos==1){
			aux=raiz->consultarls();
			raiz->modifls(aux->consultarrb());
			aux->modifrb(NULL);
			destruir(aux);
		}else{
			aux2=aux=raiz;
			cout<<"se llama la recursion"<<std::endl;
			cortar(aux,aux2,2,pos);
		}
		
	}else{
		cout << "Se intento eliminar un SubArbol Inexistente" <<std::endl;
	}	
}

template<class T>
void Nario<T>::eliminar(int pos)
{
	Nodoarbol<T> *aux,*aux2;
	int i;
	
	if(raiz!=NULL&&pos!=0){
		if(pos==1){
			aux=raiz->consultarls();
			raiz->modifls(aux->consultarrb());
			aux->modifrb(NULL);
			destruir(aux);
		}else{
			aux=raiz->consultarls();
			i=2;
			while(i<pos&&aux!=NULL)
			{
				aux=aux->consultarrb();
				i++;
			}
			if(aux!=NULL&&aux->consultarrb()!=NULL){
			aux2=aux->consultarrb();
			aux->modifrb(aux->consultarrb()->consultarrb());
			aux2->modifrb(NULL);
			destruir(aux2);
			}
			
		}	
	}else{
	cout << "Se intento eliminar un SubArbol Inexistente" <<std::endl;
	}	
}

template <class T>
void Nario<T>::insertarp(Nodoarbol<T> *nuevo)
{
	Nodoarbol<T> *aux,*aux2;/*apuntadores*/
	aux=raiz;
	if( aux != NULL)
	{
		aux2=copiar(nuevo);
		if(aux->consultarls()==NULL)
		{
			aux2=copiar(nuevo);
			aux->modifls(aux2);
		}
		else{
			aux=aux->consultarls();
			while(aux->consultarrb()!=NULL)
			{
				aux=aux->consultarrb();
			}
			aux->modifrb(aux2);
			nuevo=NULL;
		}
		
		
	}
	
}
template <class T>
void Nario<T>::insertar(Nario<T> nuevo)
{
	insertarp(nuevo.raiz);
}
template <class T>
void Nario<T>::invertir(Nodoarbol<T> *p)
{
	
	Nodoarbol<T> *izq,*der,*nuevo;
	if(p!=NULL)
	{
		nuevo=p;
		der=p->consultarrb();
		izq=p->consultarls();
		nuevo->modifls(izq);
		nuevo->modifrb(der);
		invertir(nuevo->consultarls());
		invertir(nuevo->consultarrb());
	}
}
template <class T>
list<T> Nario<T>::niveles(Nario<T> a)
{
	list<T> salida;
	list< Nario<T> > c,h;
	Nario<T> aux;
	c.push_front(a);
	while(!c.empty())
	{
		aux=c.front();
		salida.push_front(aux.root());
		h=aux.hijos();
		c.pop_front();
		while(!h.empty())
		{
			c.push_back(h.front());
			h.pop_front();
			
		}
	}
	salida.reverse();
	return(salida);
}
template <class T>
list<Nario<T> > Nario<T>:: hijos(Nodoarbol<T> *a)
{
	list< Nario<T> > k;
	Nario<T> p;
	Nodoarbol<T> *aux,*aux2;
	
	if(a==NULL)
	{
		return (k);
	}else{
		
		aux=a->consultarls();
		while(aux!=NULL)
		{
			aux2=aux->consultarrb();
			aux->modifrb(NULL);
			p.raiz=p.copiar(aux);
			k.push_back(p);
			aux=aux2;
		}
	}
	
	return(k);
}
template <class T>
list< Nario<T> >Nario<T>:: hijos()
{
	list< Nario<T> > x;
	
	x=hijos(raiz);
	return(x);
	
}
#endif 
