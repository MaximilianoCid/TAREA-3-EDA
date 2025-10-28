/*
 * tree.cpp
 *
 *  Created on: Aug 31, 2022
 *      Author: jsaavedr
 */

#include "trees/tree.hpp"
#include <iostream>

namespace trees {

Tree::Tree(): root(nullptr) {
        // El árbol parte vacío; la raíz se inicializa en nullptr.
}

void Tree::establecerRaiz(TreeNode* node){
        // Solo permitimos fijar la raíz una vez para evitar pérdidas de memoria.
        if (root == nullptr){
                root = node;
        }
}
void Tree::insertar(TreeNode* child, TreeNode* parent){
        // Inserta el nodo hijo bajo el padre siempre que ambos existan.
        if (parent != nullptr && child != nullptr){
                child->establecerPadre(parent);
                parent->obtenerHijos()->insertarPrimero(child);
        }
}

void Tree::insertar(int val, int val_parent){
        // Se busca el nodo padre y, de encontrarse, se crea el nuevo hijo.
        TreeNode* parent = buscar(val_parent);
        if (parent != nullptr){
                TreeNode* child = new TreeNode(val);
                insertar(child, parent);
                std::cout << "insertado " << val << " in " << val_parent << " at " << parent << std::endl;
        }
}

TreeNode* Tree::buscarRecursivo(int val, TreeNode* node){
        TreeNode* ans = nullptr;
        if (node != nullptr){
                if (node->obtenerDato() == val){
                        ans = node;
                }
                else{ // search in children
                        // Explora recursivamente cada hijo hasta encontrar el valor.
                        TreeList* childrenList = node->obtenerHijos();
                        TreeListNode* ptr = childrenList->obtenerCabeza();
                        while (ptr!=nullptr && ans == nullptr){
                                ans = buscarRecursivo(val, ptr->obtenerDato());
                                ptr = ptr->obtenerSiguiente();
                        }
                }
        }
        return ans;
}

TreeNode* Tree::buscar(int val){
        // Punto de entrada para la búsqueda desde la raíz.
        TreeNode* ans = buscarRecursivo(val, root);
        return ans;
}


void Tree::recorrerRecursivo(TreeNode* node, int level){
        if (node != nullptr){
                // Se imprime el valor con una sangría proporcional al nivel.
                std::cout << std::string(level*2, '-');
                std::cout<<node->obtenerDato() << " at level " << level <<std::endl;
                TreeList* childrenList = node->obtenerHijos();
                TreeListNode* ptr = childrenList->obtenerCabeza();
                while (ptr!=nullptr){
                        recorrerRecursivo(ptr->obtenerDato(), level + 1);
                        ptr = ptr->obtenerSiguiente();
                }
        }
}

void Tree::recorrer(){
        // Inicia un recorrido en profundidad a partir de la raíz.
        recorrerRecursivo(root, 1);
}

Tree::~Tree() {
        // Al eliminar el árbol se libera la raíz, lo que recursivamente borra todo.
        delete root;
}

} /* namespace trees */
