#ifndef nodo_h
#define nodo_h

 #include <iostream>

 template <class T>
 class nodo
 {
    private:
      T _info;
      nodo *_sig;
    public:
      nodo() : _sig(NULL) { };
      nodo(T e) : _info(e), _sig(NULL) { };
      nodo(const nodo& copia) : _info(copia._info), _sig(copia._sig) { };

      nodo* sig() const {return _sig;};
      T info() const {return _info;};

      void set_info(T e) { _info = e;};
      void modif_sig(nodo *nodito) { _sig = nodito;};
 };

#endif
