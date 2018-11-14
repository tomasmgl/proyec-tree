#ifndef NODOARBOL
#define NODOARBOL
#include<iostream>
template <class T>
class Nodoarbol
{
	private:
		Nodoarbol *rb,*ls,*padre;
		T element;
	public:
		Nodoarbol(){rb=ls=NULL;};
		Nodoarbol(T x){element=x;rb=ls=NULL;}
		Nodoarbol(T x ,Nodoarbol *hi,Nodoarbol *hd){element=x;rb=hd;ls=hi;}
		/**consultar**/
		Nodoarbol *consultarrb(){return rb;}
		Nodoarbol *consultarls(){return ls;}
		Nodoarbol *consultarpad(){return padre;}
		T consultare(){return element;}
		/**modificar**/
		void modifrb(Nodoarbol *x){rb=x;}
		void modifls(Nodoarbol *x){ls=x;}
		void modifpad(Nodoarbol *x){padre=x;}
		void modife(T  x){element=x;}
		bool eshoja(){return(ls==NULL && rb==NULL);}
		~Nodoarbol(){}
};



#endif
