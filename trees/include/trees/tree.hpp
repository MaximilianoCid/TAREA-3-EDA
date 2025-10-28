/*
 * tree.hpp
 *
 *  Created on: Aug 31, 2022
 *      Author: jsaavedr
 */

#ifndef TREE_HPP_
#define TREE_HPP_

#include "trees/treeNode.hpp"


namespace trees {

/**
 * \brief Representa un árbol general (no binario) cuyos nodos almacenan enteros.
 *
 * La clase encapsula el puntero a la raíz y ofrece operaciones básicas para
 * insertar hijos, buscar valores y recorrer el árbol.  Se apoya en las clases
 * auxiliares TreeNode y TreeList para administrar los vínculos entre nodos y la
 * lista de hijos de cada uno.
 */
class Tree {
private:
        /// Puntero a la raíz del árbol. Puede ser nulo cuando el árbol está vacío.
        TreeNode* root;

public:
        /// Construye un árbol vacío inicializando la raíz a nullptr.
        Tree();

        /// Asigna la raíz del árbol si aún no se había establecido.
        void establecerRaiz(TreeNode* node);

        /// Inserta un nodo hijo debajo de un nodo padre ya existente.
        void insertar(TreeNode* node, TreeNode* parent);

        /// Crea un nodo hijo con el valor indicado e intenta insertarlo bajo el padre.
        void insertar(int child, int parent);

        /// Búsqueda recursiva de un valor a partir de un nodo arbitrario.
        TreeNode* buscarRecursivo(int val, TreeNode* node);

        /// Busca un valor dentro del árbol empezando desde la raíz.
        TreeNode* buscar(int val);

        /// Recorre el árbol en preorden imprimiendo cada nivel con indentación.
        void recorrerRecursivo(TreeNode* node, int level);

        /// Recorre el árbol completo desde la raíz.
        void recorrer();

        /// Libera todos los recursos asociados al árbol y sus nodos.
        virtual ~Tree();
};

} /* namespace trees */

#endif /* TREE_HPP_ */
