/*
 * treeNode.hpp
 *
 *  Created on: Aug 30, 2022
 *      Author: jsaavedr
 */

#ifndef TREENODE_HPP_
#define TREENODE_HPP_

#include "trees/treeList.hpp"

namespace trees {

class TreeList;
/**
 * \brief Nodo individual del árbol general.
 *
 * Cada nodo conoce a su padre, el dato entero que almacena y la lista de hijos
 * directos.  No se impone ninguna restricción en la cantidad de hijos que puede
 * contener.
 */
class TreeNode {
private:
        /// Referencia al nodo padre. Es nullptr para la raíz del árbol.
        TreeNode* parent;

        /// Valor almacenado en el nodo. Puede adaptarse a otro tipo si se requiere.
        int data; // data can be of any type

        /// Lista enlazada que mantiene los hijos inmediatos del nodo.
        TreeList* children;

public:
        /// Construye un nodo sin dato definido y sin padre.
        TreeNode();

        /// Construye un nodo con el valor proporcionado.
        explicit TreeNode(int val);

        /// Actualiza la referencia al nodo padre.
        void establecerPadre(TreeNode* node);

        /// Cambia el valor almacenado en el nodo.
        void establecerDato(int val);

        /// Reemplaza la lista de hijos por una lista externa.
        void establecerHijos(TreeList* list);

        /// Obtiene el puntero al padre del nodo.
        TreeNode* obtenerPadre();

        /// Devuelve el valor almacenado.
        int obtenerDato();

        /// Recupera la lista de hijos inmediata.
        TreeList* obtenerHijos();

        /// Libera los recursos del nodo y de sus descendientes.
        virtual ~TreeNode();
};

} /* namespace trees */

#endif /* TREENODE_HPP_ */
