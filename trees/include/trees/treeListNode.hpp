/*
 * childNode.hpp
 *
 *  Created on: Aug 30, 2022
 *      Author: jsaavedr
 */

#ifndef CHILDNODE_HPP_
#define CHILDNODE_HPP_

#include "trees/treeNode.hpp"

namespace trees {
class TreeNode;
/**
 * \brief Nodo de la lista enlazada de hijos.
 *
 * Envuelve un puntero a TreeNode y el enlace al siguiente elemento de la lista
 * utilizada en TreeList.
 */
class TreeListNode {
private:
        /// Nodo del árbol almacenado en esta posición de la lista.
        TreeNode* data;

        /// Puntero al siguiente elemento de la lista o nullptr si es el último.
        TreeListNode* ptrNext;

public:
        /// Construye un nodo sin dato y sin siguiente (ambos nulos).
        TreeListNode();

        /// Construye un nodo inicializando dato y enlace.
        TreeListNode(TreeNode* _data, TreeListNode* next = nullptr);

        /// Actualiza el dato almacenado.
        void establecerDato(TreeNode* _data);

        /// Cambia el puntero al siguiente elemento.
        void establecerSiguiente(TreeListNode* _next);

        /// Devuelve el dato almacenado.
        TreeNode* obtenerDato();

        /// Devuelve el siguiente elemento en la lista.
        TreeListNode* obtenerSiguiente();

        /// Libera el nodo de árbol almacenado.
        virtual ~TreeListNode();
};

} /* namespace trees */

#endif /* CHILDNODE_HPP_ */
