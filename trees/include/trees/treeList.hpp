#ifndef CHILDRENLIST_HPP_
#define CHILDRENLIST_HPP_

#include "trees/treeListNode.hpp"

namespace trees {

class TreeNode;
class TreeListNode;
class TreeList {
private:
        //puntero al primer elemento
        TreeListNode* head;

public:
        //constructor
        TreeList();
        //entrega el head
        TreeListNode* obtenerCabeza();
        //inserta un nodo al principio
        void insertarPrimero(TreeNode* treeNode);
        //elimina el primer elemento
        void eliminarPrimero();
        //elimina un nodo
        void eliminar(int val);
        //elimina todos los nodos
        void eliminarTodos();
        //dice si esta vacio o no
        bool estaVacia();
        //entrega el nodo con el valor val
        TreeNode* buscar(int val);
        void imprimir();
        virtual ~TreeList();
};

} /* namespace trees */

#endif /* CHILDRENLIST_HPP_ */
