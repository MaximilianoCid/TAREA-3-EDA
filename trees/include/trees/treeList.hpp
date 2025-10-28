/*
 * childrenList.hpp
 *
 *  Created on: Aug 31, 2022
 *      Author: jsaavedr
 */

#ifndef CHILDRENLIST_HPP_
#define CHILDRENLIST_HPP_

#include "trees/treeListNode.hpp"

namespace trees {

class TreeNode;
class TreeListNode;
/**
 * \brief Lista enlazada simple utilizada para almacenar los hijos de un nodo.
 *
 * La lista guarda punteros a TreeNode y ofrece operaciones básicas de inserción,
 * búsqueda y eliminación.  Se usa internamente por TreeNode para modelar la
 * relación padre-hijos.
 */
class TreeList {
private:
        /// Puntero al primer elemento de la lista.
        TreeListNode* head;

public:
        /// Construye una lista vacía.
        TreeList();

        /// Devuelve el nodo inicial de la lista.
        TreeListNode* obtenerCabeza();

        /// Inserta un nodo al inicio de la lista.
        void insertarPrimero(TreeNode* treeNode);

        /// Elimina el primer elemento de la lista.
        void eliminarPrimero();

        /// Elimina cualquier nodo cuyo valor almacenado coincida con val.
        void eliminar(int val);

        /// Vacía por completo la lista, liberando cada TreeListNode.
        void eliminarTodos();

        /// Indica si la lista está vacía.
        bool estaVacia();

        /// Busca un valor dentro de la lista y devuelve el TreeNode asociado.
        TreeNode* buscar(int val);

        /// Imprime en consola el valor de cada hijo almacenado.
        void imprimir();

        /// Libera todos los recursos asociados a la lista.
        virtual ~TreeList();
};

} /* namespace trees */

#endif /* CHILDRENLIST_HPP_ */
